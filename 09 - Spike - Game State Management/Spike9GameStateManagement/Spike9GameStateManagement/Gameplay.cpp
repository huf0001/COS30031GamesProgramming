#include "pch.h"

#include "Gameplay.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

std::string Gameplay::GetCurrentWorldName()
{
	return (*currentWorld).GetName();
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

Gameplay::Gameplay()
{
	name = "Gameplay";
	worlds = std::map<std::string, World*>();
	worlds["Void World"] = new World("Void World");
	currentWorld = nullptr;
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

std::string Gameplay::Setup()
{
	setup = true;
	std::string result;

	result += "Zorkish :: " + (*currentWorld).GetName();
	result += "\n--------------------------------------------------------";
	result += "\n";
	result += "\n" + (*currentWorld).DescribeCurrentLocation();
	result += "\n:> ";

	return result;
}

std::string Gameplay::SetWorld(std::string world)
{
	if (worlds.find(world) == worlds.end())
	{
		return "Error";
	}
	else
	{
		currentWorld = worlds[world];
		return "Success";
	}
}

std::string Gameplay::Update(std::string input)
{
	if (!setup)
	{
		return Setup();
	}

	if (input == "hiscore")
	{		
		(*Game::Instance()).SetNextStage("NewHighScore");
		return "You have entered the magic word and will now see the \"New High Score\" screen.\n\n";
	}
	else if (input == "quit")
	{		
		(*Game::Instance()).SetNextStage("MainMenu");
		return "Your adventure has ended without fame or fortune.\n\n";
	}

	return "I'm sorry, that is not valid input.\n:> ";
}
