#pragma once
#include <vector>
#include <bitset>
#include <memory>
#include "Player.h"
#include "Door.h"
#include "Chest.h"
#include "Utilities.h"


class Room
{
public:
	Room();
	~Room();

	void EnterRoom(Player &aPlayer);

	void CreateRoom(Player &aPlayer, std::vector<std::vector<Door>> &someDoors, std::vector<std::vector<Room>> &someRooms);
	bool IsRoomCreated();
	void Render(Player &aPlayer);
	std::vector<int> GetRoomCoords() const;
	void SetRoomCoords(std::vector<int> &someCoords);

	void SetRoomPos(Player &aPlayer);
	void SetRoomChests(std::vector<Chest> &someChests);
	void SetDoorPointers(std::vector<Door*> &someDoorP);
	void SetDoorBools(std::bitset<4> someBools);
private:
	int chanceOfExit = 5;
	int myMinNumberOfDoors = 1;
	bool myRoomIsCreated;
	std::bitset<4> myDoors;
	std::vector<Door*> myDoorsP;

	std::vector<Chest> myChests;
	int myX;
	int myY;

	void CreateDoors(Player &aPlayer, std::vector<std::vector<Door>> &someDoors, std::vector<std::vector<Room>> &someRooms);

	std::vector<int> GetDoorCoords(Directions aDirection);
	int GetNumberOfDoors(std::vector<std::vector<Door>> &someDoors);
	void PrintRoomDialogue(Player &aPlayer);
	bool PrintDoorDialogue(Player &aPlayer);
	void PrintChestDialogue(Player &aPlayer);
	bool IsEdgeOfWorld(const std::vector<int> &someCoords, Player &aPlayer);
};

