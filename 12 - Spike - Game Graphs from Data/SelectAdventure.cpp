#include "SelectAdventure.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

SelectAdventure::SelectAdventure()
{
	name = "SelectAdventure";
	worldNames = std::vector<std::string>();
	worldFilenames = std::vector<std::string>();
	worldsFilename = "Worlds.txt";
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

std::string SelectAdventure::Setup()
{
	setup = true;

	//Read available worlds from file
	std::ifstream ifs(worldsFilename);

	if (ifs.is_open())
	{
		std::string line;
		std::vector<std::string> splitLine;
		int lineCount = 0;
		
		while (std::getline(ifs, line))
		{
			lineCount++;
			
			if (line.length() == 0 || line[0] == '#')
			{
				continue;
			}

			splitLine = StringManager::Instance()->StringToVector(line, ':');

			if (splitLine.size() != 2)
			{
				std::cout << "\tError reading '" << worldsFilename << "' at line " << lineCount << std::endl;
			}
			else
			{
				worldNames.push_back(splitLine[0]);
				worldFilenames.push_back(splitLine[1]);
			}
		}
	}
	else
	{
		std::cout << "\tUnable to open file\n";
	}

	ifs.close();


	//Print setup output
	std::string result;

	result += "Zorkish :: Select Adventure";
	result += "\n--------------------------------------------------------";
	result += "\n";
	result += "\nChoose your adventure:";
	result += "\n";

	for (int i = 1; i <= worldNames.size(); i++)
	{
		result += "\n\t" + i + ". " + worldNames[i - 1];
	}
	
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
