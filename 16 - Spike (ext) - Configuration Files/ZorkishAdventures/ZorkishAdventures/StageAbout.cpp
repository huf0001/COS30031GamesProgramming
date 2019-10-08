#include "pch.h"

#include "StageAbout.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

StageAbout::StageAbout()
{
	name = "About";
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

std::string StageAbout::Setup()
{
	setup = true;
	std::string result = "";

	result += "Zorkish :: About";
	result += "\n--------------------------------------------------------";
	result += "\n";
	result += "\nWritten by: Sam Huffer";
	result += "\n";
	result += "\nPress Enter to return to the Main Menu";
	result += "\n:> ";

	return result;
}

std::string StageAbout::Update(std::string input)
{
	if (!setup)
	{
		setup = true;
		return Setup();
	}

	Game::Instance()->SetNextStage("MainMenu");
	return "\n";
}
