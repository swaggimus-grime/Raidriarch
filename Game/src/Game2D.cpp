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

	Raid::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Raid::Renderer2D::DrawQuad({ 0,0 }, { 1,1 }, { 0,1,0,1 });
	Raid::Renderer2D::EndScene();
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