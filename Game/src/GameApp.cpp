#include <Raidriarch.h>
#include <Raid/Core/EntryPoint.h>

#include "Game2D.h"

class Game : public Raid::App
{
public:
	Game()
		:App("Game")
	{
		// PushLayer(new ExampleLayer());
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