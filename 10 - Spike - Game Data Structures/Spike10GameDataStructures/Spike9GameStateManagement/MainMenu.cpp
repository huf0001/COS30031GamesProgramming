#include "pch.h"

#include "MainMenu.h"
#include "Game.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

MainMenu::MainMenu()
{
	name = "MainMenu";
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

std::string MainMenu::Setup()
{
	setup = true;
	std::string result;

	result += "Zorkish :: Main Menu";
	result += "\n--------------------------------------------------------";
	result += "\n";
	result += "\nWelcome to Zorkish Adventures";
	result += "\n";
	result += "\n\t1. Select Adventure and Play";
	result += "\n\t2. Hall of Fame";
	result += "\n\t3. Help";
	result += "\n\t4. About";
	result += "\n\t5. Quit";
	result += "\n";
	result += "\nSelect 1-5";
	result += "\n:> ";

	return result;
}

std::string MainMenu::Update(std::string input)
{
	if (!setup)
	{
		return Setup();
	}

	if (input.length() == 1)
	{
		if (input == "1")
		{
			Game::Instance()->SetNextStage("SelectAdventure");
			return "\n";
		}
		else if (input == "2")
		{
			Game::Instance()->SetNextStage("HallOfFame");
			return "\n";
		}
		else if (input == "3")
		{
			Game::Instance()->SetNextStage("Help");
			return "\n";
		}
		else if (input == "4")
		{
			Game::Instance()->SetNextStage("About");
			return "\n";
		}
		else if (input == "5")
		{
			Game::Instance()->Quit();
			return "\nThus ends another grand Zorkish Adventure.\n";
		}
	}
	
	return "I'm sorry, that is not valid input. Please select 1-5.\n:> ";
}
