#include "Game2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Game2D::Game2D()
	: Layer("Game2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Game2D::OnAttach()
{
	m_SquareVA = Raid::VertexArray::Create();

	float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	Raid::Ref<Raid::VertexBuffer> squareVB;
	squareVB.reset(Raid::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	squareVB->SetLayout({
		{ Raid::ShaderDataType::Float3, "a_Position" }
		});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Raid::Ref<Raid::IndexBuffer> squareIB;
	squareIB.reset(Raid::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
	m_SquareVA->SetIndexBuffer(squareIB);

	m_FlatColorShader = Raid::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Game2D::OnDetach()
{
}

void Game2D::OnUpdate(Raid::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Raid::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Raid::RenderCommand::Clear();

	Raid::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<Raid::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<Raid::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	Raid::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Raid::Renderer::EndScene();
}

void Game2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Game2D::OnEvent(Raid::Event& e)
{
	m_CameraController.OnEvent(e);
}