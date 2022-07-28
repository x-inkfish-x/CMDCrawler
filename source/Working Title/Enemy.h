#pragma once
#include "Player.h"

class Enemy
{
public:
	Enemy();
	~Enemy();

	int GetHealth();
	void ReduceHealth(Player &aPlayer);
	int GetEvasion();
	int GetAccuracy();
	int GetAttack();

	void SetAttributes(Player &aPlayer);

	std::string GetName();
	void SetName(std::string aName);

private:
	int myHealth;
	int myEvasion;
	int myAccuracy;
	int myAttack;

	std::string myName;
};

