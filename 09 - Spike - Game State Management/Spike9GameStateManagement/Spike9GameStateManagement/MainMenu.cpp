#include "pch.h"

#include "MainMenu.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

MainMenu::MainMenu()
{
	name = "MainMenu";
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

std::string MainMenu::Setup(std::string input)
{
	setup = true;
	std::string result = "";

	result += "Zorkish :: Main Menu";
	result += "\n--------------------------------------------------------";
	result += "\nWelcome to Zorkish Adventures";
	result += "\n\n\t1. Select Adventure and Play";
	result += "\n\t2. Hall of Fame";
	result += "\n\t3. Help";
	result += "\n\t4. About";
	result += "\n\t5. Quit";
	result += "\n\nSelect 1-5:> ";

	return result;
}

std::string MainMenu::Update(std::string input)
{
	if (!setup)
	{
		setup = true;
		return Setup(input);
	}

	std::string invalidInput = "I'm sorry, that is not valid input. Please select 1-5:> ";
	std::string validInput = "You entered a valid input. However, we are still testing. Please select 1-5:> ";

	if (input.length() != 1)
	{
		return invalidInput;
	}
	else if (input == "1")
	{
		//Select Adventure and Play
		return validInput;
	}
	else if (input == "2")
	{
		//Hall of Fame
		return validInput;
	}
	else if (input == "3")
	{
		//Help
		return validInput;
	}
	else if (input == "4")
	{
		//About
		return validInput;
	}
	else if (input == "5")
	{
		//Quit
		return validInput;
	}
	else
	{
		return invalidInput;
	}
}
