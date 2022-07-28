#pragma once
#include "Spell.h"
#include "Player.h"
class SpellFactory
{
public:
	SpellFactory();
	~SpellFactory();

	Spell CreateSpell(Player &aPlayer);
};

