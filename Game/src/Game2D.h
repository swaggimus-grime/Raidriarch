#pragma once

#include "Raidriarch.h"

class Game2D : public Raid::Layer
{
public:
	Game2D();
	virtual ~Game2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Raid::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Raid::Event& e) override;
private:
	Raid::OrthographicCameraController m_CameraController;
	// Temp
	Raid::Ref<Raid::VertexArray> m_SquareVA;
	Raid::Ref<Raid::Shader> m_FlatColorShader;

	Raid::Ref<Raid::Texture2D> m_CheckerboardTexture;
	Raid::Ref<Raid::Texture2D> m_JokerTexture;
	Raid::Ref<Raid::Framebuffer> m_Framebuffer;

	glm::vec4 m_SquareColor = { 0.f, 1.f, 0.f, 1.f };
};