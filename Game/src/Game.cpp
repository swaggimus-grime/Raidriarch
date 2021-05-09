#include <Raidriarch.h>

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