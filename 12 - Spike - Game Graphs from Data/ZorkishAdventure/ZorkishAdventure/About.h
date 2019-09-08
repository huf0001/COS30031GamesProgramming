#ifndef ABOUT_H
#define ABOUT_H

#include <string>
#include "Stage.h"
#include "Game.h"

class About : Stage
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
	About();

	//Public Methods
	std::string Update(std::string input);
};

#endif
