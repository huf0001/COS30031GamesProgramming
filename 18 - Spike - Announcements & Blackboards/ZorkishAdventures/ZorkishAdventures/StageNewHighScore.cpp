#include "pch.h"

#include "StageNewHighScore.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

StageNewHighScore::StageNewHighScore()
{
	name = "NewHighScore";
}

//Public Methods-------------------------------------------------------------------------------------------------------------------------------------

std::string StageNewHighScore::Setup()
{
	setup = true;
	std::string result;
	StageGameplay* gameplay = (StageGameplay*)StageManager::Instance()->GetStage("Gameplay");

	result += "Zorkish :: New High Score";
	result += "\n--------------------------------------------------------";
	result += "\n";
	result += "\nCongratuations!";
	result += "\n";
	result += "\nYou have made it to the Zorkish Hall of Fame";
	result += "\n";
	result += "\nAdventure: " + gameplay->GetCurrentWorldName();
	result += "\nScore: 0";
	result += "\nMoves: 0";
	result += "\n";
	result += "\nPlease type your name and press enter:";
	result += "\n:> ";

	return result;
}

std::string StageNewHighScore::Update(std::string input)
{
	if (!setup)
	{
		return Setup();
	}
	
	Game::Instance()->SetNextStage("MainMenu");
	return "New high score added. Returning to Main Menu.\n\n";
}