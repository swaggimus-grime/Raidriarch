#pragma once

#include "Raidriarch.h"

namespace Raid {
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Raid::Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Raid::Event& e) override;
	private:
		OrthographicCameraController m_CameraController;
		// Temp
		Ref<VertexArray> m_SquareVA;
		Ref<Shader> m_FlatColorShader;

		Ref<Texture2D> m_CheckerboardTexture;
		Ref<Texture2D> m_JokerTexture;
		Ref<Framebuffer> m_Framebuffer;

		glm::vec4 m_SquareColor = { 0.f, 1.f, 0.f, 1.f };

		glm::vec2 m_ViewportSize = { 0.f, 0.f };
		bool m_ViewportFocused = false, m_ViewportHovered = false;
	};
}
