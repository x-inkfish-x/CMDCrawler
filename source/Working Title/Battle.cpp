#include "stdafx.h"
#include <iostream>
#include "Battle.h"
#include "Utilities.h"
#include "EnemyFactory.h"
#include "ItemFactory.h"


Battle::Battle(Player &aPlayer)
{
	EnemyFactory enemyFactory;

	aPlayer.IncrementBattlesEntered();

	int numberOfEnemies = randBetween(1, 3);
	
	for (int i = 0; i < numberOfEnemies; ++i)
	{
		myEnemies.push_back(enemyFactory.CreateEnemy(aPlayer));
	}
	
	StartBattle(aPlayer);
}


Battle::~Battle()
{
}

void Battle::StartBattle(Player &aPlayer)
{
	
	do
	{
		PrintPeripheral(aPlayer);

		std::string outPut = "You are facing " + std::to_string(myEnemies.size()) + " enemies!\n\n";

		for (unsigned int i = 0; i < myEnemies.size(); i++)
		{
			outPut += std::to_string(i + 1) + ": Enemy, " + std::to_string(myEnemies[i].GetHealth()) + " HP\n";
		}

		outPut += "\n\nWhich one would you like to attack?\n";
		//PrintDialog(outPut);

		char enemyToAttack = GetCharInput();
		
		unsigned int index = static_cast<int>(enemyToAttack - '0') - 1;

		if (index >= 0 && index < myEnemies.size())
		{
			AttackEnemies(aPlayer, index);

			if (myEnemies.size() > 0)
			{
				EnemiesAttack(aPlayer);
			}
		}

		aPlayer.CheckCommand(enemyToAttack);
	} while (EnemiesRemain() == true && aPlayer.GetHealth() > 0);
}

