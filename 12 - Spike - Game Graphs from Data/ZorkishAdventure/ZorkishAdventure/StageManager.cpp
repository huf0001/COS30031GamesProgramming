#include "StageManager.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

StageManager* StageManager::instance = 0;

StageManager* StageManager::Instance()
{
	if (!instance)
	{
		instance = new StageManager();
	}

	return instance;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

StageManager::StageManager()
{
	stages = std::map<std::string, Stage*>();
	stages["MainMenu"] = (Stage*) new MainMenu();
	stages["About"] = (Stage*) new About();
	stages["Help"] = (Stage*) new Help();
	stages["SelectAdventure"] = (Stage*) new SelectAdventure();
	stages["Gameplay"] = (Stage*) new Gameplay();
	stages["NewHighScore"] = (Stage*) new NewHighScore();
	stages["HallOfFame"] = (Stage*) new HallOfFame();
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

Stage* StageManager::GetStage(std::string stage)
{
	if (stages.find(stage) == stages.end())
	{
		return nullptr;
	}
	else
	{
		return stages[stage];
	}
}
