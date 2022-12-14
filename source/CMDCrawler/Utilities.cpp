#include "stdafx.h"
#include <cstdlib>

#include <string>
#include <iostream>
#include "Utilities.h"

int randBetween(int aStart, int anEnd)
{
	int modVal = anEnd - aStart + 1;
	return rand() % modVal + aStart;
}

int GetNumInput(int aStart, int anEnd)
{
	int returnValue = 0;

	do
	{
		std::cin >> returnValue;
		FlushInputStream();

	} while (returnValue < aStart || returnValue > anEnd);

	return returnValue;
}

char GetCharInput()
{
	char returnChar = static_cast<char>(std::getchar());
	FlushInputStream();

	return returnChar;
}

void FlushInputStream()
{
	std::cin.sync();
	std::cin.clear();
}



void gotoXY(short x, short y)
{
	COORD c = { x, y };

	SetConsoleCursorPosition(hstdout, c);
}

void PrintPoint(const char aChar)
{
	int targetColor = 0;

	if (aChar != ' ' && aChar != '\n'){
		switch (aChar)
		{
		case '#':
			//set background color
			targetColor += BACKGROUND_RED;
			//set text color
			//targetColor += "" + std::to_string(static_cast<int>(Colors::RED));
			break;

		case '-':
			//white
			targetColor += BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
			break;

		case '/':
			//gray
			targetColor += BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
			break;

		case '=':
			//green
			targetColor += BACKGROUND_GREEN;
			break;

		case '?':
			//black
			targetColor = 0;
			break;

		case '+':
			//dark gray
			targetColor += 0 | BACKGROUND_INTENSITY;//BACKGROUND_BLUE | BACKGROUND_INTENSITY;
			break;
			
		case '@':
			//yellow
			targetColor += BACKGROUND_GREEN | BACKGROUND_RED;
			break;

		case '!':
			//cyan
			targetColor += BACKGROUND_BLUE | BACKGROUND_GREEN;
			break;

		case '$':
			targetColor += BACKGROUND_BLUE;
			break;

		case '&':
			targetColor += BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
			break;

		case '*':
			targetColor += BACKGROUND_BLUE | BACKGROUND_INTENSITY;
			break;

		default:
			targetColor = 0;

		}


		SetConsoleTextAttribute(hstdout, static_cast<short>(targetColor));
		std::cout << " ";
	}
	else if (aChar == '\n')
	{
		
		std::cout << std::endl;
	}
	else
	{
		CONSOLE_SCREEN_BUFFER_INFO SBInfo;
		GetConsoleScreenBufferInfo(hstdout, &SBInfo);

		gotoXY(SBInfo.dwCursorPosition.X + 1, SBInfo.dwCursorPosition.Y);
	}


	targetColor = 0;
	SetConsoleTextAttribute(hstdout, static_cast<short>(targetColor));
}

void PrintRoom()
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

void PrintFrame()
{
	std::string frame =
		std::string(
		"############################################################################################\n") +
		"############################################################################################\n" +
		"##                                                                                        ##\n" +
		"##                                                                                        ##\n" +
		"##                                                                                        ##\n" +
		"##                                                                                        ##\n" +
		"##                                                                                        ##\n" +
		"##                                                                                        ##\n" +
		"##                                                                                        ##\n" +
		"##                                                                                        ##\n" +
		"##                                                                                        ##\n" +
		"##                                                                                        ##\n" +
		"##                                                                                        ##\n" +
		"##                                                                                        ##\n" +
		"##                                                                                        ##\n" +
		"##                                                                                        ##\n" +
		"##                                                                                        ##\n" +
		"##                                                                                        ##\n" +
		"##                                                                                        ##\n" +
		"##                                                                                        ##\n" +
		"##                                                                                        ##\n" +
		"##                                                                                        ##\n" +
		"##                                                                                        ##\n" +
		"##                                                                                        ##\n" +
		"##                                                                                        ##\n" +
		"##                                                                                        ##\n" +
		"##                                                                                        ##\n" +
		"##                                                                                        ##\n" +
		"##                                                                                        ##\n" +
		"##                                                                                        ##\n" +
		"##                                                                                        ##\n" +
		"##                                                                                        ##\n" +
		"##                                                                                        ##\n" +
		"##                                                                                        ##\n" +
		"##                                                                                        ##\n" +
		"##                                                                                        ##\n" +
		"##                                                                                        ##\n" +
		"############################################################################################\n" +
		"############################################################################################\n";

	gotoXY(static_cast<short>(0), static_cast<short>(0));

	for (unsigned int i = 0; i < frame.size(); ++i)
	{
		PrintPoint(frame[i]);
	}
}

