#include "pch.h"

#ifndef STAGEMANAGER_H
#define STAGEMANAGER_H

#include <iostream>
#include <map>
#include <string>

#include "MainMenu.h"

class Stage;

class StageManager
{
private:
	std::map<std::string, Stage*> stages;
public:
	StageManager();
	Stage* GetStage(std::string stage);
};

#endif