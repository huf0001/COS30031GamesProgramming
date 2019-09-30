#include "pch.h"

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
	stages["MainMenu"] = (Stage*) new StageMainMenu();
	stages["About"] = (Stage*) new StageAbout();
	stages["Help"] = (Stage*) new StageHelp();
	stages["SelectAdventure"] = (Stage*) new StageSelectAdventure();
	stages["Gameplay"] = (Stage*) new StageGameplay();
	stages["NewHighScore"] = (Stage*) new StageNewHighScore();
	stages["HallOfFame"] = (Stage*) new StageHallOfFame();
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
