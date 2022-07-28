#pragma once
#include <vector>
#include "Spell.h"

class Player;

class Spellbook
{
public:
	Spellbook();

	void DisplaySpells(Player &aPlayer);
	void AddSpell(Spell &aSpell);
	const std::vector<Spell> &GetSpells();
	void UseHotkeyedSpell(char aHotkey, Player &aPlayer);

private:
	std::vector<Spell> mySpells;
	int myMaxNumberOfSpells = 20;

	void SpellOptions(int anIndex, Player &aPlayer);
	void PrintTablet(short anOffsetX, short anOffsetY);

	void PrintSpells(int aPage);
};

