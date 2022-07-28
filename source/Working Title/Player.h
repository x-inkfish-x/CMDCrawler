#pragma once
#include <vector>
#include <string>
#include "Item.h"
#include "Spell.h"
#include "Utilities.h"
#include "Inventory.h"
#include "Spellbook.h"

class Player
{
public:
	Player();
	~Player();

	void Update();

	int GetHealth();
	int GetStrength();
	int GetDexterity();
	int GetIntelligence();
	int GetCondition();
	int GetAttackStrength();
	int GetMagicStrength();
	int GetStamina();
	int GetCapacity();
	int GetSpeed();
	int GetResiliance();
	int GetMaxHealth();
	std::string GetName();
	
	Inventory &GetInventory();
	void TakeDamage(int aDamage);

	int GetRoomEntered();
	int GetBattlesEntered();

	void IncrementRoomsEntered();
	void IncrementBattlesEntered();


	std::vector<int> GetPlayerPos();

	int GetAttributeModification(AttributeTypes anAttribute);
	int GetAttributeValue(AttributeTypes anAttribute);

	void SetPlayerPos(const std::vector<int> newPos);
	int GetPlayerPosX() const;
	int GetPlayerPosY() const;

	int GetLastPosX();
	int GetLastPosY();

	Directions GetFacingDirection();

	void PrintStatusBar();
	void SetWorldSize(int aWidth, int aHeight);
	int GetWorldSizeX();
	int GetWorldSizeY();
	std::string GetDirectionString();

	
	void CheckCommand(char aCommand);

	void DecrementStamina(unsigned int aDecrement);
	bool SetName();

	std::vector<Item> &GetEquipment();
	Item EquipItem(Item &anItem, ItemTypes anItemType);

	void PrintEquipment();

	void AddSpell(Spell &aSpell);
	void UseSpell(Spell &aSpell);
	const std::vector<char> &GetHotkeys();
	void AddHotkey(char aHotkey);
	void RemoveHotkey(char aHotkey);


private:
	Inventory myInventory;
	Spellbook mySpellbook;

	std::vector<char> mySpellHotKeys;

	std::vector<int> myPlayerPos;
	int myLastPosX;
	int myLastPosY;
	int myWorldWidthX;
	int myWorldHeightY;
	
	std::vector<Item> myEquitment;
	std::vector<Spell> myActiveSpells;

	int myBaseStrength;
	int myBaseDexterity;
	int myBaseIntelligence;
	int myBaseCondition;

	int myRoomsEntered = 0;
	int myBattles = 0;

	int myStaminaLoss;
	int myDamage;
	
	int myMaxHealth;

	
	std::string myName;

	int GetEquipmentWeight();

	void WearSpells();
	
	void DisplayInventory();
	
	void DisplayStats();

	void PrintItems(int aPage);
	
};

