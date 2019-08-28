#include "pch.h"
#pragma once

#include "Game.h"

#include <iostream>
#include <string>
#include <map>

using namespace std;

class StageManager
{
private:
	map<string, Stage> stages;
public:
	StageManager();
	Stage* GetStage(string stage);
};