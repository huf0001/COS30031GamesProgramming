#include "NewHighScore.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

NewHighScore::NewHighScore()
{
	name = "NewHighScore";
}

//Public Methods-------------------------------------------------------------------------------------------------------------------------------------

std::string NewHighScore::Setup()
{
	setup = true;
	std::string result;
	Gameplay* gameplay = (Gameplay*)StageManager::Instance()->GetStage("Gameplay");

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

std::string NewHighScore::Update(std::string input)
{
	if (!setup)
	{
		return Setup();
	}
	
	Game::Instance()->SetNextStage("MainMenu");
	return "New high score added. Returning to Main Menu.\n\n";
}