#include "raidpch.h"
#include "Framebuffer.h"

#include "Raid/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Raid {

	Ref<Framebuffer> Framebuffer::Create(const FramebufferProperties& props)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    RAID_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLFramebuffer>(props);
		}

		RAID_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}