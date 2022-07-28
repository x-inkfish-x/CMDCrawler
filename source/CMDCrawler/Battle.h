#pragma once
#include <vector>
#include "Player.h"
#include "Enemy.h"
class Battle
{
public:
	Battle(Player &aPlayer);
	~Battle();

private:
	void StartBattle(Player &aPlayer);
	
	bool EnemiesRemain();
	void AttackEnemies(Player &aPlayer, int anEnemyToAttack);
	void EnemiesAttack(Player &aPlayer);

	void PrintPeripheral(Player &aPlayer);
	void PrintBattleBackground();
	void PrintEnemySprite(int anOffsetX, int anOffsetY);
	void PrintEnemies();
	void PrintEnemyData(int anIndex, int anOffsetX, int anOffsetY);
	void GenerateDrops(Player &aPlayer);

	std::vector<Enemy> myEnemies;
};

