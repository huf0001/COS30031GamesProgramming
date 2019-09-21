#include "CommandAlias.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

std::string CommandAlias::GetSyntax()
{
	std::string result;

	result += "ALIAS\n";
	result += "----------------------------\n";
	result += "Function:\n";
	result += "\t- Give a command a new alias.\n";
	result += "Syntax:\n";
	result += "\t- \"alias [command] as [alias]\"\n";

	if (aliases.size() > 0)
	{
		result += "Aliases for \"alias\":\n";

		for (std::string alias : aliases)
		{
			result += "\t- \"" + alias + "\"\n";
		}
	}

	return result;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

CommandAlias::CommandAlias()
{
	AddKeyword("alias");
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

std::string CommandAlias::Process(std::vector<std::string> input, World* world, Player* player)
{
	input.erase(input.begin());

	switch (input.size())
	{
		case 0:
			return "You need to specify a command and an alias for that command.";
		case 1:
		case 2:
			return "What alias do you want to give \"" + input[0] + "\"?";
		case 3:
			if (!StringManager::Instance()->VectorContainsString(input, "as"))
			{
				return "What alias do you want to give \"" + StringManager::Instance()->VectorToString(input, ' ') + "\"?";
			}
			else if (input[1] != "as")
			{
				return "Incorrect formatting. Command keywords don't have spaces.";
			}
			
			if (!CommandManager::Instance()->HasCommand(input[0]))
			{
				return "Command with keyword / alias \"" + input[0] +"\" does not exist.";
			}
			else if (CommandManager::Instance()->HasCommand(input[2]))
			{
				return "Command with keyword / alias \"" + input[2] + "\" already exists.";
			}
			else
			{
				CommandManager::Instance()->GetCommand(input[0])->AddAlias(input[2]);
				return "Command \"" + input[0] + "\" assigned alias \"" + input[2] +"\".";
			}

		default:
			if (!StringManager::Instance()->VectorContainsString(input, "as"))
			{
				return "What alias do you want to give \"" + StringManager::Instance()->VectorToString(input, ' ') + "\"?";
			}
			else if (input[1] != "as")
			{
				return "Invalid commmand keyword. Specify a keyword that does not have spaces.";
			}
			else
			{
				return "Invalid command alias. Aliases cannot have spaces.";
			}
	}
}