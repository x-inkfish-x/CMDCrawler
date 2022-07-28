#pragma once
#include "Item.h"

class Player;
class Inventory
{
public:
	Inventory();

	bool AddItemToInventory(Item &aItem, Player &aPlayer);
	int GetInventoryWeight();
	void DisplayItems(Player &aPlayer);

private:
	std::vector<Item> myItems;
	void DisplayItemOptions(int anIndex, Player &aPlayer);
	unsigned int myMaxNumberOfItems = 20;

	void PrintTablet(short anOffsetX, short anOffsetY);
	
	void PrintItems(int aPage, Player &aPlayer);
};

