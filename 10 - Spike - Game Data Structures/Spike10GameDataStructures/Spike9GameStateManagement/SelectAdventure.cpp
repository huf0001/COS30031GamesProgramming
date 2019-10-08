#include "pch.h"

#include "SelectAdventure.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

SelectAdventure::SelectAdventure()
{
	name = "SelectAdventure";
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

std::string SelectAdventure::Setup()
{
	setup = true;
	std::string result;

	result += "Zorkish :: Select Adventure";
	result += "\n--------------------------------------------------------";
	result += "\n";
	result += "\nChoose your adventure:";
	result += "\n";
	result += "\n\t1. Mountain World";
	result += "\n\t2. Water World";
	result += "\n\t3. Box World";
	result += "\n";
	result += "\nSelect 1-3";
	result += "\n:> ";

	return result;
}

std::string SelectAdventure::Update(std::string input)
{
	if (!setup)
	{
		return Setup();
	}

	if (input.length() == 1)
	{
		if (input == "1")
		{
			return SelectWorld("Mountain World");
		}
		else if (input == "2")
		{
			return SelectWorld("Water World");
		}
		else if (input == "3")
		{
			return SelectWorld("Box World");
		}
	}

	return "I'm sorry, that is not valid input. Please select 1-3.\n:> ";
}

std::string SelectAdventure::SelectWorld(std::string world)
{
	Gameplay* gameplay = (Gameplay*)StageManager::Instance()->GetStage("Gameplay");
	std::string outcome = gameplay->SetWorld("Void World");
	//std::string outcome = gameplay->SetWorld(world);

	if (outcome == "Success")
	{
		Game::Instance()->SetNextStage("Gameplay");
		return world + " selected . . . Re-routing to Void World . . .\n\n";
	}
	else
	{
		return "Developer Error: " + world + " is not an available world. Please select 1-3.\n:>";
	}
}
