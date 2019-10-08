#include "pch.h"

#include "HallOfFame.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

HallOfFame::HallOfFame()
{
	name = "HallOfFame";
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

std::string HallOfFame::Setup()
{
	setup = true;
	std::string result = "";

	result += "Zorkish :: Hall of Fame";
	result += "\n--------------------------------------------------------";
	result += "\n";
	result += "\nTop 10 Zorkish Adventure Champions";
	result += "\n";
	result += "1. Fred, Mountain World, 5000";
	result += "2. Mary, Mountain World, 4000";
	result += "3. Joe, Water World, 3000";
	result += "4. Henry, Mountain World, 2000";
	result += "5. Susan, Mountain World, 1000";
	result += "6. Alfred, Water World, 900";
	result += "7. Clark, Mountain World, 800";
	result += "8. Harold, Mountain World, 500";
	result += "9. Julie, Water World, 300";
	result += "10. Bill, Box World, -5";
	result += "\n";
	result += "\nPress Enter to return to the Main Menu";
	result += "\n:> ";

	return result;
}

std::string HallOfFame::Update(std::string input)
{
	if (!setup)
	{
		return Setup();
	}

	(*Game::Instance()).SetNextStage("MainMenu");
	return "\n";
}
