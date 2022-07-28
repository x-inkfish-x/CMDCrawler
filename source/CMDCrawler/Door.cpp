#include "stdafx.h"
#include "Door.h"
#include "Room.h"

Door::Door()
{
	myDoorIsCreated = false;
	myFirstRoom = nullptr;
	mySecondRoom = nullptr;
}


Door::~Door()
{
}

bool Door::IsDoorCreated()
{
	return myDoorIsCreated;
}

void Door::CreateDoor(Player &aPlayer, std::vector<std::vector<Room>> &someRooms, Directions aDirection)
{
	myDoorIsCreated = true;
	myFirstRoom = &someRooms[aPlayer.GetPlayerPosX()][aPlayer.GetPlayerPosY()];

	std::vector<int> roomCoords = { aPlayer.GetPlayerPosX(), aPlayer.GetPlayerPosY() };

	switch (aDirection)
	{
	case Directions::Up:
		roomCoords = { roomCoords[static_cast<int>(Axees::X)], roomCoords[static_cast<int>(Axees::Y)] - 1 };
		break;
	case Directions::Right:
		roomCoords = { roomCoords[static_cast<int>(Axees::X)] + 1, roomCoords[static_cast<int>(Axees::Y)] };
		break;
	case Directions::Down:
		roomCoords = { roomCoords[static_cast<int>(Axees::X)], roomCoords[static_cast<int>(Axees::Y)] + 1 };
		break;
	case Directions::Left:
		roomCoords = { roomCoords[static_cast<int>(Axees::X)] - 1, roomCoords[static_cast<int>(Axees::Y)] };
		break;
	case Directions::LAST:
		break;
	default:
		roomCoords = { 1, 1 };
		break;
	}
	mySecondRoom = &someRooms[roomCoords[static_cast<int>(Axees::X)]][roomCoords[static_cast<int>(Axees::Y)]];
	mySecondRoom->SetRoomCoords(roomCoords);
}

void Door::UseDoor(Player &aPlayer)
{
	if (aPlayer.GetPlayerPos() == myFirstRoom->GetRoomCoords())
	{
		aPlayer.SetPlayerPos(mySecondRoom->GetRoomCoords());
	}
	else
	{
		aPlayer.SetPlayerPos(myFirstRoom->GetRoomCoords());
	}
}

bool Door::IsThereIsNoDoor()
{
	return myNoDoor;
}

void Door::ThereIsNoDoor()
{
	myNoDoor = true;
}