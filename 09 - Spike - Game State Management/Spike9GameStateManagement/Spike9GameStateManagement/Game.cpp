#include "pch.h"

#include "Game.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

void Game::SetStage(Stage* stage)
{
	(*currentStage).SetSetup(false);
	currentStage = stage;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

Game::Game()
{
	stageManager = new StageManager();
	currentStage = (*stageManager).GetStage("MainMenu");
	input = "";
	output = "";
	finished = false;
}

//Input Loop Methods---------------------------------------------------------------------------------------------------------------------------------

void Game::ConvertToUppercase(std::string * s)
{
	std::string result = *s;
	transform(result.begin(), result.end(), result.begin(), ::toupper);
	*s = result;
}

//Converts the pointed-to std::string into all-lowercase
void Game::ConvertToLowercase(std::string * s)
{
	std::string result = *s;
	transform(result.begin(), result.end(), result.begin(), ::tolower);
	*s = result;
}

void Game::Input()
{
	std::cin >> input;
	ConvertToLowercase(&input);
}

//Update Loop Methods--------------------------------------------------------------------------------------------------------------------------------

void Game::Update()
{
	output = (*currentStage).Update(input);
}

//Render Loop Methods--------------------------------------------------------------------------------------------------------------------------------

void Game::Render()
{
	std::cout << output;
}

//Main Execution-------------------------------------------------------------------------------------------------------------------------------------

void Game::Run()
{
	Update();
	Render();

	while (!finished)
	{
		Input();
		Update();
		Render();
	}
}

