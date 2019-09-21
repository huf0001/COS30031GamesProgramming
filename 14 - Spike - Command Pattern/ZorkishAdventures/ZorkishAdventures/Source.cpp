#include "CommandDebug.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

std::string CommandDebug::GetSyntax()
{
	std::string result;

	result += "DEBUG\n";
	result += "----------------------------\n";
	result += "Function:\n";
	result += "\t- Provides all information on the current location, its paths and items, and the player's inventory.\n";
	result += "Syntax:\n";
	result += "\t- \"debug\"\n";

	if (aliases.size() > 0)
	{
		result += "Aliases for \"debug\":\n";

		for (std::string alias : aliases)
		{
			result += "\t- \"" + alias + "\"\n";
		}
	}

	return result;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

CommandDebug::CommandDebug()
{
	AddKeyword("debug");
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

std::string CommandDebug::Process(std::vector<std::string> input, World* world, Player* player)
{
	
}