#include "Game2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Game2D::Game2D()
	: Layer("Game2D"), m_CameraController(1280.0f / 720.0f), m_SquareColor({ 0.2f, 0.3f, 0.8f, 1.0f })
{
}

void Game2D::OnAttach()
{
	RAID_PROFILE_FUNCTION();

	m_CheckerboardTexture = Raid::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Game2D::OnDetach()
{
	RAID_PROFILE_FUNCTION();
}

void Game2D::OnUpdate(Raid::Timestep ts)
{
	RAID_PROFILE_FUNCTION();

	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Raid::Renderer2D::ResetStats();
	{
		RAID_PROFILE_SCOPE("Renderer Prep");
		Raid::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Raid::RenderCommand::Clear();
	}

	{
		static float rotation = 0.0f;
		rotation += ts * 50.0f;

		RAID_PROFILE_SCOPE("Renderer Draw");
		Raid::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Raid::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
		Raid::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Raid::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, m_SquareColor);
		Raid::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f);
		Raid::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_CheckerboardTexture, 20.0f);
		Raid::Renderer2D::EndScene();

		Raid::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				Raid::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		Raid::Renderer2D::EndScene();
	}
}

void Game2D::OnImGuiRender()
{
	RAID_PROFILE_FUNCTION();

	ImGui::Begin("Settings");

	auto stats = Raid::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Game2D::OnEvent(Raid::Event& e)
{
	m_CameraController.OnEvent(e);
}