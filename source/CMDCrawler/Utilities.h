#pragma once
#include <Windows.h>
#include <string>

const HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

enum class AttributeTypes
{
	Strength,
	Dexterity,
	Intelligence,
	Constitution,
	Health,
	AttackStrength,
	MagicStrength,
	Stamina,
	Capacity,
	Speed,
	Resiliance,
	MaxHealth,
	LAST
};

enum class Directions
{
	Up,
	Right,
	Down,
	Left,
	LAST
};

enum class Axees
{
	X,
	Y
};

enum class ItemTypes
{
	Weapon,
	Helmet,
	Shield,
	ChestPlate,
	Gauntlet,
	Legs,
	Braces,
	Boots,
	Ring,
	Pendant,
	LAST
};

enum class WeaponTypes
{
	LongSword,
	ShortSword,
	Schmitar,
	Dagger,
	Flail,
	Mace,
	Axe,
	LAST
};

int randBetween(int aStart, int anEnd);
int GetNumInput(int aStart, int anEnd);
char GetCharInput();
void FlushInputStream();

void gotoXY(short aX, short aY);

void PrintPoint(const char aChar);

void PrintRoom();
void PrintFrame();
void PrintRightDoor();
void PrintCenterDoor();
void PrintLeftDoor();
void PrintDialog(const std::string &aDialog);
void InputBox();
void PauseGame();

void PrintBackGround();

std::string GetAttributeString(AttributeTypes anAttributeType);

std::string GetItemTypeString(ItemTypes anItemType);