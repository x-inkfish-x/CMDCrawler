#pragma once
#include <vector>
#include "Room.h"
#include "Door.h"
#include "Chest.h"

namespace Factory
{
	Room RoomFactory(Player &aPlayer, std::vector<std::vector<Door>> &someDoors, std::vector<std::vector<Room>> &someRooms);
	std::vector<Chest> GetRoomChests(Player &aPlayer);
}