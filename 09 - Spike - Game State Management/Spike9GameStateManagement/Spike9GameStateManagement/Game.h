#include "pch.h"

#ifndef GAME_H
#define GAME_H

#include <array>
#include <iostream>
#include <string>

#include "MainMenu.h"
#include "Stage.h"
#include "StageManager.h"

class Game
{
private:
	//Private Fields
	StageManager * stageManager;
	Stage * currentStage;
	std::string input;
	std::string output;
	bool finished;

	//Private Methods
	void ConvertToUppercase(std::string* string);

	void ConvertToLowercase(std::string* string);

	void Input();

	void Update();

	void Render();

public:
	//Public Properties
	void SetStage(Stage* stage);

	//Constructor
	Game();	

	//Public Methods
	void Run();
};

#endif