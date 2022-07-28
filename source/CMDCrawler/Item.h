#pragma once
#include <vector>
#include <string>
#include "Utilities.h"

class Item
{
public:
	Item();
	~Item();

	int GetModifier(AttributeTypes anAttribute);
	std::string GetItemName();

	int GetWeight();

	void PrintItem(int anIndex, short anOffsetX, short anOffsetY, short aBackgroundColor, short aTextColor);

	void SetStats(const std::vector<int> &someStats);
	void SetName(const std::string &aName);
	void SetWeight(int aWeight);

	void SetItemType(ItemTypes anItemType);
	ItemTypes GetItemType() const;

private:

	ItemTypes myItemType;
	
	std::vector<int> myAttributeModifiers;
	std::string myName;
	
	int myWeight;
};

