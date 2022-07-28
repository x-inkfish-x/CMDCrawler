#include "stdafx.h"
#include "RoomFactory.h"
#include "DoorFactory.h"
#include <bitset>

namespace Factory
{
	Room RoomFactory(Player &aPlayer, std::vector<std::vector<Door>> &someDoors, std::vector<std::vector<Room>> &someRooms)
	{

		Room room;
		room.SetRoomPos(aPlayer);
		std::vector<Chest> chests = GetRoomChests(aPlayer);
		room.SetRoomChests(chests);
		
		room.CreateRoom(aPlayer, someDoors, someRooms);
		

		return room;
	}


	std::vector<Chest> GetRoomChests(Player &aPlayer)
	{
		int numOfChests = randBetween(0, 3);
		std::vector<Chest> chests;

		for (int i = 0; i < numOfChests; i++)
		{
			chests.push_back(Chest(aPlayer));
		}

		return chests;
	}
}
