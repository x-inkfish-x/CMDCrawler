#include "stdafx.h"
#include <iostream>
#include "Spellbook.h"
#include "Player.h"
#include "SpellFactory.h"


Spellbook::Spellbook()
{
}

void Spellbook::DisplaySpells(Player &aPlayer)
{
	

	char input;
	int page = 0;
	do
	{
		PrintBackGround();

		PrintSpells(page);

		input = GetCharInput();

		unsigned int index = static_cast<int>(input - '0') - 1;

		if (index >= 0 && index + 6 * page < mySpells.size())
		{
			int realIndex = index + 6 * page;

			SpellOptions(realIndex, aPlayer);

			//mySpells.erase(mySpells.begin() + index + 6 * page);
		}

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
			if (!(static_cast<unsigned int>(page + 1) > mySpells.size() / 6))
			{
				++page;
			}
			break;
		}


		/*PrintBackGround();
		PrintSpells();

		input = GetCharInput();

		unsigned int index = static_cast<int>(input - '0') - 1;

		if (index >= 0 && index < mySpells.size())
		{
		mySpells.erase(mySpells.begin() + index);
		}*/
	} while (input != 'b' && input != 'B');
}

void Spellbook::PrintSpells(int aPage)
{
	short offsetX = 3;
	short offsetY = 3;
	gotoXY(offsetX, offsetY);
	SetConsoleTextAttribute(hstdout, FOREGROUND_INTENSITY);
	std::cout << "Spells";

	gotoXY(offsetX + 80, offsetY);
	std::cout << aPage + 1 << "/" << mySpells.size() / 7 + 1;

	++offsetY;
	gotoXY(2, offsetY);
	std::cout << "________________________________________________________________________________________";

	++offsetY;
	int counter = 0;

	unsigned int startIndex = aPage * 6;

	for (unsigned int i = 0; i < 6 &&
		i + aPage * 6 < mySpells.size(); ++i)
	{
		short currentOffsetX = static_cast<short>(offsetX + 46 * counter);

		mySpells[startIndex].PrintSpell(i + 1, currentOffsetX, offsetY, 0, FOREGROUND_INTENSITY);

		++startIndex;
		++counter;

		if ((counter + 1) % 3 == 0)
		{
			counter = 0;
			offsetY += 10;
		}
	}

	gotoXY(5, 36);
	std::cout << "B. Back";

	gotoXY(59, 36);
	std::cout << "P. Previous page / N. Next page";

	gotoXY(20, 36);
	std::cout << "Select a spell:  ";
}

void Spellbook::AddSpell(Spell &aSpell)
{
		mySpells.push_back(aSpell);
}

const std::vector<Spell> &Spellbook::GetSpells()
{
	return mySpells;
}

void Spellbook::SpellOptions(int anIndex, Player &aPlayer)
{

	char input;

	do{
		PrintTablet(22, 8);
		

		SetConsoleTextAttribute(hstdout, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);

		gotoXY(25, 11);
		std::cout << "U. Use spell";
		gotoXY(25, 14);
		std::cout << "T. Throw away spell";
		gotoXY(25, 17);
		std::cout << "H. Set hotkey";
		gotoXY(25, 20);
		std::cout << "B. Back";

		gotoXY(27, 22);

		input = GetCharInput();

		switch (input)
		{
		case 't':
		case 'T':
			aPlayer.RemoveHotkey(mySpells[anIndex].GetHotKey());
			mySpells.erase(mySpells.begin() + anIndex);
			return;

		case 'u':
		case 'U':
			aPlayer.RemoveHotkey(mySpells[anIndex].GetHotKey());
			aPlayer.UseSpell(mySpells[anIndex]);
			mySpells.erase(mySpells.begin() + anIndex);
			return;
		case 'h':
		case 'H':
			mySpells[anIndex].SetHotKey(aPlayer);
			return;
		}
	} while (input != 'b' && input != 'B');
	

}

void Spellbook::PrintTablet(short anOffsetX, short anOffsetY)
{
	std::string outPut = std::string("") +
		"??????????????????????????????????????????\n" +
		"?++++++++++++++++++++++++++++++++++++++++?\n" +
		"?+//////////////////////////////////////+?\n" +
		"?+//////////////////////////////////////+?\n" +
		"?+//////////////////////////////////////+?\n" +
		"?+//////////////////////////////////////+?\n" +
		"?+//////////////////////////////////////+?\n" +
		"?+//////////////////////////////////////+?\n" +
		"?+//////////////////////////////////////+?\n" +
		"?+//////////////////////////////////////+?\n" +
		"?+//////////////////////////////////////+?\n" +
		"?+//////////////////////////////////////+?\n" +
		"?+//////////////////////////////////////+?\n" +
		"?+//////////////////////////////////////+?\n" +
		"?+//////////////////////////////////////+?\n" +
		"?+//////////////////////////////////////+?\n" +
		"?++++++++++++++++++++++++++++++++++++++++?\n" +
		"??????????????????????????????????????????\n";

	gotoXY(anOffsetX, anOffsetY);

	for (unsigned int i = 0; i < outPut.size(); ++i)
	{
		char outChar = outPut[i];

		if (outChar == '\n')
		{
			++anOffsetY;
			gotoXY(anOffsetX, anOffsetY);
		}
		else
		{
			PrintPoint(outChar);
		}
	}

}

void Spellbook::UseHotkeyedSpell(char aHotkey, Player &aPlayer)
{
	
	for (std::vector<Spell>::iterator it = mySpells.begin(); it != mySpells.end(); ++it)
	{
		if (aHotkey == it->GetHotKey())
		{
			aPlayer.UseSpell(*it);
			aPlayer.RemoveHotkey(aHotkey);
			mySpells.erase(it);
			break;
		}
	}
}