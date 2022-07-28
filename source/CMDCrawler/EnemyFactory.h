#pragma once
#include "Enemy.h"
#include "Player.h"
class EnemyFactory
{
public:
	EnemyFactory();
	~EnemyFactory();

	Enemy CreateEnemy(Player &aPlayer);
};

