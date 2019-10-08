#include "CommandHelp.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

std::string CommandHelp::GetSyntax()
{
	std::string result;

	result += "HELP\n";
	result += "----------------------------\n";
	result += "Function:\n";
	result += "\t- View available commands, their functions, and their syntax.\n";
	result += "Syntax:\n";
	result += "\t- \"help\"\n";

	if (aliases.size() > 0)
	{
		result += "Aliases for \"help\":\n";

		for (std::string alias : aliases)
		{
			result += "\t- \"" + alias + "\"\n";
		}
	}

	return result;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

CommandHelp::CommandHelp() : Command("HELP")
{
	AddKeyword("help");
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

std::string CommandHelp::Process(std::vector<std::string> input, World* world, Player* player)
{
	std::string result;

	result += "Available Commands:\n";
	result += CommandManager::Instance()->GetCommandSyntaxes(false);

	return result;
}