//Universal stuff
#include "pch.h"
#pragma once

#include "Game.h"

void Game::ConvertToUppercase(string * s)
{
	string result = *s;
	transform(result.begin(), result.end(), result.begin(), ::toupper);
	*s = result;
}

//Converts the pointed-to string into all-lowercase
void Game::ConvertToLowercase(string * s)
{
	string result = *s;
	transform(result.begin(), result.end(), result.begin(), ::tolower);
	*s = result;
}

void Game::Input()
{
	cin >> input;
	ConvertToLowercase(&input);
}

void Game::Update()
{

}

void Game::Render()
{
	cout << input << endl;
}

void Game::SetStage(Stage* stage)
{
	this->currentStage = stage;
}

void Game::Run()
{
	stageManager = new StageManager();
	currentStage = stageManager->GetStage("MainMenu");

	while (!finished)
	{
		Input();
		Update();
		Render();
	}
}
