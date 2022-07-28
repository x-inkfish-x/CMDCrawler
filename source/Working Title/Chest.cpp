#include "stdafx.h"
#include <iostream>
#include "Chest.h"
#include "Utilities.h"
#include "ItemFactory.h"
#include "SpellFactory.h"


Chest::Chest(Player &aPlayer)
{
	myChestIsBroken = false;
	myChestIsOpen = false;
	myChestDifficulty = randBetween(1, 5) * (1 + aPlayer.GetRoomEntered() / 5);
}


Chest::~Chest()
{
}

void Chest::BreakChest(Player &aPlayer)
{
	int unlockValue = randBetween(0, 99) * aPlayer.GetStrength() * aPlayer.GetSpeed();
	

	if (unlockValue >= 1000 * myChestDifficulty)
	{
		myChestIsOpen = true;
		GenerateContents(aPlayer);
	}
	else
	{
		myChestIsBroken = true;
	}
}

void Chest::PickChest(Player &aPlayer)
{
	int unlockValue = randBetween(0, 99) * aPlayer.GetIntelligence() * aPlayer.GetDexterity();

	if (unlockValue >= 1000 * myChestDifficulty)
	{
		myChestIsOpen = true;
		GenerateContents(aPlayer);
	}
	else
	{
		myChestIsBroken = true;
	}
}

void Chest::DisplayChestContents(Player &aPlayer)
{
	char input;
	do
	{
		PrintBackGround();
		std::string output = "Chest\n\n1. Items\t" + std::to_string(myItems.size()) + "\n2. Spells\t" + std::to_string(mySpells.size()) + "\nB. Back";
		PrintDialog(output);

		input = GetCharInput();

		switch (input)
		{
		case '1':
			DisplayItems(aPlayer);
			break;
		case '2':
			DisplaySpells(aPlayer);
			break;
		default:
			break;
		}

		aPlayer.CheckCommand(input);

	} while (input != 'b' && input != 'B');
}

void Chest::DisplayItems(Player &aPlayer)
{
	char input;
	if (myItems.size() > 0)
	{
		do
		{
			PrintBackGround();

			std::string output;
			short offsetX = 3;
			short offsetY = 3;
			gotoXY(offsetX, offsetY);
			SetConsoleTextAttribute(hstdout, FOREGROUND_INTENSITY);
			std::cout << "Items";

			gotoXY(offsetX + 40, offsetY);
			std::cout << "Capacity: " << aPlayer.GetCapacity();

			++offsetY;
			gotoXY(2, offsetY);
			std::cout << "________________________________________________________________________________________";

			++offsetY;

			int counter = 0;

			for (unsigned int i = 0; i < myItems.size(); ++i)
			{
				short currentOffsetX = static_cast<short>(offsetX + 46 * counter);

				myItems[i].PrintItem(i + 1, currentOffsetX, offsetY, 0, FOREGROUND_INTENSITY);

				++counter;

				if ((counter + 1) % 3 == 0)
				{
					counter = 0;
					offsetY += 10;
				}
			}

			gotoXY(5, 36);
			std::cout << "B. Back";

			gotoXY(20, 36);
			std::cout << "Select item to pick up: ";
			input = GetCharInput();

			unsigned int index = static_cast<int>(input - '0') - 1;

			if (index >= 0 && index < myItems.size())
			{
				if (aPlayer.GetInventory().AddItemToInventory(myItems[index], aPlayer) == true)
				{
					myItems.erase(myItems.begin() + index);
				}
			}

			aPlayer.CheckCommand(input);

		} while (input != 'b' && input != 'B' && myItems.size() > 0);
	}
}

void Chest::DisplaySpells(Player &aPlayer)
{
	char input;
	if (mySpells.size() > 0)
	{
		do
		{
			PrintBackGround();

			std::string output;
			short offsetX = 3;
			short offsetY = 3;
			gotoXY(offsetX, offsetY);
			SetConsoleTextAttribute(hstdout, FOREGROUND_INTENSITY);
			std::cout << "Spells";

			++offsetY;
			gotoXY(2, offsetY);
			std::cout << "________________________________________________________________________________________";

			++offsetY;
			int counter = 0;

			for (unsigned int i = 0; i < mySpells.size(); ++i)
			{
				short currentOffsetX = static_cast<short>(offsetX + 46 * counter);

				mySpells[i].PrintSpell(i + 1, currentOffsetX, offsetY, 0, FOREGROUND_INTENSITY);

				++counter;

				if ((counter + 1) % 3 == 0)
				{
					counter = 0;
					offsetY += 10;
				}
			}

			gotoXY(5, 36);
			std::cout << "B. Back";

			gotoXY(20, 36);
			std::cout << "Select spell to pick up: ";

			input = GetCharInput();

			unsigned int index = static_cast<int>(input - '0') - 1;

			if (index >= 0 && index < mySpells.size())
			{
				aPlayer.AddSpell(mySpells[index]);
				mySpells.erase(mySpells.begin() + index);
			}

			aPlayer.CheckCommand(input);

		} while (input != 'b' && input != 'B' && mySpells.size() > 0);
	}
}

bool Chest::IsChestBroken()
{
	return myChestIsBroken;
}

bool Chest::IsChestOpen()
{
	return myChestIsOpen;
}

void Chest::OpenChest(Player &aPlayer)
{
	if (myChestIsOpen == false && myChestIsBroken == false)
	{
		UnlockChest(aPlayer);
	}

	if (myChestIsOpen == true)
	{
		DisplayChestContents(aPlayer);
	}
	else if (myChestIsBroken == true)
	{
		PrintDialog("The chest is broken, you can't get into it any more.\n\n");
		std::getchar();
	}
}

void Chest::GenerateContents(Player &aPlayer)
{
	int maxNumItems = myMaxNumItems;
	int numOfItems = randBetween(1, maxNumItems);

	ItemFactory itemFactory;
	for (int i = 0; i < numOfItems; i++)
	{
		myItems.push_back(itemFactory.CreateItem(aPlayer));
	}

	int numOfSpells = randBetween(0, myMaxNumSpells);
	SpellFactory spellFactory;
	for (int i = 0; i < numOfSpells; i++)
	{
		mySpells.push_back(spellFactory.CreateSpell(aPlayer));
	}
}

void Chest::UnlockChest(Player &aPlayer)
{
	char choice;

	do
	{
		std::string outPut = "You can open the chest by either breaking or picking the lock. What would you like to do?\n\n1. Break lock\n2. Pick lock\nB. Back\n\n";
		PrintDialog(outPut);

		choice = GetCharInput();

		switch (choice)
		{
		case '1':
			BreakChest(aPlayer);
			aPlayer.DecrementStamina(2);
			break;

		case '2':
			PickChest(aPlayer);
			aPlayer.DecrementStamina(1);
			break;

		default:
			break;
		}
	} while (choice != 'b' && choice != 'B' && myChestIsBroken == false && myChestIsOpen == false);

}

int Chest::GetChestDifficulty()
{
	return myChestDifficulty;
}

std::string Chest::GetStatusString()
{
	if (myChestIsOpen)
	{
		return "Open";
	}
	else if (myChestIsBroken)
	{
		return "Broken";
	}
	else
	{
		return "Locked";
	}
}