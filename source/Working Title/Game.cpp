#include "stdafx.h"
#include <iostream>
#include "Game.h"
#include "Item.h"
#include "Chest.h"
#include "Utilities.h"
#include "Battle.h"


Game::Game()
{
	myGameIsRunning = true;
	myWorld.Create(myPlayer);
}


Game::~Game()
{
}

void Game::Run()
{
	while (myGameIsRunning == true && myPlayer.GetHealth() > 0 && myPlayer.GetStamina() > 0)
	{
		myWorld.Update(myPlayer);
		Update();
	}
}

void Game::Update()
{
	myPlayer.Update();
}

void Game::Render()
{
	system("cls");
}