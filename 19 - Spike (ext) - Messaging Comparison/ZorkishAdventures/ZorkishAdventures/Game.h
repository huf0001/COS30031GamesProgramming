#include "pch.h"

#ifndef GAME_H
#define GAME_H

class Game
{
private:
	//Private Fields
	static Game* instance;
	//StageManager* stageManager;
	Stage* currentStage;
	Stage* nextStage;
	std::string input;
	std::string output;
	bool finished;

	//Constructor
	Game();

	//Private Methods
	void Input();

	void Update();

	void Render();

public:
	//Public Properties
	static Game* Instance();

	//Public Methods
	void SetNextStage(std::string stage);
	void Process();
	void Quit();
};

#endif