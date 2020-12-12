#include "entity/adapter/DialogListAdapter.hpp"
#include "util/ApplicationParameters.hpp"

#include <iostream>
// BottomDialogSimple *person* Our tale begins in the small sacred forest by your home village. You have stumbled into a strange cavern and need to find your way out! |Files/0,0|

// BottomDialog 5 Our tale begins in the small sacred forest by your home village. You have stumbled into a strange cavern and need to find your way out!-*Files/0,0* *
// if token is surrounded by colons its a new character
// if token is surrounded by | then its a file to load
std::istringstream DialogListAdapter::TransformData(std::string data)
{
	return std::istringstream(data);
	// if (data.find("BottomDialogSimple") == std::string::npos)
	// 	return std::istringstream(data);

	// auto const longDialogs = FirstPass_(data);
	// return LastPass_(longDialogs);
}

std::list<DialogComp> DialogListAdapter::FirstPass_(std::string data)
{
	std::list<DialogComp> firstPassDialogComp;
	uint32_t currentSprite = 0;
	std::string text = "";
	// latest work here
		auto dataStream =  std::istringstream(data);
		std::string currentToken;
		bool firstCharacterSeen = false;
		while(dataStream >> currentToken)
		{
			std::cout << currentToken << std::endl;
			if (currentToken.front() == '|' &&
				currentToken.back() == '|')
			{
				firstPassDialogComp.push_back
				({
					0u, currentSprite, text, std::string("")
				});
				firstPassDialogComp.push_back
				({
					0u, 0u, "", std::string(currentToken)
				});
				continue;
			}
			if (currentToken.front() == ':' &&
				currentToken.back() == ':')
			{
				if (!firstCharacterSeen)
				{
					firstCharacterSeen = true;
				}
				else
				{
					firstPassDialogComp.push_back
					({
						0u, currentSprite, text, std::string("")
					});
				}
				currentSprite = GetCharacterIndexFromString_(currentToken);
				text = "";
				continue;
			}
			text += currentToken + " ";
		}
		return firstPassDialogComp;
}

std::istringstream DialogListAdapter::LastPass_(std::list<DialogComp> dialogList)
{

}

uint32_t DialogListAdapter::GetCharacterIndexFromString_(std::string token)
{
	// todo
	return 0u;
}