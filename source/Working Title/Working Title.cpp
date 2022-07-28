// Working Title.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <time.h>
#include "Game.h"
#include "Utilities.h"
#include <Windows.h>

int _tmain()
{
	system("MODE CON COLS=93 LINES=40");

	srand(static_cast<unsigned int>(time(0)));

	Game *game = new Game();
	game->Run();

	delete game;


	return 0;
}