#include "pch.h"

#ifndef MAINMENU_H
#define MAINMENU_H

#include <string>
#include "Stage.h"

class MainMenu : Stage
{
private:
	//Private Fields

	//Private Methods

protected:
	//Protected Fields

	//Protected Methods
	std::string Setup(std::string input);
public:
	//Constructor
	MainMenu();

	//Public Methods
	std::string Update(std::string input);
};

#endif