#include "stdafx.h"
#include <iostream>
#include "Room.h"
#include "Battle.h"
#include "DoorFactory.h"

void PrintChest(const int anOffSet);

Room::Room()
{
	myRoomIsCreated = false;
}


Room::~Room()
{
}

void Room::SetRoomPos(Player &aPlayer)
{
	myX = aPlayer.GetPlayerPosX();
	myY = aPlayer.GetPlayerPosY();
}

void Room::SetRoomChests(std::vector<Chest> &someChests)
{
	myChests = someChests;
}

void Room::CreateRoom(Player &aPlayer, std::vector<std::vector<Door>> &someDoors, std::vector<std::vector<Room>> &someRooms)
{
	myRoomIsCreated = true;

	CreateDoors(aPlayer, someDoors, someRooms);

	if (aPlayer.GetRoomEntered() > 0)
	{
		int chanceOfEncounter = 100;

		int encounter = randBetween(0, 99);

		if (chanceOfEncounter > encounter)
		{
			Battle battle(aPlayer);
		}

		/*switch (aPlayer.GetRoomEntered())
		{
		default:
			break;
		}*/
	}
	else
	{
		PrintFrame();
		std::string openingDialog = "Hello?";
		PrintDialog(openingDialog);
		PauseGame();

		openingDialog = "Hello?";
		PrintDialog(openingDialog);
		PauseGame();

		Render(aPlayer);

		openingDialog = "Ah, excellent, you woke up!";
		PrintDialog(openingDialog);
		PauseGame();

		openingDialog = "Not that I had any doubt regarding your... vitality, of course, but you have been out for a long time.";
		PrintDialog(openingDialog);
		PauseGame();

		openingDialog = "So, now that you are awake, let's get to it!";
		PrintDialog(openingDialog);
		PauseGame();

		openingDialog = "You probably are somewhat confused as to where you are and what has happened to you, but it's really quite simple.";
		PrintDialog(openingDialog);
		PauseGame();

		openingDialog = "You are, of course, in the maze, which is an experimental facility the exact location of which you need not concern yourself.";
		PrintDialog(openingDialog);
		PauseGame();

		openingDialog = "Now, mr. ... mmh.... I'm sorry, but it's a mess here, and I seem to have misplaced your file. Could you please give me your name again?";
		PrintDialog(openingDialog);
		PauseGame();

		do
		{
			openingDialog = "Input name:";
			PrintDialog(openingDialog);
		} while (!aPlayer.SetName());
		
		openingDialog = "Aah, of course, mr. " + aPlayer.GetName() + "... or would that be miss, or maybe even mrs.? Ah, no matter, a pleasure anyway.";
		PrintDialog(openingDialog);
		PauseGame();

		openingDialog = "Now, now, no need to be agitated, and the profanity is profoundly unnecessary.";
		PrintDialog(openingDialog);
		PauseGame();

		openingDialog = "Of course I can't tell you any more, that would destroy proper blinding!";
		PrintDialog(openingDialog);
		PauseGame();

		openingDialog = "Look, just get started, and I'll check in on you later...";
		PrintDialog(openingDialog);
		PauseGame();
	}
	
}

bool Room::IsRoomCreated()
{
	return myRoomIsCreated;
}

