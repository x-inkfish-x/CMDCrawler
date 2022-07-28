#pragma once
#include "Player.h"
#include "World.h"

class Game
{
public:
	Game();
	~Game();

	void Run();

private:
	void Update();
	void Render();
	bool myGameIsRunning;
	Player myPlayer;
	World myWorld;
};

