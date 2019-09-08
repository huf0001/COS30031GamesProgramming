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
	result += "\n1. Fred, Mountain World, 5000";
	result += "\n2. Mary, Mountain World, 4000";
	result += "\n3. Joe, Water World, 3000";
	result += "\n4. Henry, Mountain World, 2000";
	result += "\n5. Susan, Mountain World, 1000";
	result += "\n6. Alfred, Water World, 900";
	result += "\n7. Clark, Mountain World, 800";
	result += "\n8. Harold, Mountain World, 500";
	result += "\n9. Julie, Water World, 300";
	result += "\n10. Bill, Box World, -5";
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

	Game::Instance()->SetNextStage("MainMenu");
	return "\n";
}
