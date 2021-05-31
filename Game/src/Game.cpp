#include <Raidriarch.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Raid::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Raid::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Raid::Ref<Raid::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Raid::VertexBuffer::Create(vertices, sizeof(vertices)));
		Raid::BufferLayout layout = {
			{ Raid::ShaderDataType::Float3, "a_Position" },
			{ Raid::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Raid::Ref<Raid::IndexBuffer> indexBuffer;
		indexBuffer.reset(Raid::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Raid::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Raid::Ref<Raid::VertexBuffer> squareVB;
		squareVB.reset(Raid::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Raid::ShaderDataType::Float3, "a_Position" },
			{ Raid::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Raid::Ref<Raid::IndexBuffer> squareIB;
		squareIB.reset(Raid::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			
			uniform vec3 u_Color;
			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader.reset(Raid::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));

		m_TextureShader.reset(Raid::Shader::Create("assets/shaders/Texture.glsl"));

		m_Texture = Raid::Texture2D::Create("assets/textures/lil_b.png");
		m_ChernoLogoTexture = Raid::Texture2D::Create("assets/textures/captain_falcon.png");

		std::dynamic_pointer_cast<Raid::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Raid::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);

	}

	void OnUpdate(Raid::Timestep ts) override
	{
		if (Raid::Input::IsKeyPressed(RAID_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Raid::Input::IsKeyPressed(RAID_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Raid::Input::IsKeyPressed(RAID_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Raid::Input::IsKeyPressed(RAID_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Raid::Input::IsKeyPressed(RAID_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (Raid::Input::IsKeyPressed(RAID_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		Raid::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Raid::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Raid::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Raid::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Raid::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Raid::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		m_Texture->Bind();
		Raid::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_ChernoLogoTexture->Bind();
		Raid::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));


		// Triangle
		// Raid::Renderer::Submit(m_Shader, m_VertexArray);

		Raid::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Raid::Event& event) override
	{
	}
private:
	Raid::Ref<Raid::VertexArray> m_VertexArray;

	Raid::Ref<Raid::Shader> m_FlatColorShader, m_TextureShader;
	Raid::Ref<Raid::VertexArray> m_SquareVA;

	Raid::Ref<Raid::Texture2D> m_Texture, m_ChernoLogoTexture;

	Raid::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Game : public Raid::App
{
public:
	Game()
	{
		PushLayer(new ExampleLayer());
	}

	~Game()
	{

	}

};

Raid::App* Raid::CreateApp()
{
	return new Game();
}