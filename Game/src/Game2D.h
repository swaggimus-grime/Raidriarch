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

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};