void Room::Render(Player &aPlayer)
{
	system("cls");
	PrintFrame();
	PrintRoom();

	switch (aPlayer.GetFacingDirection())
	{
	case Directions::Down:
		if (myDoors[static_cast<int>(Directions::Left)] == true)
		{
			PrintRightDoor();
		}
		if (myDoors[static_cast<int>(Directions::Down)] == true)
		{
			PrintCenterDoor();
		}
		if (myDoors[static_cast<int>(Directions::Right)] == true)
		{
			PrintLeftDoor();
		}
		break;

	case Directions::Up:
		if (myDoors[static_cast<int>(Directions::Right)] == true)
		{
			PrintRightDoor();
		}
		if (myDoors[static_cast<int>(Directions::Up)] == true)
		{
			PrintCenterDoor();
		}
		if (myDoors[static_cast<int>(Directions::Left)] == true)
		{
			PrintLeftDoor();
		}
		break;

	case Directions::Right:
		if (myDoors[static_cast<int>(Directions::Down)] == true)
		{
			PrintRightDoor();
		}
		if (myDoors[static_cast<int>(Directions::Right)] == true)
		{
			PrintCenterDoor();
		}
		if (myDoors[static_cast<int>(Directions::Up)] == true)
		{
			PrintLeftDoor();
		}
		break;

	case Directions::Left:
		if (myDoors[static_cast<int>(Directions::Up)] == true)
		{
			PrintRightDoor();
		}
		if (myDoors[static_cast<int>(Directions::Left)] == true)
		{
			PrintCenterDoor();
		}
		if (myDoors[static_cast<int>(Directions::Down)] == true)
		{
			PrintLeftDoor();
		}
		break;
	}

	for (unsigned int i = 0; i < myChests.size(); ++i)
	{
		PrintChest(i);
	}

	aPlayer.PrintStatusBar();
}

void Room::CreateDoors(Player &aPlayer, std::vector<std::vector<Door>> &someDoors, std::vector<std::vector<Room>> &someRooms)
{
	myDoorsP = std::vector<Door*>(4);
	int chanceOfDoorSpawn = 50;

	do{
		for (int i = 0; i < static_cast<int>(Directions::LAST); ++i)
		{
			int doorSpawned = randBetween(0, 99);

			//get door cordinates in that given direction
			std::vector<int> leftDoorCord = GetDoorCoords(static_cast<Directions>(i));

			if (!IsEdgeOfWorld(leftDoorCord, aPlayer))
			{
				//get a reference to the door
				Door &leftDoor = someDoors[leftDoorCord[static_cast<int>(Axees::X)]][leftDoorCord[static_cast<int>(Axees::Y)]];


				if (leftDoor.IsDoorCreated() == true)
				{
					myDoors[i] = true;
					myDoorsP[i] = &leftDoor;
				}
				else if (leftDoor.IsThereIsNoDoor() == true)
				{
					myDoors[i] = false;
				}
				else if (doorSpawned < chanceOfDoorSpawn)
				{
					Factory::DoorFactory(leftDoor, aPlayer, someRooms, static_cast<Directions>(i));

					myDoors[i] = true;
					myDoorsP[i] = &leftDoor;
				}
			}
		}
	} while (GetNumberOfDoors(someDoors) < myMinNumberOfDoors);

	for (int i = 0; i < static_cast<int>(Directions::LAST); ++i)
	{
		//get door cordinates in that given direction
		std::vector<int> leftDoorCord = GetDoorCoords(static_cast<Directions>(i));
		if (!IsEdgeOfWorld(leftDoorCord, aPlayer))
		{
			//get a reference to the door
			Door &leftDoor = someDoors[leftDoorCord[static_cast<int>(Axees::X)]][leftDoorCord[static_cast<int>(Axees::Y)]];

			if (myDoors[i] == false)
			{
				leftDoor.ThereIsNoDoor();
			}
		}
	}
}

std::vector<int> Room::GetDoorCoords(Directions aDirection)
{
	std::vector<int> returnVector;

	switch (aDirection)
	{
	case Directions::Up:
		returnVector = { 2 * myX, myY - 1 };
		return returnVector;

	case Directions::Right:
		returnVector = { 2 * myX + 1, myY };
		return returnVector;

	case Directions::Down:
		returnVector = { 2 * myX, myY };
		return returnVector;

	case Directions::Left:
		returnVector = { 2 * myX - 1, myY };
		return returnVector;
	}
	return std::vector < int > {-1, -1};
}

