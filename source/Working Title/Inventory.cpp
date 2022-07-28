#include "stdafx.h"
#include <iostream>
#include "Inventory.h"
#include "Player.h"
#include "ItemFactory.h"



Inventory::Inventory()
{
	
}

bool Inventory::AddItemToInventory(Item &aItem, Player &aPlayer)
{
	if (aItem.GetWeight() < aPlayer.GetCapacity() && myItems.size() <= myMaxNumberOfItems)
	{
		if (aPlayer.GetEquipment()[static_cast<int>(aItem.GetItemType())].GetItemType() == ItemTypes::LAST)
		{
			aPlayer.EquipItem(aItem, aItem.GetItemType());
		}
		else
		{
			Item &equipedItem = aPlayer.GetEquipment()[static_cast<int>(aItem.GetItemType())];

			int newStrength = aItem.GetModifier(AttributeTypes::Strength);
			int equipedStrength = equipedItem.GetModifier(AttributeTypes::Strength);

			if (equipedStrength < newStrength)
			{
				myItems.push_back(equipedItem);
				aPlayer.EquipItem(aItem, aItem.GetItemType());
			}
			else
			{
				myItems.push_back(aItem);
			}
		}
		return true;
	}
	else
	{
		std::string output = "You cannot carry this";
		PrintDialog(output);
		std::getchar();
		return false;
	}
}

void Inventory::DisplayItems(Player &aPlayer)
{
	char input;
	int page = 0;
	do
	{
		PrintBackGround();

		PrintItems(page, aPlayer);

		input = GetCharInput();

		unsigned int index = static_cast<int>(input - '0') - 1;

		if (index >= 0 && index + 6 * page < myItems.size())
		{
			int realIndex = index + 6 * page;
			DisplayItemOptions(realIndex, aPlayer);
			//myItems.erase(myItems.begin() + realIndex);
		}

		switch (input)
		{
		case 'p':
		case 'P':
			if (!(page - 1 < 0))
			{
				--page;
			}
			break;
		case 'n':
		case 'N':
			if (!(static_cast<unsigned int>(page + 1) > myItems.size() / 6))
			{
				++page;
			}
			break;
		}
	} while (input != 'b' && input != 'B');
}

void Inventory::PrintItems(int aPage, Player &aPlayer)
{
	short offsetX = 3;
	short offsetY = 3;
	gotoXY(offsetX, offsetY);
	SetConsoleTextAttribute(hstdout, FOREGROUND_INTENSITY);
	std::cout << "Items";

	gotoXY(offsetX + 20, offsetY);
	std::cout << "Capacity: " << aPlayer.GetCapacity();

	gotoXY(offsetX + 80, offsetY);
	std::cout << aPage + 1 << "/" << myItems.size() / 7 + 1;

	++offsetY;
	gotoXY(2, offsetY);
	std::cout << "________________________________________________________________________________________";

	++offsetY;
	int counter = 0;

	unsigned int startIndex = aPage * 6;

	for (unsigned int i = 0; i < 6 &&
		i + aPage * 6 < myItems.size(); ++i)
	{
		short currentOffsetX = static_cast<short>(offsetX + 46 * counter);

		myItems[startIndex].PrintItem(i + 1, currentOffsetX, offsetY, 0, FOREGROUND_INTENSITY);

		++startIndex;
		++counter;

		if ((counter + 1) % 3 == 0)
		{
			counter = 0;
			offsetY += 10;
		}
	}

	gotoXY(5, 36);
	std::cout << "B. Back";

	gotoXY(59, 36);
	std::cout << "P. Previous page / N. Next page";

	gotoXY(20, 36);
	std::cout << "Select an item:  ";
}

int Inventory::GetInventoryWeight()
{
	int weight = 0;
	for (std::vector<Item>::iterator it = myItems.begin(); it != myItems.end(); it++)
	{
		weight += (*it).GetWeight();
	}

	return weight;
}

