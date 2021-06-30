#pragma once

#include "Raid/Renderer/RendererAPI.h"

namespace Raid {
	class VulkanRendererAPI : public RendererAPI {
		virtual void Init() override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) override;
	};
}