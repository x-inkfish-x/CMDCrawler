#include "stdafx.h"
#include "SpellFactory.h"


SpellFactory::SpellFactory()
{
}


SpellFactory::~SpellFactory()
{
}

Spell SpellFactory::CreateSpell(Player &aPlayer)
{
	return Spell(aPlayer.GetBattlesEntered());
}