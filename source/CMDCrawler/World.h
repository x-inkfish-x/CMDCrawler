#pragma once
#include <vector>
#include "Room.h"
#include "Door.h"
#include "Player.h"

class World
{
public:
	World();
	~World();

	int GetWorldSizeX();
	int GetWorldSizeY();
	void Update(Player &aPlayer);
	void Create(Player &aPlayer);
	void Render(Player &aPlayer);

private:
	int myWorldSizeX = 50;
	int myWorldSizeY = 50;

	int myCurrentRoomX;
	int myCurrentRoomY;

	std::vector<std::vector<Room>> myRooms;
	std::vector<std::vector<Door>> myDoors;

	void SetCurrentRoom(const Player &aPlayer);
};

