#include "CommandHiScore.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

std::string CommandHiScore::GetSyntax()
{
	std::string result;

	result += "HISCORE\n";
	result += "----------------------------\n";
	result += "Function:\n";
	result += "\t- Skip to the New High Score screen (for testing purposes only).\n";
	result += "Syntax:\n";
	result += "\t- \"hiscore\"\n";

	if (aliases.size() > 0)
	{
		result += "Aliases for \"hiscore\":\n";

		for (std::string alias : aliases)
		{
			result += "\t- \"" + alias + "\"\n";
		}
	}

	return result;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

CommandHiScore::CommandHiScore()
{
	AddKeyword("hiscore");
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

std::string CommandHiScore::Process(std::vector<std::string> input, World* world, Player* player)
{
	Game::Instance()->SetNextStage("NewHighScore");
	return "You have entered the magic word and will now see the \"New High Score\" screen.\n\n";
}

