#include "stdafx.h"
#include "EnemyFactory.h"


EnemyFactory::EnemyFactory()
{
}


EnemyFactory::~EnemyFactory()
{
}

Enemy EnemyFactory::CreateEnemy(Player &aPlayer)
{
	Enemy enemy;
	enemy.SetName("Skeleton");
	enemy.SetAttributes(aPlayer);

	return enemy;
}