void PrintRightDoor()
{
	std::string rightDoor =
		std::string(
		"                                                                                  ????-\n") +
		"                                                                              ????---?-\n" +
		"                                                                          ????----+++?-\n" +
		"                                                                          ?---+++++++?-\n" +
		"                                                                          ?-+++++++++?-\n" +
		"                                                                          ?-+++++++++?-\n" +
		"                                                                          ?-+++++++++?-\n" +
		"                                                                          ?-+++++++++?-\n" +
		"                                                                          ?-+++++++++?-\n" +
		"                                                                          ?-+++++++++?-\n" +
		"                                                                          ?-+++++++++?-\n" +
		"                                                                          ?-+++++++++?-\n" +
		"                                                                          ?-+++++++++?-\n" +
		"                                                                          ??---++++++?-\n" +
		"                                                                            ???---+++?-\n" +
		"                                                                               ???---?-\n" +
		"                                                                                  ????-\n";

	gotoXY(0, 19);

	for (unsigned int i = 0; i < rightDoor.size(); ++i)
	{
		PrintPoint(rightDoor[i]);
	}
}

void PrintLeftDoor()
{
	std::string leftDoor = 
		std::string(
		"     -????\n") +
		"     -?---????\n" +
		"     -?+++----????\n" +
		"     -?+++++++---?\n" +
		"     -?+++++++++-?\n" +
		"     -?+++++++++-?\n" +
		"     -?+++++++++-?\n" +
		"     -?+++++++++-?\n" +
		"     -?+++++++++-?\n" +
		"     -?+++++++++-?\n" +
		"     -?+++++++++-?\n" +
		"     -?+++++++++-?\n" +
		"     -?+++++++++-?\n" +
		"     -?++++++---??\n" +
		"     -?+++---???\n" +
		"     -?---???\n" +
		"     -????\n";

	gotoXY(0, 19);

	for (unsigned int i = 0; i < leftDoor.size(); ++i)
	{
		PrintPoint(leftDoor[i]);
	}
}

void PrintCenterDoor()
{
	std::string centerDoor = 
		std::string(
		"                                      ????????????????\n") +
		"                                      ?++++++++++++++?\n" +
		"                                      ?++++++++++++++?\n" +
		"                                      ?++++++++++++++?\n" +
		"                                      ?++++++++++++++?\n" +
		"                                      ?++++++++++++++?\n" +
		"                                      ?++++++++++++++?\n" +
		"                                      ????????????????\n";

	gotoXY(0, 22);

	for (unsigned int i = 0; i < centerDoor.size(); ++i)
	{
		PrintPoint(centerDoor[i]);
	}
}

void PrintDialog(const std::string &aDialogString)
{
	std::string dialogWindow =
		std::string(
		"           ???????+//////////////////////////////////////////////////////+???????\n") +
		"              ????+//////////////////////////////////////////////////////+????\n" +
		"                ??+//////////////////////////////////////////////////////+??\n" +
		"                 ?+//////////////////////////////////////////////////////+?\n" +
		"                 ?+//////////////////////////////////////////////////////+?\n" +
		"                 ?+//////////////////////////////////////////////////////+?\n" +
		"                 ?+//////////////////////////////////////////////////////+?\n" +
		"                 ?+//////////////////////////////////////////////////////+?\n" +
		"                 ?+//////////////////////////////////////////////////////+?\n" +
		"                 ?+//////////////////////////////////////////////////////+?\n" +
		"                 ?+//////////////////////////////////////////////////////+?\n" +
		"                 ?+//////////////////////////////////////////////////////+?\n" +
		"                 ?++++++++++++++++++++++++++++++++++++++++++++++++++++++++?\n" +
		"                 ??????????????????????????????????????????????????????????\n";

	gotoXY(0, 2);

	for (unsigned int i = 0; i < dialogWindow.size(); ++i)
	{
		PrintPoint(dialogWindow[i]);
	}

	short textXOrigin = 20;
	short textYOrigin = 2;
	gotoXY(textXOrigin, textYOrigin);

	int color = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;

	SetConsoleTextAttribute(hstdout, static_cast<short>(color));
	int currentLinePosition = 0;
	int dialogWindowWidth = 51;

	for (unsigned int i = 0; i < aDialogString.size(); ++i)
	{
		char currentChar = aDialogString[i];
		
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
			textYOrigin += 1;
			gotoXY(textXOrigin, textYOrigin);
			currentLinePosition = 0;
		}
	}

	gotoXY(textXOrigin, textYOrigin + 2);
}

