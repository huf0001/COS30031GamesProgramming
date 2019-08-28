#pragma once

#include "pch.h"

#include "Stage.cpp"
#include "StageManager.cpp"

#include <array>
#include <iostream>
#include <string>

using namespace std;

class Game
{
private:
	StageManager* stageManager;
	Stage* currentStage;
	string input;
	string output;
	bool finished = false;

	void ConvertToUppercase(string* string);

	void ConvertToLowercase(string* string);

	void Input();

	void Update();

	void Render();

public:
	void SetStage(Stage* stage);

	void Run();
};