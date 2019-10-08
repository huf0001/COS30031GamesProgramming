#include "StageGameplay.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

std::string StageGameplay::GetCurrentWorldName()
{
	return world->GetName();
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

StageGameplay::StageGameplay()
{
	name = "Gameplay";
	world = nullptr;
	player = new Player("Player 1");
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

std::string StageGameplay::Setup()
{
	setup = true;
	std::string result;

	result += "Zorkish :: " + world->GetName();
	result += "\n--------------------------------------------------------";
	result += "\n";
	result += "\nYou awaken in " + world->DescribeCurrentLocation();
	result += "\n:> ";

	return result;
}

void StageGameplay::SetWorld(World* world)
{
	this->world = world;
}

std::string StageGameplay::Update(std::string input)
{
	if (!setup)
	{
		return Setup();
	}

	std::vector<std::string> inputStrings = StringManager::Instance()->StringToVector(input, ' ');
	
	if (CommandManager::Instance()->CanProcess(inputStrings, world, player))
	{
		std::string result = CommandManager::Instance()->Process(inputStrings, world, player);

		if (result != "Error")
		{
			return result + "\n:> ";
		}
		else
		{
			return "I'm sorry, that is not valid input.\n:> ";
		}
	}

	return "I'm sorry, that is not valid input.\n:> ";
}
