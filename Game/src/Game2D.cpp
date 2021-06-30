#include "Game2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

#include <chrono>

Game2D::Game2D()
	: Layer("Game2D"), m_CameraController(1280.f / 720.f)
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

	RAID_PROFILE_FUNCTION();

	m_CameraController.OnUpdate(ts);

	{
		RAID_PROFILE_SCOPE("Renderer Prep");
		Raid::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Raid::RenderCommand::Clear();
	}
	
	{
		RAID_PROFILE_SCOPE("Renderer Draw");
		Raid::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Raid::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Raid::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		//Raid::Renderer2D::DrawQuad({ -1,-1 }, { 0.5,0.5 }, m_Joker);
		Raid::Renderer2D::EndScene();
	}
	
}

void Game2D::OnImGuiRender()
{
	RAID_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::End();
}

void Game2D::OnEvent(Raid::Event& e)
{
	m_CameraController.OnEvent(e);
}

