#include "pch.h"

#include "StageHelp.h"
#include "Game.h"

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

StageHelp::StageHelp()
{
	name = "Help";
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

std::string StageHelp::Setup()
{
	setup = true;
	std::string result = "";

	result += "Zorkish :: Help\n";
	result += "--------------------------------------------------------\n";
	result += "Available Commands:\n";
	result += CommandManager::Instance()->GetCommandSyntaxes(true);
	result += "\n";
	result += "Press Enter to return to the Main Menu\n";
	result += ":> ";

	return result;
}

std::string StageHelp::Update(std::string input)
{
	if (!setup)
	{
		return Setup();
	}

	Game::Instance()->SetNextStage("MainMenu");
	return "\n";
}