bool Battle::EnemiesRemain()
{
	if (myEnemies.size() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Battle::AttackEnemies(Player &aPlayer, int anEnemyToAttack)
{
	std::string outPut = "You attacked enemy " + std::to_string(anEnemyToAttack + 1) + "!\n";

	myEnemies[anEnemyToAttack].ReduceHealth(aPlayer);

	if (!(myEnemies[anEnemyToAttack].GetHealth() > 0))
	{
		outPut += "Enemy died!";
	}
	PrintDialog(outPut);
	std::getchar();
	if (!(myEnemies[anEnemyToAttack].GetHealth() > 0))
	{
		myEnemies.erase(myEnemies.begin() + anEnemyToAttack);
		GenerateDrops(aPlayer);
	}

	aPlayer.Update();
}

void Battle::GenerateDrops(Player &aPlayer)
{
	
	int numOfItems = randBetween(0, 2);
	
	if (numOfItems > 0)
	{
		std::vector<Item> items;
		ItemFactory itemFactory;
		for (int i = 0; i < numOfItems; ++i)
		{
			items.push_back(itemFactory.CreateItem(aPlayer));
		}

		char input;

		do
		{
			PrintBackGround();

			std::string output;
			short offsetX = 3;
			short offsetY = 3;
			gotoXY(offsetX, offsetY);
			SetConsoleTextAttribute(hstdout, FOREGROUND_INTENSITY);
			std::cout << "Items";

			gotoXY(offsetX + 40, offsetY);
			std::cout << "Capacity: " << aPlayer.GetCapacity();

			++offsetY;
			gotoXY(2, offsetY);
			std::cout << "________________________________________________________________________________________";

			++offsetY;
			int counter = 0;

			for (unsigned int i = 0; i < items.size(); ++i)
			{
				short currentOffsetX = static_cast<short>(offsetX + 46 * counter);

				items[i].PrintItem(i + 1, currentOffsetX, offsetY, 0, FOREGROUND_INTENSITY);

				++counter;

				if ((counter + 1) % 3 == 0)
				{
					counter = 0;
					offsetY += 10;
				}
			}

			gotoXY(5, 36);
			std::cout << "B. Back";

			gotoXY(20, 36);
			std::cout << "Select item to pick up: ";
			input = GetCharInput();

			unsigned int index = static_cast<int>(input - '0') - 1;

			if (index >= 0 && index < items.size())
			{
				if (aPlayer.GetInventory().AddItemToInventory(items[index], aPlayer) == true)
				{
					items.erase(items.begin() + index);
				}
			}

			aPlayer.CheckCommand(input);
		} while (input != 'b' && input != 'B' && items.size() > 0);
	}
	PrintPeripheral(aPlayer);
}

void Battle::EnemiesAttack(Player &aPlayer)
{
	std::string outPut = "Enemies attack!!\n\n";
	for (std::vector<Enemy>::iterator it = myEnemies.begin(); it != myEnemies.end() && aPlayer.GetHealth() > 0; it++)
	{
		if (randBetween(0, 99) >= 1)
		{
			int damage = it->GetAttack();
			aPlayer.TakeDamage(damage);
			outPut += "You took " + std::to_string(damage) + " points of damage!\n";
		}
	}
	PrintDialog(outPut);
	std::getchar();
}

void Battle::PrintPeripheral(Player &aPlayer)
{
	PrintBattleBackground();
	PrintEnemies();
	PrintFrame();
	aPlayer.PrintStatusBar();
}

void Battle::PrintBattleBackground()
{
	std::string room =
		std::string(
		"  ---//////////////////////////////////////////////////////////////////////////////////---  \n") +
		"  ///---////////////////////////////////////////////////////////////////////////////---///  \n" +
		"  //////---//////////////////////////////////////////////////////////////////////---//////  \n" +
		"  /////////---////////////////////////////////////////////////////////////////---/////////  \n" +
		"  ////////////---//////////////////////////////////////////////////////////---////////////  \n" +
		"  ///////////////---////////////////////////////////////////////////////---///////////////  \n" +
		"  //////////////////---//////////////////////////////////////////////---//////////////////  \n" +
		"  /////////////////////----------------------------------------------/////////////////////  \n" +
		"  /////////////////////-////////////////////////////////////////////-/////////////////////  \n" +
		"  /////////////////////-////////////////////////////////////////////-/////////////////////  \n" +
		"  /////////////////////-////////////////////////////////////////////-/////////////////////  \n" +
		"  /////////////////////-////////////////////////////////////////////-/////////////////////  \n" +
		"  /////////////////////-////////////////////////////////////////////-/////////////////////  \n" +
		"  /////////////////////-////////////////////////////////////////////-/////////////////////  \n" +
		"  /////////////////////-////////////////////////////////////////////-/////////////////////  \n" +
		"  /////////////////////-////////////////////////////////////////////-/////////////////////  \n" +
		"  /////////////////////-////////////////////////////////////////////-/////////////////////  \n" +
		"  /////////////////////-////////////////////////////////////////////-/////////////////////  \n" +
		"  /////////////////////-////////////////////////////////////////////-/////////////////////  \n" +
		"  /////////////////////-////////////////////////////////////////////-/////////////////////  \n" +
		"  /////////////////////-////////////////////////////////////////////-/////////////////////  \n" +
		"  /////////////////////-////////////////////////////////////////////-/////////////////////  \n" +
		"  /////////////////////-////////////////////////////////////////////-/////////////////////  \n" +
		"  /////////////////////-////////////////////////////////////////////-/////////////////////  \n" +
		"  /////////////////////-////////////////////////////////////////////-/////////////////////  \n" +
		"  /////////////////////-////////////////////////////////////////////-/////////////////////  \n" +
		"  /////////////////////-////////////////////////////////////////////-/////////////////////  \n" +
		"  /////////////////////----------------------------------------------/////////////////////  \n" +
		"  //////////////////---##############################################---//////////////////  \n" +
		"  ///////////////---####################################################---///////////////  \n" +
		"  ////////////---#########========================================#########---////////////  \n" +
		"  /////////---#########==============================================#########---/////////  \n" +
		"  //////---#########====================================================#########---//////  \n" +
		"  ///---#########==========================================================#########---///  \n" +
		"  ---#########================================================================#########---  \n";

	gotoXY(static_cast<short>(0), static_cast<short>(2));

	for (unsigned int i = 0; i < room.size(); i++)
	{
		PrintPoint(room[i]);
	}
}

void Battle::PrintEnemies()
{
	for (unsigned int i = 0; i < myEnemies.size(); ++i)
	{
		int offsetX;
		int offsetY;
		switch (i)
		{
		case 0:
			offsetX = 5;
			offsetY = 15;
			break;

		case 1:
			offsetX = 35;
			offsetY = 15;
			break;

		case 2:
			offsetX = 65;
			offsetY = 15;
			break;

		default:
			offsetX = 0;
			offsetY = 0;
			break;

		}
		
		PrintEnemySprite(offsetX, offsetY);
		PrintEnemyData(i, offsetX, offsetY);
	}
}

void Battle::PrintEnemyData(int anIndex, int anOffsetX, int anOffsetY)
{

	anOffsetX -= 2;
	anOffsetY -= 13;
	short offsetX = static_cast<short>(anOffsetX);
	short offsetY = static_cast<short>(anOffsetY);

	std::string tablet = std::string("") +
		" ????????????????????????\n"
		"?++++++++++++++++++++++++?\n"
		"?+//////////////////////+?\n"
		"?+//////////////////////+?\n"
		"?+//////////////////////+?\n"
		"?+//////////////////////+?\n"
		"?+//////////////////////+?\n"
		"?+//////////////////////+?\n"
		"?+//////////////////////+?\n"
		"?+//////////////////////+?\n"
		"?++++++++++++++++++++++++?\n"
		" ????????????????????????\n";

	gotoXY(offsetX, offsetY);

	for (unsigned int i = 0; i < tablet.size(); i++)
	{
		if (tablet[i] == '\n')
		{
			offsetY += 1;
			gotoXY(static_cast<short>(offsetX), static_cast<short>(offsetY));
		}
		else
		{
			PrintPoint(tablet[i]);
		}
	}

	SetConsoleTextAttribute(hstdout, static_cast<short>(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED));

	offsetX = static_cast<short>(anOffsetX + 3);
	offsetY = static_cast<short>(anOffsetY + 2);

	gotoXY(offsetX + 5, offsetY);

	std::string output = std::to_string(anIndex + 1) + "\n\n" + myEnemies[anIndex].GetName() + "\n\n" +
		"Health: " + std::to_string(myEnemies[anIndex].GetHealth()) +
		"\nAttack: " + std::to_string(myEnemies[anIndex].GetAttack());

	int currentLinePosition = 0;
	int dialogWindowWidth = 20;

	for (unsigned int i = 0; i < output.size(); ++i)
	{
		char currentChar = output[i];

		if (currentChar == '\n')
		{
			currentLinePosition = 0;
		}
		else
		{
			std::cout << currentChar;
			currentLinePosition += 1;
		}

		if (currentLinePosition % (dialogWindowWidth + 1) == 0)
		{
			offsetY += 1;
			gotoXY(offsetX, offsetY);
			currentLinePosition = 0;
		}
	}
}

void Battle::PrintEnemySprite(int anOffsetX, int anOffsetY)
{
	short offsetX = static_cast<short>(anOffsetX);
	short offsetY = static_cast<short>(anOffsetY);

	std::string skelleton =
		std::string("") +
		"            ???????\n"
		"          ??//////+??\n"
		"        ??+//////+///?\n"
		"       ?++/+/??////??/?\n"
		"       ?+/+//??////??/?\n"
		"       ?+///////??///?\n"
		"        ?+/+?///++//+?\n"
		"         ??+?/?/?/?/?\n"
		"         ?+/+???????\n"
		"         ?////+?   ???\n"
		"    ?????+/+/+/????@&?\n"
		"   ?/?//////+//??&@??\n"
		"  ?+?++++++++??@&??+?\n"
		"??/??//////??@&??///?\n"
		"?+?  ?+++??&@??+++??\n"
		"??+? ????@&??? ???/?\n"
		"  ?/?*?&@???/?   ?/?\n"
		"   ?/?*????????????/?\n"
		"  ?/+/?$?///+///?/??/?\n"
		"   ???+??+/++/+?/+?++/?";

	gotoXY(offsetX, offsetY);

	for (unsigned int i = 0; i < skelleton.size(); i++)
	{
		if (skelleton[i] == '\n')
		{
			offsetY += 1;
			gotoXY(static_cast<short>(offsetX), static_cast<short>(offsetY));
		}
		else
		{
			PrintPoint(skelleton[i]);
		}
	}
}