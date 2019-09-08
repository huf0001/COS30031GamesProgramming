#ifndef HALLOFFAME_H
#define HALLOFFAME_H

#include <string>
#include "Stage.h"
#include "Game.h"

class HallOfFame : Stage
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
	HallOfFame();

	//Public Methods
	std::string Update(std::string input);
};

#endif
