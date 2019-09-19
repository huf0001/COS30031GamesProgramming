#include "pch.h"

#include "Command.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

std::string Command::GetName()
{
	return name;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

Command::Command()
{
	keywords = std::vector<std::string>();
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

void Command::AddKeyword(std::string keyword)
{
	keywords.push_back(keyword);
}

bool Command::HasKeyword(std::string string)
{
	for (std::string keyword : keywords)
	{
		if (string == keyword)
		{
			return true;
		}
	}

	return false;
}

bool Command::CanProcess(std::vector<std::string> input, World* world, Player* player)
{
	return HasKeyword(input[0]);
}