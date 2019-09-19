#include "pch.h"

#ifndef STAGEMAINMENU_H
#define STAGEMAINMENU_H

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