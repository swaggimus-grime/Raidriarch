#include "raidpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Raid {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}