void Inventory::DisplayItemOptions(int anIndex, Player &aPlayer)
{
	Item &selectedItem = myItems[anIndex];
	Item &equipment = aPlayer.GetEquipment()[static_cast<int>(selectedItem.GetItemType())];
	
	char input;

	do
	{
		PrintTablet(2, 8);
		PrintTablet(46, 8);

		short backgroundColor = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
		SetConsoleTextAttribute(hstdout, backgroundColor | FOREGROUND_INTENSITY);
		gotoXY(10, 10);
		std::cout << "Selected Item";
		gotoXY(54, 10);
		std::cout << "Equiped Item";
		selectedItem.PrintItem(1, 4, 12, backgroundColor, 0);

		short offsetX = 32;
		short offsetY = 14;
		gotoXY(offsetX, offsetY);

		for (int i = 0; i < static_cast<int>(AttributeTypes::LAST); ++i)
		{
			if (selectedItem.GetModifier(static_cast<AttributeTypes>(i)))
			{
				int resultModifier = selectedItem.GetModifier(static_cast<AttributeTypes>(i)) - equipment.GetModifier(static_cast<AttributeTypes>(i));

				char sign;

				if (resultModifier < 0)
				{
					sign = '-';
					resultModifier *= (-1);
					SetConsoleTextAttribute(hstdout, backgroundColor | FOREGROUND_RED);
				}
				else
				{
					sign = '+';
					SetConsoleTextAttribute(hstdout, backgroundColor | FOREGROUND_GREEN);
				}

				std::cout << "(" << sign << resultModifier << ")";
				++offsetY;
				gotoXY(offsetX, offsetY);
			}
		}

		equipment.PrintItem(2, 48, 12, backgroundColor, 0);

		offsetX = 2;
		offsetY = 34;
		gotoXY(offsetX, offsetY);

		SetConsoleTextAttribute(hstdout, 0 | FOREGROUND_INTENSITY);

		std::cout << "________________________________________________________________________________________";

		offsetX = 2;
		offsetY = 36;
		gotoXY(offsetX, offsetY);

		std::string output = "????????????????????????????????????????????????????????????????????????????????????????";

		for (unsigned int i = 0; i < output.size(); ++i)
		{
			if (output[i] == '\n')
			{
				++offsetY;
				gotoXY(offsetX, offsetY);
			}
			else
			{
				PrintPoint(output[i]);
			}
		}


		offsetX = 2;
		offsetY = 36;
		gotoXY(offsetX, offsetY);
		SetConsoleTextAttribute(hstdout, 0 | FOREGROUND_INTENSITY);
		std::cout << " E. Equip selected item      T. Throw away item       B. Back      ";

		input = GetCharInput();

		switch (input)
		{
		case 'e':
		case 'E':
			selectedItem = aPlayer.EquipItem(selectedItem, selectedItem.GetItemType());
			return;

		case 't':
		case 'T':
			myItems.erase(myItems.begin() + anIndex);
			return;
		}
	} while (input != 'b' && input != 'B');
}

void Inventory::PrintTablet(short anOffsetX, short anOffsetY)
{
	std::string outPut = std::string("") +
		"????????????????????????????????????????????\n" +
		"?++++++++++++++++++++++++++++++++++++++++++?\n" +
		"?+////////////////////////////////////////+?\n" +
		"?+////////////////////////////////////////+?\n" +
		"?+////////////////////////////////////////+?\n" +
		"?+////////////////////////////////////////+?\n" +
		"?+////////////////////////////////////////+?\n" +
		"?+////////////////////////////////////////+?\n" +
		"?+////////////////////////////////////////+?\n" +
		"?+////////////////////////////////////////+?\n" +
		"?+////////////////////////////////////////+?\n" +
		"?+////////////////////////////////////////+?\n" +
		"?+////////////////////////////////////////+?\n" +
		"?+////////////////////////////////////////+?\n" +
		"?+////////////////////////////////////////+?\n" +
		"?+////////////////////////////////////////+?\n" +
		"?++++++++++++++++++++++++++++++++++++++++++?\n" +
		"????????????????????????????????????????????\n";

	gotoXY(anOffsetX, anOffsetY);

	for (unsigned int i = 0; i < outPut.size(); ++i)
	{
		char outChar = outPut[i];

		if (outChar == '\n')
		{
			++anOffsetY;
			gotoXY(anOffsetX, anOffsetY);
		}
		else
		{
			PrintPoint(outChar);
		}
	}

}