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
	aliases = std::vector<std::string>();
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

void Command::AddKeyword(std::string string)
{
	keywords.push_back(string);
}

void Command::AddAlias(std::string string)
{
	aliases.push_back(string);
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

bool Command::HasAlias(std::string string)
{
	for (std::string alias : aliases)
	{
		if (string == alias)
		{
			return true;
		}
	}

	return false;
}

bool Command::CanProcess(std::vector<std::string> input, World* world, Player* player)
{
	return HasKeyword(input[0]) || HasAlias(input[0]);
}

void Command::ResetAliases()
{
	aliases = std::vector<std::string>();
}