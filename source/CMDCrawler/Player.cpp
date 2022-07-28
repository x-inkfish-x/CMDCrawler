#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <iomanip>
#include "Player.h"
#include "Utilities.h"
#include <cctype>




Player::Player()
{
	myPlayerPos = std::vector<int>(2);
	

	//todo: change these back to random values
	myBaseCondition = randBetween(5, 15);
	myBaseDexterity = randBetween(5, 15);
	myBaseIntelligence = randBetween(5, 15);
	myBaseStrength = randBetween(10, 20);
	myLastPosX = 0;
	myLastPosY = 0;

	myEquitment = std::vector<Item>(static_cast<int>(ItemTypes::LAST));

	myStaminaLoss = 0;
}

Player::~Player()
{
}

void Player::Update()
{
	++myStaminaLoss;
	WearSpells();
}

int Player::GetAttackStrength()
{
	return GetStrength() * 5 + GetDexterity() + GetAttributeModification(AttributeTypes::AttackStrength);
}

int Player::GetCapacity()
{
	return GetStrength() * 5 + GetAttributeModification(AttributeTypes::Capacity) - myInventory.GetInventoryWeight() - GetEquipmentWeight();
}

int Player::GetCondition()
{
	return myBaseCondition + GetAttributeModification(AttributeTypes::Constitution);
}

int Player::GetDexterity()
{
	return myBaseDexterity + GetAttributeModification(AttributeTypes::Dexterity);
}

int Player::GetHealth()
{
	return GetMaxHealth() - myDamage;
}

int Player::GetMaxHealth()
{
	return GetStrength() * 20 + GetCondition() * 10 + GetAttributeModification(AttributeTypes::MaxHealth);
}

int Player::GetIntelligence()
{
	return myBaseIntelligence + GetAttributeModification(AttributeTypes::Intelligence);
}

int Player::GetMagicStrength()
{
	return GetDexterity() * 3 + GetIntelligence() * 10 + GetAttributeModification(AttributeTypes::MagicStrength);
}

int Player::GetResiliance()
{
	return GetStrength() + GetStamina() + GetAttributeModification(AttributeTypes::Resiliance);
}

int Player::GetSpeed()
{
	return (GetCondition() * 2 + GetDexterity()) / 2 + GetAttributeModification(AttributeTypes::Speed);
}

int Player::GetStamina()
{
	return GetCondition() * 5 + GetStrength() * 5 + GetAttributeModification(AttributeTypes::Stamina) - myStaminaLoss;
}

int Player::GetStrength()
{
	return myBaseStrength + GetAttributeModification(AttributeTypes::Strength);
}

std::string Player::GetName()
{
	return myName;
}

