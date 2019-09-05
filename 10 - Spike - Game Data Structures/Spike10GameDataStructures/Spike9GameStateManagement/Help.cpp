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
	result += "\n\t- 'look' (look around at your current location)";
	result += "\n\t- 'look at ___'";
	result += "\n\t- 'look in ___'";
	//result += "\n\t- 'look inside ___'";
	result += "\n\t- 'look at ___ in ___'";
	//result += "\n\t- 'look at ___ inside ___'";
	//result += "\n\t- 'inspect ___'";
	//result += "\n\t- 'inspect in ___'";
	//result += "\n\t- 'inspect inside ___'";
	//result += "\n\t- 'inspect ___ in ___'";
	//result += "\n\t- 'inspect ___ inside ___'";
	result += "\n\t- 'inventory' (look in your inventory)";
	result += "\n";
	result += "\n\t- 'pick up ___'";
	result += "\n\t- 'pick up ___ from ___'";
	result += "\n\t- 'take ___'";
	result += "\n\t- 'take ___ from ___'";
	result += "\n\t- 'put ___ in ___'";
	//result += "\n\t- 'put ___ into ___'";
	result += "\n\t- 'drop ___'";
	//result += "\n\t- 'drop ___ from ___'";
	//result += "\n\t- 'drop ___ in ___'";
	//result += "\n\t- 'drop ___ into ___'";
	//result += "\n\t- 'drop ___ from ___ in ___'";
	//result += "\n\t- 'drop ___ from ___ into ___'";
	result += "\n";
	result += "\n\t- 'quit' (return to the main menu)";
	result += "\n\t- 'hiscore' (record a new high score - for testing)";
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