#include "stdafx.h"
#include "ItemFactory.h"


ItemFactory::ItemFactory()
{
}


ItemFactory::~ItemFactory()
{
}

Item ItemFactory::CreateItem(Player &aPlayer)
{
	Item item;

	item.SetItemType(GetItemType());
	item.SetStats(GetItemStats(aPlayer.GetBattlesEntered()));
	item.SetName(GetItemName(item));
	item.SetWeight(GetItemWeight(aPlayer.GetBattlesEntered()));
	

	return item;
}

ItemTypes ItemFactory::GetItemType()
{
	return static_cast<ItemTypes>(randBetween(0, static_cast<int>(ItemTypes::LAST) - 1));
}

std::vector<int> ItemFactory::GetItemStats(int aLevel)
{
	int attributeMultiplier = (1 + aLevel / 4);

	std::vector<int> attributeModifiers = std::vector<int>(static_cast<int>(AttributeTypes::LAST));
	std::fill(attributeModifiers.begin(), attributeModifiers.end(), 0);
	int attributeCount = 0;

	do
	{
		if (attributeCount > 4)
		{
			attributeCount = 0;
		}
		for (int attribute = static_cast<int>(AttributeTypes::Strength);
			attribute < static_cast<int>(AttributeTypes::LAST); attribute++)
		{
			int chanceOfAttribute = 15;
			int spawn = randBetween(0, 99);
			if (spawn < chanceOfAttribute)
			{
				++attributeCount;
				do
				{
					attributeModifiers[attribute] = (randBetween(-2, 5 * attributeMultiplier));
				} while (attributeModifiers[attribute] == 0);
			}
		}
	} while (attributeCount == 0 || attributeCount > 4);

	return attributeModifiers;

	
}

std::string ItemFactory::GetItemTypeString(const Item &anItem)
{
	std::string returnString = "ERROR";

	switch (anItem.GetItemType())
	{
	case ItemTypes::Boots:
		returnString = "Boots";
		break;

	case ItemTypes::Braces:
		returnString = "Braces";
		break;

	case ItemTypes::ChestPlate:
		returnString = "Chestplate";
		break;

	case ItemTypes::Gauntlet:
		returnString = "Gauntlet";
		break;

	case ItemTypes::Helmet:
		returnString = "Helmet";
		break;

	case ItemTypes::Legs:
		returnString = "Legs";
		break;

	case ItemTypes::Pendant:
		returnString = "Pendant";
		break;

	case ItemTypes::Ring:
		returnString = "Ring";
		break;

	case ItemTypes::Shield:
		returnString = "Shield";
		break;

	case ItemTypes::Weapon:
		WeaponTypes weaponType = static_cast<WeaponTypes>(randBetween(0, static_cast<int>(WeaponTypes::LAST) - 1));
		returnString = GetWeaponTypeString(weaponType);
		break;
	}

	return returnString;
}

std::string ItemFactory::GetWeaponTypeString(WeaponTypes aWeaponType)
{
	std::string returnString = "ERROR";

	switch (aWeaponType)
	{
	case WeaponTypes::Axe:
		returnString = "Axe";
		break;

	case WeaponTypes::Dagger:
		returnString = "Dagger";
		break;

	case WeaponTypes::Flail:
		returnString = "Flail";
		break;

	case WeaponTypes::LongSword:
		returnString = "Longsword";
		break;

	case WeaponTypes::Mace:
		returnString = "Mace";
		break;

	case WeaponTypes::Schmitar:
		returnString = "Schmitar";
		break;

	case WeaponTypes::ShortSword:
		returnString = "Shortsword";
		break;
	}

	return returnString;
}

std::string ItemFactory::GetItemName(const Item &anItem)
{
	std::string name = "";

	int numberOfAdjectives = 8;
	int getWord = randBetween(1, numberOfAdjectives);

	switch (getWord)
	{
	case 1:
		name += "Aetheric";
		break;

	case 2:
		name += "Awesome";
		break;

	case 3:
		name += "Supreme";
		break;

	case 4:
		name += "Divine";
		break;

	case 5:
		name += "Angelic";
		break;

	case 6:
		name += "Demonic";
		break;

	case 7:
		name += "Satanic";
		break;

	case 8:
		name += "Great";
		break;

	}

	name += " ";

	int numberOfItems = 7;
	getWord = randBetween(1, numberOfItems);

	name += GetItemTypeString(anItem);

	name += " of ";

	int numberOfProperties = 7;
	getWord = randBetween(1, numberOfProperties);

	switch (getWord)
	{
	case 1:
		name += "Division";
		break;

	case 2:
		name += "the Cataclysm";
		break;

	case 3:
		name += "the Apocalyps";
		break;

	case 4:
		name += "Hel";
		break;

	case 5:
		name += "the Underworld";
		break;

	case 6:
		name += "Inferno";
		break;

	case 7:
		name += "Annihilation";
		break;
	}

	return name;
}

int ItemFactory::GetItemWeight(int aLevel)
{
	int attributeMultiplier = (1 + aLevel / 4);
	int weight = randBetween(10, 15 * attributeMultiplier);
	return weight;
}