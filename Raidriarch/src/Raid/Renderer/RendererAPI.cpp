#include "raidpch.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"
#include "Platform/Vulkan/VulkanRendererAPI.h"

namespace Raid {
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	RendererAPI* RendererAPI::Create()
	{
		switch (s_API) {
		case API::OpenGL:
			return new OpenGLRendererAPI;
		case API::Vulkan:
			return new VulkanRendererAPI;
		case API::None:
			RAID_CORE_ASSERT(false, "Raidriarch does not support API-less app yet!")
		default:
			RAID_CORE_ERROR("Unknown API!");
		}
	}
}