bool Player::SetName()
{
	std::getline(std::cin, myName);

	if (myName.size() == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

int Player::GetAttributeModification(AttributeTypes anAttribute)
{
	int modifier = 0;

	for (std::vector<Item>::iterator it = myEquitment.begin(); it != myEquitment.end(); it++)
	{
		modifier += (*it).GetModifier(anAttribute);
	}

	for (std::vector<Spell>::iterator it = myActiveSpells.begin(); it != myActiveSpells.end(); it++)
	{
		modifier += (*it).GetModifier(anAttribute);
	}

	return modifier;
}

Inventory &Player::GetInventory()
{
	return myInventory;
}

void Player::WearSpells()
{
	for (std::vector<Spell>::iterator it = myActiveSpells.begin(); it != myActiveSpells.end();)
	{
		
		(*it).WearSpell();

		if ((*it).GetDurability() < 1)
		{
			it = myActiveSpells.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void Player::AddSpell(Spell &aSpell)
{
	mySpellbook.AddSpell(aSpell);
}

void Player::SetPlayerPos(const std::vector<int> newPos)
{
	myLastPosX = myPlayerPos[0];
	myLastPosY = myPlayerPos[1];
	myPlayerPos = newPos;
}

int Player::GetPlayerPosX() const
{
	return myPlayerPos[0];
}

int Player::GetPlayerPosY() const
{
	return myPlayerPos[1];
}

int Player::GetLastPosX()
{
	return myLastPosX;
}

int Player::GetLastPosY()
{
	return myLastPosY;
}

void Player::TakeDamage(int aDamage)
{
	myDamage += aDamage;
}

Directions Player::GetFacingDirection()
{
	std::vector<int> returnVector = { myPlayerPos[static_cast<int>(Axees::X)] - myLastPosX, myPlayerPos[static_cast<int>(Axees::Y)] - myLastPosY };

	if (returnVector[static_cast<int>(Axees::X)] > 0)
	{
		return Directions::Right;
	}
	if (returnVector[static_cast<int>(Axees::X)] < 0)
	{
		return Directions::Left;
	}

	if (returnVector[static_cast<int>(Axees::Y)] < 0)
	{
		return Directions::Up;
	}

	return Directions::Down;
}

int Player::GetRoomEntered()
{
	return myRoomsEntered;
}

int Player::GetBattlesEntered()
{
	return myBattles;
}

void Player::IncrementBattlesEntered()
{
	myBattles++;
}

void Player::IncrementRoomsEntered()
{
	myRoomsEntered++;
}

std::vector<int> Player::GetPlayerPos()
{
	return myPlayerPos;
}

void Player::PrintStatusBar()
{
	short offsetX = 2;
	short offsetY = 31;

	std::string statusBar = std::string(
		"????????????????\n") +
		"++++++++++++++++????\n" +
		"++++++++++++++++++++???\n"
		"+++++++++++++++++++++++?\n" +
		"++++++++++++++++++++++++????????????????????????????????????????????????????????????????\n" +
		"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

	gotoXY(offsetX, offsetY);

	for (unsigned int i = 0; i < statusBar.size(); ++i)
	{
		if (statusBar[i] == '\n')
		{
			++offsetY;
			gotoXY(offsetX, offsetY);
		}
		else
		{
			PrintPoint(statusBar[i]);
		}
	}

	SetConsoleTextAttribute(hstdout, 0 | BACKGROUND_INTENSITY);

	std::string currentHealth = std::to_string(GetHealth()) + "/";
	std::string maxHealth = std::to_string(GetMaxHealth());

	offsetX = 3;
	offsetY = 33;

	gotoXY(offsetX, offsetY);

	std::cout << "HP:";
	std::cout << std::right << std::setw(10) << currentHealth;
	++offsetY;
	offsetX = 6;
	gotoXY(offsetX, offsetY);
	std::cout << std::right << std::setw(9) << maxHealth;

	offsetX = 3;
	offsetY += 2;
	gotoXY(offsetX, offsetY);
	std::cout << "Stamina:";
	std::cout << std::right << std::setw(9) << GetStamina();

	offsetX = 26;
	gotoXY(offsetX, offsetY);
	std::cout << "I. Inventory   E. Equipement   S. Stats            ";

	InputBox();
}

void Player::SetWorldSize(int aWidth, int aHeight)
{
	myWorldWidthX = aWidth;
	myWorldHeightY = aHeight;
}

int Player::GetWorldSizeX()
{
	return myWorldWidthX;
}

int Player::GetWorldSizeY()
{
	return myWorldHeightY;
}

void Player::CheckCommand(char aCommand)
{
	switch (aCommand)
	{
	case 'i':
	case 'I':
		DisplayInventory();
		break;

	case 's':
	case 'S':
		DisplayStats();
		break;

	case 'e':
	case 'E':
		PrintEquipment();
		break;
	default:
		break;
	}

	for (std::vector<char>::iterator it = mySpellHotKeys.begin(); it != mySpellHotKeys.end(); ++it)
	{
		aCommand = static_cast<char>(std::toupper(aCommand));
		if (*it == aCommand)
		{
			mySpellbook.UseHotkeyedSpell(aCommand, *this);
			break;
		}
	}
}

void Player::DisplayInventory()
{
	char input;
	
	SetConsoleTextAttribute(hstdout, FOREGROUND_INTENSITY);

	do
	{
		PrintBackGround();
		std::string output = "Inventory\n\n1. Equipment\n2. Spellbook\nB.Back";
		PrintDialog(output);

		input = GetCharInput();
		
		switch (input)
		{
		case '1':
			myInventory.DisplayItems(*this);
			break;

		case '2':
			mySpellbook.DisplaySpells(*this);
			break;
		default:
			break;
		}

	} while (input != 'b' && input != 'B');
}

void Player::UseSpell(Spell &aSpell)
{
	std::string outPut = std::string("You cast ") + aSpell.GetSpellName() + " on yourself!";
	PrintDialog(outPut);
	PauseGame();
	myActiveSpells.push_back(aSpell);
}

void Player::DecrementStamina(unsigned int aDecrement)
{
	myStaminaLoss += aDecrement;
}

void Player::DisplayStats()
{
	PrintFrame();
	PrintBackGround();

	SetConsoleTextAttribute(hstdout, FOREGROUND_INTENSITY);// FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	short offsetX = 3;
	short offsetY = 3;

	gotoXY(offsetX, offsetY);

	std::cout << "Stats";

	offsetX = 20;
	offsetY = 3;
	gotoXY(offsetX, offsetY);

	std::cout << "Name: " << myName;

	offsetX = 65;
	offsetY = 3;
	gotoXY(offsetX, offsetY);
	std::cout << "HP: " << GetHealth() << "/" << GetMaxHealth();

	offsetX = 2;
	offsetY = 4;
	gotoXY(offsetX, offsetY);
	std::cout << "________________________________________________________________________________________";
	
	offsetX = 3;
	offsetY = 6;
	

	short count = 0;

	for (int i = 0; i < static_cast<int>(AttributeTypes::LAST); ++i)
	{
		if (static_cast<AttributeTypes>(i) != AttributeTypes::Health ||
			static_cast<AttributeTypes>(i) != AttributeTypes::MaxHealth)
		{
			short currentX = offsetX + 27 * count;
			gotoXY(currentX, offsetY);

			std::string attributeName = GetAttributeString(static_cast<AttributeTypes>(i));
			std::cout << attributeName << "   ";

			std::cout << GetAttributeValue(static_cast<AttributeTypes>(i));
			++count;

			if ((count + 1) % 4 == 0)
			{
				count = 0;
				offsetY += 3;
				gotoXY(offsetX, offsetY);
			}
		}
	}

	std::getchar();
}

int Player::GetAttributeValue(AttributeTypes anAttribute)
{
	switch (anAttribute)
	{
	case AttributeTypes::Health:
		return GetHealth();

	case AttributeTypes::Strength:
		return GetStrength();

	case AttributeTypes::Dexterity:
		return GetDexterity();

	case AttributeTypes::Intelligence:
		return GetIntelligence();

	case AttributeTypes::Constitution:
		return GetCondition();

	case AttributeTypes::AttackStrength:
		return GetAttackStrength();

	case AttributeTypes::MagicStrength:
		return GetMagicStrength();

	case AttributeTypes::Stamina:
		return GetStamina();

	case AttributeTypes::Capacity:
		return GetCapacity();

	case AttributeTypes::Speed:
		return GetSpeed();

	case AttributeTypes::Resiliance:
		return GetResiliance();

	case AttributeTypes::MaxHealth:
		return GetMaxHealth();

	default:
		return 0;
	}
}

int Player::GetEquipmentWeight()
{
	int weight = 0;
	for (std::vector<Item>::iterator it = myEquitment.begin(); it != myEquitment.end(); it++)
	{
		weight += (*it).GetWeight();
	}

	return weight;
}

std::vector<Item> &Player::GetEquipment()
{
	return myEquitment;
}

Item Player::EquipItem(Item &anItem, ItemTypes anItemType)
{
	int index = static_cast<int>(anItemType);
	Item tempItem = myEquitment[index];
	myEquitment[index] = anItem;

	return tempItem;
}

void Player::PrintEquipment()
{
	char input;
	int page = 0;
	do
	{
		PrintBackGround();

		PrintItems(page);

		input = GetCharInput();

		//unsigned int index = static_cast<int>(input - '0') - 1;

		//if (index >= 0 && index + 6 * page < myEquitment.size())
		//{
		//	myInventory.AddItemToInventory(myEquitment[index], *this);
		//	myEquitment[index] = Item();
		//	//myItems.erase(myItems.begin() + realIndex);
		//}

		switch (input)
		{
		case 'p':
		case 'P':
			if (!(page - 1 < 0))
			{
				--page;
			}
			break;
		case 'n':
		case 'N':
			if (!(static_cast<unsigned int>(page + 1) > myEquitment.size() / 6))
			{
				++page;
			}
			break;
		}
	} while (input != 'b' && input != 'B');
}

void Player::PrintItems(int aPage)
{
	short offsetX = 3;
	short offsetY = 3;
	gotoXY(offsetX, offsetY);
	SetConsoleTextAttribute(hstdout, FOREGROUND_INTENSITY);
	std::cout << "Equipment";
	
	gotoXY(offsetX + 80, offsetY);
	std::cout << aPage + 1 << "/" << myEquitment.size() / 7 + 1;


	offsetY += 2;
	int counter = 0;

	unsigned int startIndex = aPage * 6;

	for (unsigned int i = 0; i < 6 &&
		i + aPage * 6 < myEquitment.size(); ++i)
	{
		short currentOffsetX = static_cast<short>(offsetX + 46 * counter);
		
		gotoXY(currentOffsetX + 5, offsetY);
		
		std::cout << GetItemTypeString(static_cast<ItemTypes>(startIndex));

		offsetY;

		if (myEquitment[startIndex].GetWeight() != 0)
		{
			
			myEquitment[startIndex].PrintItem(i + 1, currentOffsetX, offsetY + 2, 0, FOREGROUND_INTENSITY);
		}

		++startIndex;
		++counter;

		if ((counter + 1) % 3 == 0)
		{
			counter = 0;
			offsetY += 9;
		}
	}

	gotoXY(5, 36);
	std::cout << "B. Back";

	gotoXY(59, 36);
	std::cout << "P. Previous page / N. Next page";

	gotoXY(20, 36);
	std::cout << "Input:  ";
}

const std::vector<char> &Player::GetHotkeys()
{
	return mySpellHotKeys;
}

void Player::AddHotkey(char aHotkey)
{
	mySpellHotKeys.push_back(aHotkey);
}

void Player::RemoveHotkey(char aHotkey)
{
	for (std::vector<char>::iterator it = mySpellHotKeys.begin(); it != mySpellHotKeys.end(); ++it)
	{
		if (aHotkey == *it)
		{
			mySpellHotKeys.erase(it);
			break;
		}
	}
}