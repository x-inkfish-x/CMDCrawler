#include "stdafx.h"
#include <iostream>
#include "Item.h"

Item::Item()
{
	myAttributeModifiers = std::vector<int>(static_cast<int>(AttributeTypes::LAST));
	myName = "";
	myWeight = 0;
	myItemType = ItemTypes::LAST;
}


Item::~Item()
{
}

int Item::GetModifier(AttributeTypes anAttribute)
{
	return myAttributeModifiers[static_cast<int>(anAttribute)];
}

std::string Item::GetItemName()
{
	return myName;
}

int Item::GetWeight()
{
	return myWeight;
}

void Item::PrintItem(int anIndex, short anOffsetX, short anOffsetY, short aBackgroundColor, short aTextColor)
{
	gotoXY(anOffsetX, anOffsetY);

	/*std::cout << "           " << GetItemTypeString(myItemType);

	anOffsetY += 2;*/
	gotoXY(anOffsetX, anOffsetY);

	SetConsoleTextAttribute(hstdout, aBackgroundColor | aTextColor);
	std::cout << anIndex << ". " << myName;

	anOffsetX += 3;
	++anOffsetY;
	gotoXY(anOffsetX, anOffsetY);
	std::cout << "Weight: " << myWeight;

	++anOffsetY;
	gotoXY(anOffsetX, anOffsetY);

	for (int i = 0; i < static_cast<int>(AttributeTypes::LAST); ++i)
	{
		int attributeModifier = myAttributeModifiers[i];

		if (attributeModifier != 0)
		{
			SetConsoleTextAttribute(hstdout, aBackgroundColor | aTextColor);
			std::string attributeName = GetAttributeString(static_cast<AttributeTypes>(i));
			std::cout << attributeName << ":  ";

			char sign;
			if (attributeModifier >= 0)
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

void Item::SetStats(const std::vector<int> &someStats)
{
	myAttributeModifiers = someStats;
}

void Item::SetName(const std::string &aName)
{
	myName = aName;
}

void Item::SetWeight(const int aWeight)
{
	myWeight = aWeight;
}

void Item::SetItemType(ItemTypes anItemType)
{
	myItemType = anItemType;
}

ItemTypes Item::GetItemType() const
{
	return myItemType;
}