void InputBox()
{
	std::string inputBox = std::string("") +
		"     ???\n"
		"   ???????\n"
		"  ???+++???\n"
		" ??+++++++??\n"
		" ???+++++???\n"
		"  ???+++??? \n";

	short offsetX = 44;
	short offsetY = 30;

	gotoXY(offsetX, offsetY);

	for (unsigned int i = 0; i < inputBox.size(); i++)
	{
		if (inputBox[i] == '\n')
		{
			offsetY += 1;
			gotoXY(static_cast<short>(offsetX), static_cast<short>(offsetY));
		}
		else
		{
			PrintPoint(inputBox[i]);
		}
	}

	offsetX = 50;
	offsetY = 33;

	SetConsoleTextAttribute(hstdout, BACKGROUND_INTENSITY);
	gotoXY(offsetX, offsetY);
}

std::string GetAttributeString(AttributeTypes anAttributeType)
{
	switch (anAttributeType)
	{
	case AttributeTypes::Strength:
		return "Strength";
		
	case AttributeTypes::Dexterity:
		return "Dexterity";

	case AttributeTypes::Intelligence:
		return "Intelligence";

	case AttributeTypes::Constitution:
		return "Constitution";

	case AttributeTypes::Health:
		return "Health";

	case AttributeTypes::AttackStrength:
		return "Attack strength";

	case AttributeTypes::MagicStrength:
		return "Magic strength";

	case AttributeTypes::Stamina:
		return "Stamina";

	case AttributeTypes::Capacity:
		return "Capacity";

	case AttributeTypes::Speed:
		return "Speed";

	case AttributeTypes::Resiliance:
		return "Resiliance";

	case AttributeTypes::MaxHealth:
		return "Max health";
	default:
		return "ERROR";
		break;
	}
}

void PrintBackGround()
{
	std::string backGround = std::string("") +
		"????????????????????????????????????????????????????????????????????????????????????????\n" +
		"????????????????????????????????????????????????????????????????????????????????????????\n" +
		"????????????????????????????????????????????????????????????????????????????????????????\n" +
		"????????????????????????????????????????????????????????????????????????????????????????\n" +
		"????????????????????????????????????????????????????????????????????????????????????????\n" +
		"????????????????????????????????????????????????????????????????????????????????????????\n" +
		"????????????????????????????????????????????????????????????????????????????????????????\n" +
		"????????????????????????????????????????????????????????????????????????????????????????\n" +
		"????????????????????????????????????????????????????????????????????????????????????????\n" +
		"????????????????????????????????????????????????????????????????????????????????????????\n" +
		"????????????????????????????????????????????????????????????????????????????????????????\n" +
		"????????????????????????????????????????????????????????????????????????????????????????\n" +
		"????????????????????????????????????????????????????????????????????????????????????????\n" +
		"????????????????????????????????????????????????????????????????????????????????????????\n" +
		"????????????????????????????????????????????????????????????????????????????????????????\n" +
		"????????????????????????????????????????????????????????????????????????????????????????\n" +
		"????????????????????????????????????????????????????????????????????????????????????????\n" +
		"????????????????????????????????????????????????????????????????????????????????????????\n" +
		"????????????????????????????????????????????????????????????????????????????????????????\n" +
		"????????????????????????????????????????????????????????????????????????????????????????\n" +
		"????????????????????????????????????????????????????????????????????????????????????????\n" +
		"????????????????????????????????????????????????????????????????????????????????????????\n" +
		"????????????????????????????????????????????????????????????????????????????????????????\n" +
		"????????????????????????????????????????????????????????????????????????????????????????\n" +
		"????????????????????????????????????????????????????????????????????????????????????????\n" +
		"????????????????????????????????????????????????????????????????????????????????????????\n" +
		"????????????????????????????????????????????????????????????????????????????????????????\n" +
		"????????????????????????????????????????????????????????????????????????????????????????\n" +
		"????????????????????????????????????????????????????????????????????????????????????????\n" +
		"????????????????????????????????????????????????????????????????????????????????????????\n" +
		"????????????????????????????????????????????????????????????????????????????????????????\n" +
		"????????????????????????????????????????????????????????????????????????????????????????\n" +
		"????????????????????????????????????????????????????????????????????????????????????????\n" +
		"????????????????????????????????????????????????????????????????????????????????????????\n" +
		"????????????????????????????????????????????????????????????????????????????????????????\n";

	short offsetX = 2;
	short offsetY = 2;

	gotoXY(offsetX, offsetY);

	for (unsigned int i = 0; i < backGround.size(); ++i)
	{
		if (backGround[i] == '\n')
		{
			++offsetY;
			gotoXY(offsetX, offsetY);
		}
		else
		{
			PrintPoint(backGround[i]);
		}
	}
}

void PauseGame()
{
	std::getchar();
	FlushInputStream();
}

std::string GetItemTypeString(ItemTypes anItemType)
{
	std::string returnString = "ERROR";

	switch (anItemType)
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
		returnString = "Weapon";
		break;
	}

	return returnString;
}