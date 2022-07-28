#include "stdafx.h"
#include <iostream>
#include "Spell.h"
#include "Utilities.h"
#include "Player.h"
#include <cctype>

Spell::Spell(int aLevel)
{
	myHotKey = '\0';
	int attributeMultiplier = (1 + aLevel / 4);

	myAttributeModifiers = std::vector<int>(static_cast<int>(AttributeTypes::LAST));
	std::fill(myAttributeModifiers.begin(), myAttributeModifiers.end(), 0);

	int spawnRate = 15;
	int attributeCount = 0;

	do
	{
		if (attributeCount > 4)
		{
			attributeCount = 0;
		}
		for (int i = 0; i < static_cast<int>(AttributeTypes::LAST); ++i)
		{
			int spawn = randBetween(0, 99);
			if (spawn < spawnRate)
			{
				++attributeCount;
				do
				{
					myAttributeModifiers[i] = (randBetween(-2, 5 * attributeMultiplier));
				} while (myAttributeModifiers[i] == 0);
			}
		}
	} while (attributeCount == 0);

	myDurability = randBetween(2, 10);

	myName = GenerateSpellName();

}


Spell::~Spell()
{
}

std::string Spell::GenerateSpellName()
{
	std::string name;

	int numSpellPrefix = 1;
	int getWord = randBetween(1, numSpellPrefix);

	switch (getWord)
	{
	case 1:
		name += "Devestating";
		break;
	}

	name += " ";

	int numSpellType = 4;
	getWord = randBetween(1, numSpellType);

	switch (getWord)
	{
	case 1:
		name += "Hex";
		break;

	case 2:
		name += "Spell";
		break;

	case 3:
		name += "Ritual";
		break;

	case 4:
		name += "Curse";
		break;
	}

	name += " of ";

	int numSpellPostfix = 3;
	getWord = randBetween(1, numSpellPostfix);

	switch (getWord)
	{
	case 1:
		name += "Destruction";
		break;

	case 2:
		name += "Armagedon";
		break;

	case 3:
		name += "Banishment";
		break;
	}

	return name;
}

int Spell::GetModifier(AttributeTypes anAttribute)
{
	return myAttributeModifiers[static_cast<int>(anAttribute)];
}

int Spell::GetDurability()
{
	return myDurability;
}

std::string Spell::GetSpellName()
{
	return myName;
}

void Spell::WearSpell()
{
	--myDurability;
}

void Spell::PrintSpell(int anIndex, short anOffsetX, short anOffsetY, short aBackgroundColor, short aTextColor)
{
	gotoXY(anOffsetX, anOffsetY);
	SetConsoleTextAttribute(hstdout, aBackgroundColor | aTextColor);

	std::cout << anIndex << ". " << myName;

	anOffsetX += 3;
	++anOffsetY;
	gotoXY(anOffsetX, anOffsetY);
	std::cout << "Durability: " << myDurability;

	if (myHotKey != '\0')
	{
		SetConsoleTextAttribute(hstdout, aBackgroundColor | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		std::cout << "       (" << myHotKey << ")";
		SetConsoleTextAttribute(hstdout, aBackgroundColor | aTextColor);
	}

	++anOffsetY;
	gotoXY(anOffsetX, anOffsetY);

	for (int i = 0; i < static_cast<int>(AttributeTypes::LAST); ++i)
	{
		int attributeModifier = myAttributeModifiers[i];
		SetConsoleTextAttribute(hstdout, aBackgroundColor | aTextColor);
		

		if (attributeModifier != 0)
		{
			std::string attributeName = GetAttributeString(static_cast<AttributeTypes>(i));
			std::cout << attributeName << ":  ";

			SetConsoleTextAttribute(hstdout, aBackgroundColor | aTextColor);
			char sign;
			if (attributeModifier > 0)
			{
				sign = '+';
				SetConsoleTextAttribute(hstdout, aBackgroundColor | FOREGROUND_GREEN);
			}
			else
			{
				sign = '-';
				attributeModifier = -attributeModifier;
				SetConsoleTextAttribute(hstdout, aBackgroundColor | FOREGROUND_RED);
			}

			std::cout << sign << attributeModifier;
			++anOffsetY;
			gotoXY(anOffsetX, anOffsetY);
		}
	}

	SetConsoleTextAttribute(hstdout, aBackgroundColor | aTextColor);
}

char Spell::GetHotKey()
{
	return myHotKey;
}

void Spell::SetHotKey(Player &aPlayer)
{
	char hotKey;

	do
	{
		aPlayer.GetCapacity();
		PrintDialog("Choose a hotkey.\nInput nothing to remove hotkey.\n\nB. Back");
		hotKey = GetCharInput();
		hotKey = static_cast<char>(std::toupper(hotKey));

		if (hotKey != 'b' && hotKey != 'b' && IsValidHotKey(hotKey, aPlayer))
		{
			if (hotKey != '\n')
			{
				if (myHotKey != '\0')
				{
					aPlayer.RemoveHotkey(myHotKey);
				}
				aPlayer.AddHotkey(hotKey);
				myHotKey = hotKey;
				return;
			}
			else
			{
				aPlayer.RemoveHotkey(myHotKey);
				myHotKey = '\0';
				return;
			}
		}
		else
		{
			std::string outPut = std::string("") + hotKey + " is not a valid hotkey.";
			PrintDialog(outPut);
			PauseGame();
		}
	} while (hotKey != 'b' && hotKey != 'B');
}

bool Spell::IsValidHotKey(char aHotKey, Player &aPlayer)
{
	if (aHotKey == 'i' || aHotKey == 'I' ||
		aHotKey == 'e' || aHotKey == 'E' ||
		aHotKey == 's' || aHotKey == 'S' ||
		aHotKey == '\0' || aHotKey == ' ' ||
		aHotKey >= '0' && aHotKey <= '9')
	{
		return false;
	}
	else
	{
		const std::vector<char> setHotKeys = aPlayer.GetHotkeys();
		for (size_t i = 0; i < setHotKeys.size(); ++i)
		{
			if (aHotKey == setHotKeys[i])
			{
				return false;
			}
		}

		return true;
	}
}