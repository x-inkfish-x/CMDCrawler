#include "stdafx.h"
#include "World.h"
#include <iostream>
#include "RoomFactory.h"



World::World()
{
	
}


World::~World()
{
}

void World::Create(Player &aPlayer) {
	myRooms = std::vector<std::vector<Room>>(myWorldSizeX);

	for (unsigned int i = 0; i < myRooms.size(); i++)
	{
		myRooms[i] = std::vector<Room>(myWorldSizeY);
		std::fill(myRooms[i].begin(), myRooms[i].end(), Room());
	}

	myDoors = std::vector<std::vector<Door>>(2 * myWorldSizeX);

	for (unsigned int i = 0; i < myDoors.size(); i++)
	{
		myDoors[i] = std::vector<Door>(myWorldSizeY);
		std::fill(myDoors[i].begin(), myDoors[i].end(), Door());
	}

	aPlayer.SetPlayerPos({ myWorldSizeX / 2, myWorldSizeY / 2 });
	aPlayer.SetWorldSize(myWorldSizeX, myWorldSizeY);
	
}

int World::GetWorldSizeX()
{
	return myWorldSizeX;
}

int World::GetWorldSizeY()
{
	return myWorldSizeY;
}

void World::Update(Player &aPlayer)
{
	SetCurrentRoom(aPlayer);

	
	//TODO: FIGURE SHIT OUT
	if (myRooms[myCurrentRoomX][myCurrentRoomY].IsRoomCreated() == false )
	{
		myRooms[myCurrentRoomX][myCurrentRoomY] = Factory::RoomFactory(aPlayer, myDoors, myRooms);
	}
	
	if (aPlayer.GetHealth() > 0 && aPlayer.GetStamina() > 0)
	{
		myRooms[myCurrentRoomX][myCurrentRoomY].EnterRoom(aPlayer);
	}
	aPlayer.IncrementRoomsEntered();
}

void World::SetCurrentRoom(const Player &aPlayer)
{
	myCurrentRoomX = aPlayer.GetPlayerPosX();
	myCurrentRoomY = aPlayer.GetPlayerPosY();
}

//void World::Render(Player &aPlayer)
//{
//	//myRooms[myCurrentRoomX][myCurrentRoomY].Render(aPlayer);
//}