#include "pch.h"

#include "StageManager.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

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

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

StageManager::StageManager()
{
	stages = std::map<std::string, Stage*>();
	stages["MainMenu"] = (Stage*) new MainMenu();
	//Add about stage
	//Add help stage
	//Add select adventure stage
	//Add gameplay stage
	//Add new high score stage
	//Add hall of fame stage
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

