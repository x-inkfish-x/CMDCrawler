#include "stdafx.h"
#include "DoorFactory.h"

namespace Factory
{
	Door DoorFactory(Door &aDoor, Player &aPlayer, std::vector<std::vector<Room>> &someRooms, Directions aDirection)
	{
		aDoor.CreateDoor(aPlayer, someRooms, aDirection);
		return aDoor;
	}
}
