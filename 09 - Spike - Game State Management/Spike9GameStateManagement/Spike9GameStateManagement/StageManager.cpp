#pragma once

#include "pch.h"

#include "StageManager.h"

StageManager::StageManager()
{
	stages = map<string, Stage>();
}

Stage* StageManager::GetStage(string stage)
{
	if (stages.find(stage) == stages.end())
	{
		return nullptr;
	}
	else
	{
		return &(stages[stage]);
	}
}