int Room::GetNumberOfDoors(std::vector<std::vector<Door>> &someDoors)
{
	int numberOfDoors = 0;

	for (int i = 0; i < static_cast<int>(Directions::LAST); i++)
	{
		std::vector<int> doorCoords = GetDoorCoords(static_cast<Directions>(i));

		if (myDoors[i] == true)
		{
			Door door = someDoors[doorCoords[static_cast<int>(Axees::X)]][doorCoords[static_cast<int>(Axees::Y)]];

			if (door.IsDoorCreated() == true)
			{
				++numberOfDoors;
			}
		}
	}

	return numberOfDoors;
}

void Room::EnterRoom(Player &aPlayer)//, std::vector<std::vector<Door>> &someDoors)
{
	if (aPlayer.GetRoomEntered() > 0)
	{
		int chanceOfEncounter = 10;
		int encounter = randBetween(0, 99);
		if (encounter < chanceOfEncounter)
		{
			Battle battle(aPlayer);
		}
	}
	
	PrintRoomDialogue(aPlayer);
}

void Room::PrintRoomDialogue(Player &aPlayer)
{

	int numOfChests = myChests.size();
	int numOfDoors = 0;
	for (int i = 0; i < static_cast<int>(Directions::LAST); ++i)
	{
		if (myDoors[i] == true)
		{
			++numOfDoors;
		}
	}

	bool inRoomMenu = true;
	while (inRoomMenu == true && aPlayer.GetHealth() > 0)
	{
		Render(aPlayer);
		std::string outputStr = "There are " + std::to_string(numOfChests) + " chests and " + std::to_string(numOfDoors) +
			" doors in this room. What would you like to examine?\n\n1. The chests\n2. The doors";
		
		PrintDialog(outputStr);

		//std::cout << "X: " << aPlayer.GetPlayerPosX() << "Y: " << aPlayer.GetPlayerPosY() << "  " << aPlayer.GetDirectionString();

		char choice = GetCharInput();

		switch (choice)
		{
		case '1':
			PrintChestDialogue(aPlayer);
			break;
		case '2':
			if (PrintDoorDialogue(aPlayer))
			{
				return;
			}
			break;
		default:
			break;
		}
		aPlayer.CheckCommand(choice);
		
	} 
	
}

bool Room::PrintDoorDialogue(Player &aPlayer)
{
	int numOfDoors = 0;
	for (unsigned int i = 0; i < myDoors.size(); ++i)
	{
		if (myDoors[i] == true)
		{
			++numOfDoors;
		}
	}

	std::string outputString = "Examining the room, you notice " + std::to_string(numOfDoors) + " doors.\n\n";
	std::vector<Door*> surroundingDoorCoords;

	int counter = 0;
	int index = static_cast<int>(aPlayer.GetFacingDirection()) + 1;
	

	for (int i = 0; i < static_cast<int>(Directions::LAST); ++i)
	{
		if ((index) % static_cast<int>(Directions::LAST) == 0)
		{
			index = 0;
		}
		bool hasDoor = myDoors[index];
		if (hasDoor == true)
		{
			++counter;
			surroundingDoorCoords.push_back(myDoorsP[index]);

			switch (i)
			{
			case 0:
				outputString += std::to_string(counter) + ". Right";
				break;

			case 1:
				outputString += std::to_string(counter) + ". Turn around";
				break;

			case 2:
				outputString += std::to_string(counter) + ". Left";
				break;

			case 3:
				outputString += std::to_string(counter) + ". Forward";
				break;

			default:
				outputString = "Some kind of error occured";
				break;
			}
			outputString += "\n";
		}
		++index;
	}

	outputString += "B. Back\n\n";

	char outPut;

	do
	{
		Render(aPlayer);
		PrintDialog(outputString);
		outPut = GetCharInput();

		unsigned int coordIndex = static_cast<int>(outPut - '0') - 1;

		if (coordIndex >= 0 && coordIndex < surroundingDoorCoords.size())
		{
			surroundingDoorCoords[coordIndex]->UseDoor(aPlayer);
			return true;
		}

		aPlayer.CheckCommand(outPut);
		
	} while (outPut != 'b' && outPut != 'B');

	return false;
}

