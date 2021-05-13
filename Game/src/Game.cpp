#include <Raidriarch.h>

class ExampleLayer : public Raid::Layer {
public:
	ExampleLayer() {
		
	}

	void OnUpdate();
};

class Game : public Raid::App
{
public:
	Game()
	{

	}

	~Game()
	{

	}

};

Raid::App* Raid::CreateApp()
{
	return new Game();
}