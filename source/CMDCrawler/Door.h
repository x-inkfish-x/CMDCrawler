#pragma once
#include <vector>
#include "Player.h"
class Room;

class Door
{
public:
	Door();
	~Door();

	bool IsDoorCreated();
	bool IsThereIsNoDoor();
	void ThereIsNoDoor();
	void CreateDoor(Player &aPlayer, std::vector<std::vector<Room>> &someRooms, Directions aDirection);
	void UseDoor(Player &aPlayer);

private:
	bool myDoorIsCreated = false;
	bool myNoDoor = false;
	Room *myFirstRoom;
	Room *mySecondRoom;
};

