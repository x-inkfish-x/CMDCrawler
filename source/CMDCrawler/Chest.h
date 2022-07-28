#pragma once
#include <vector>
#include "Item.h"
#include "Spell.h"
#include "Player.h"

class Chest
{
public:
	Chest(Player &aPlayer);
	~Chest();

	void OpenChest(Player &aPlayer);
	bool IsChestBroken();
	bool IsChestOpen();
	int GetChestDifficulty();
	std::string GetStatusString();

private:
	int myChestDifficulty;
	bool myChestIsOpen = false;
	bool myChestIsBroken = false;
	int myMaxNumItems = 4;
	int myMaxNumSpells = 4;

	std::vector<Item> myItems;
	std::vector<Spell> mySpells;

	void BreakChest(Player &aPlayer);
	void PickChest(Player &aPlayer);
	void GenerateContents(Player &aPlayer);
	void UnlockChest(Player &aPlayer);
	void DisplayChestContents(Player &aPlayer);
	void DisplayItems(Player &aPlayer);
	void DisplaySpells(Player &aPlayer);
};