bool Room::IsEdgeOfWorld(const std::vector<int> &someCoords, Player &aPlayer)
{
	return !(someCoords[static_cast<int>(Axees::X)] > 0 &&
		someCoords[static_cast<int>(Axees::X)] < aPlayer.GetWorldSizeX() * 2 - 1 &&
		someCoords[static_cast<int>(Axees::Y)] > 0 &&
		someCoords[static_cast<int>(Axees::Y)] < aPlayer.GetWorldSizeY() - 1);
}

void Room::PrintChestDialogue(Player &aPlayer)
{
	if (myChests.size() > 0)
	{
		char outPut;
		do
		{
			Render(aPlayer);
			std::string outputString = "Examining the room, you notice " + std::to_string(myChests.size()) + " chests.\n\n";
			int counter = myChests.size();
			for (unsigned int i = 0; i < myChests.size(); ++i)
			{
				outputString += std::to_string(i + 1) + " Difficulty " + std::to_string(myChests[i].GetChestDifficulty()) + ",\t" + myChests[i].GetStatusString() + "\n";
			}

			outputString += "B. Back";

			PrintDialog(outputString);

			outPut = GetCharInput();

			int index = static_cast<int>(outPut - '0') - 1;

			if (index >= 0 && index < counter)
			{
				myChests[index].OpenChest(aPlayer);
			}

			aPlayer.CheckCommand(outPut);
			
		} while (outPut != 'b' && outPut != 'B');
	}
	else
	{
		std::string outPut = "Woaw, there appears to be... no chests in this room. How about that.\n\n";
		PrintDialog(outPut);
		std::getchar();
	}
}

void PrintChest(const int anOffSet)
{
	int offsetX;
	int offsetY;

	switch(anOffSet)
	{
	case 0:
		offsetX = 18;
		offsetY = 27;
		break;

	case 1:
		offsetX = 29;
		offsetY = 25;
		break;

	case 2:
		offsetX = 57;
		offsetY = 26;
		break;

	default:
		offsetX = 0;
		offsetY = 0;
		break;
	}

	std::string chest = std::string(
		"   @@\n") +
		" @@!!!\n" +
		"@@!!!!!!\n" +
		"@!@!!!@@@\n" +
		"@!!@@@!!!@@\n" +
		" @!@!!@@@!!@\n" +
		"  @@!!!!!!!@\n" +
		"   @@@@@@@@@\n";

	gotoXY(static_cast<short>(offsetX), static_cast<short>(offsetY));

	for (unsigned int i = 0; i < chest.size(); i++)
	{
		if (chest[i] == '\n')
		{
			offsetY += 1;
			gotoXY(static_cast<short>(offsetX), static_cast<short>(offsetY));
		}
		else
		{
			PrintPoint(chest[i]);
		}
	}
}

std::string Player::GetDirectionString()
{
	std::string returnString = "";

	switch (GetFacingDirection())
	{
	case Directions::Up:
		returnString = "Up";
		break;
	case Directions::Right:
		returnString = "Right";
		break;
	case Directions::Down:
		returnString = "Down";
		break;
	case Directions::Left:
		returnString = "Left";
		break;
	case Directions::LAST:
		break;
	default:
		break;
	}

	return returnString;
}

std::vector<int> Room::GetRoomCoords() const
{
	return { myX, myY };
}

void Room::SetRoomCoords(std::vector<int> &someCoords)
{
	myX = someCoords[static_cast<int>(Axees::X)];
	myY = someCoords[static_cast<int>(Axees::Y)];
}

void Room::SetDoorPointers(std::vector<Door*> &someDoorP)
{
	myDoorsP = someDoorP;
}
void Room::SetDoorBools(std::bitset<4> someBools)
{
	myDoors = someBools;
}