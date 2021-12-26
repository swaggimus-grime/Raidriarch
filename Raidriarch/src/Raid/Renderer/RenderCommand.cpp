#include "raidpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"
#include "Platform/Vulkan/VulkanRendererAPI.h"

namespace Raid {

	RendererAPI* RenderCommand::s_RendererAPI = RendererAPI::Create();

}