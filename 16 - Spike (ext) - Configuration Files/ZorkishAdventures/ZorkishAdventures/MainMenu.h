#include "pch.h"

#ifndef MAINMENU_H
#define MAINMENU_H

#include <string>
#include "Stage.h"

class StageMainMenu : Stage
{
private:
	//Private Fields

	//Private Methods

protected:
	//Protected Fields

	//Protected Methods
	std::string Setup();
public:
	//Constructor
	StageMainMenu();

	//Public Methods
	std::string Update(std::string input);
};

#endif