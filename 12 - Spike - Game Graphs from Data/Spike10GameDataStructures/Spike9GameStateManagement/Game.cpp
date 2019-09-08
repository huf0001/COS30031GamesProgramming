#include "pch.h"

#include "Game.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

//Sets instance; required for singleton, or there will be a compilation error
Game* Game::instance = 0;

//Accessor for instance
Game* Game::Instance()
{
	if (!instance)
	{
		instance = new Game();
	}

	return instance;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

Game::Game()
{
	currentStage = StageManager::Instance()->GetStage("MainMenu");
	nextStage = nullptr;
	input = "";
	output = "";
	finished = false;
}

//Input Loop Methods---------------------------------------------------------------------------------------------------------------------------------

void Game::Input()
{
	std::getline(std::cin, input);
	input = StringManager::Instance()->ToLowercase(input);
}

//Update Loop Methods--------------------------------------------------------------------------------------------------------------------------------

void Game::Update()
{
	output = currentStage->Update(input);

	if (nextStage != nullptr)
	{
		currentStage->SetSetup(false);
		currentStage = nextStage;
		nextStage = nullptr;

		output += currentStage->Update(input);
	}
}

void Game::SetNextStage(std::string stage)
{
	nextStage = StageManager::Instance()->GetStage(stage);
}

//Render Loop Methods--------------------------------------------------------------------------------------------------------------------------------

void Game::Render()
{
	std::cout << output;
}

//Core Execution-------------------------------------------------------------------------------------------------------------------------------------

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

void Game::Quit()
{
	finished = true;
}

