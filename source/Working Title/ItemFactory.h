#pragma once
#include <vector>
#include "Item.h"
#include "Player.h"

class ItemFactory
{
public:
	ItemFactory();
	~ItemFactory();

	Item CreateItem(Player &aPlayer);

private:
	std::vector<int> GetItemStats(int aLevel);
	std::string GetItemTypeString(const Item &anItem);
	std::string GetWeaponTypeString(WeaponTypes aWeaponType);
	ItemTypes GetItemType();
	std::string GetItemName(const Item &anItem);
	int GetItemWeight(int aLevel);
};

