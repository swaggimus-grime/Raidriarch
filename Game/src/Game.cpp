#include <Raidriarch.h>
#include <Raid/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Game2D.h"


class Game : public Raid::App
{
public:
	Game()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Game2D());
	}

	~Game()
	{
	}
};

Raid::App* Raid::CreateApp()
{
	return new Game();
}