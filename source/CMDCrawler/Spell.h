#pragma once
#include <vector>
#include <string>
#include "Utilities.h"

class Player;

class Spell
{
public:
	Spell(int aLevel);
	~Spell();

	int GetModifier(AttributeTypes anAttribute);
	std::string GetSpellName();
	int GetDurability();
	void WearSpell();
	void PrintSpell(int anIndex, short anOffsetX, short anOffsetY, short aBackgroundColor, short aTextColor);
	char GetHotKey();
	void SetHotKey(Player &aPlayer);
	
private:
	std::vector<int> myAttributeModifiers;
	char myHotKey;
	int myDurability;
	std::string myName;

	std::string GenerateSpellName();
	bool IsValidHotKey(char aHotKey, Player &aPlayer);
};

