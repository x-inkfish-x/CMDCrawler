#pragma once
#include "Utilities.h"
#include "Door.h"

namespace Factory
{
	Door DoorFactory(Door &aDoor, Player &aPlayer, std::vector<std::vector<Room>> &someRooms, Directions aDirection);
}

