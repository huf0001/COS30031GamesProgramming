#include "pch.h"

#ifndef STAGEMANAGER_H
#define STAGEMANAGER_H

class StageManager
{
private:
	static StageManager* instance;
	std::map<std::string, Stage*> stages;
public:
	//Public Properties
	static StageManager* Instance();

	//Constructor
	StageManager();

	//Public Methods
	Stage* GetStage(std::string stage);
};

#endif