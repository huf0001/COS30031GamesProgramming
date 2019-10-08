#include "CommandQuit.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

std::string CommandQuit::GetSyntax()
{
	std::string result;

	result += "QUIT\n";
	result += "----------------------------\n";
	result += "Function:\n";
	result += "\t- Quit the game and return to the Main Menu.\n";
	result += "Syntax:\n";
	result += "\t- \"quit\"\n";

	if (aliases.size() > 0)
	{
		result += "Aliases for \"quit\":\n";

		for (std::string alias : aliases)
		{
			result += "\t- \"" + alias + "\"\n";
		}
	}

	return result;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

CommandQuit::CommandQuit()
{
	AddKeyword("quit");
	AddAlias("q");
	AddAlias("end");
	AddAlias("exit");
	AddAlias("bye");
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

std::string CommandQuit::Process(std::vector<std::string> input, World* world, Player* player)
{
	Game::Instance()->SetNextStage("MainMenu");
	return "Your adventure has ended without fame or fortune.\n\n";
}

