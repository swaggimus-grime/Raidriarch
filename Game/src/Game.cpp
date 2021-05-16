#include <Raidriarch.h>

class Game : public Raid::App
{
public:
	Game()
	{
		PushOverlay(new Raid::ImGuiLayer());
	}

	~Game()
	{

	}

};

Raid::App* Raid::CreateApp()
{
	return new Game();
}