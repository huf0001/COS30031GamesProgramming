#include "pch.h"

#ifndef STAGEMANAGER_H
#define STAGEMANAGER_H

#include <iostream>
#include <map>
#include <string>

#include "MainMenu.h"
#include "About.h"
#include "Help.h"
#include "SelectAdventure.h"
#include "Gameplay.h"
#include "NewHighScore.h"
#include "HallOfFame.h"

class Stage;

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