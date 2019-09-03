#include "pch.h"

#include "Help.h"
#include "Game.h"

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

Help::Help()
{
	name = "Help";
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

std::string Help::Setup()
{
	setup = true;
	std::string result = "";

	result += "Zorkish :: Help";
	result += "\n--------------------------------------------------------";
	result += "\nThe following commands are supported:";
	result += "\n";
	//inventory	
	//look
	//look at ___
	//look at ___ in ___
	//look in ___
	result += "\n\tquit";
	result += "\n\thiscore (for testing)";
	result += "\n";
	result += "\nPress Enter to return to the Main Menu";
	result += "\n:> ";

	return result;
}

std::string Help::Update(std::string input)
{
	if (!setup)
	{
		return Setup();
	}

	Game::Instance()->SetNextStage("MainMenu");
	return "\n";
}