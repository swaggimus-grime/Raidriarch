#pragma once

#include "OrthographicCamera.h"
#include "PerspectiveCamera.h"
#include "Texture.h"

namespace Raid {
	struct Quad {
		glm::vec3 Position;
		glm::vec2 Size;
		glm::vec4 Color;
		Ref<Texture> TextureData;
		float Rotation;
	};

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		// Quads
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, float rotation = 0.f);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, float rotation = 0.f);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float rotation = 0.f, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float rotation = 0.f, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		// Quad param
		static void DrawQuad(const Quad& quad);

	private:
		static void Flush();
	};
}
