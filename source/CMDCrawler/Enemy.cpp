#include "stdafx.h"
#include "Enemy.h"
#include "Utilities.h"


Enemy::Enemy()
{
	myAccuracy = 0;
	myAttack = 0;
	myHealth = 0;
	myEvasion = 0;

	myName = "ERROR";
}


Enemy::~Enemy()
{
}

int Enemy::GetHealth()
{
	return myHealth;
}

int Enemy::GetAttack()
{
	return myAttack;
}

int Enemy::GetEvasion()
{
	return myEvasion;
}

int Enemy::GetAccuracy()
{
	return myAccuracy;
}

void Enemy::ReduceHealth(Player &aPlayer)
{
	myHealth -= aPlayer.GetAttackStrength();
}

std::string Enemy::GetName()
{
	return myName;
}

void Enemy::SetName(std::string aName)
{
	myName = aName;
}

void Enemy::SetAttributes(Player &aPlayer)
{
	int attributeModifier = (1 + aPlayer.GetBattlesEntered() / 5);
	myAccuracy = randBetween(4, 20 * attributeModifier);
	myAttack = randBetween(5, 15 * attributeModifier * 2);
	myHealth = randBetween(50, 60 * attributeModifier * 2);
	myEvasion = randBetween(10, 20 * attributeModifier);
}