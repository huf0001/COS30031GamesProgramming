#include "SelectAdventure.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

SelectAdventure::SelectAdventure()
{
	name = "SelectAdventure";
	worldsFilename = "Worlds.txt";
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

std::string SelectAdventure::Setup()
{
	setup = true;
	worldNames = std::vector<std::string>();
	worldFilenames = std::vector<std::string>();

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
		result += "\n\t" + std::to_string(i) + (std::string)". " + worldNames[i - 1];		//It was complaining I can't append stuff like this without the string cast
	}
	
	result += "\n";
	
	if (worldNames.size() == 0)
	{
		result += "\nThere are no adventures to choose from.";
	}
	else
	{
		result += "\nSelect 1-" + std::to_string(worldNames.size());
	}
	
	result += "\n:> ";

	return result;
}

std::string SelectAdventure::Update(std::string input)
{
	if (!setup)
	{
		return Setup();
	}

	for (int i = 0; i < worldNames.size(); i++)
	{
		if (input == std::to_string(i + 1))
		{
			return SelectWorld(worldNames[i], worldFilenames[i]);
		}
	}

	return "I'm sorry, that is not valid input. Please select 1-3.\n:> ";
}

std::string SelectAdventure::SelectWorld(std::string name, std::string filename)
{
	World* world = nullptr;
	world = new World(filename);	

	if (world == nullptr || !world->GetLoadedSuccessfully())
	{
		return "\n:>";
	}
	else
	{
		Gameplay* gameplay = (Gameplay*)StageManager::Instance()->GetStage("Gameplay");
		gameplay->SetWorld(world);
		Game::Instance()->SetNextStage("Gameplay");
		return "Loading " + name + " . . .\n\n";
	}
}
