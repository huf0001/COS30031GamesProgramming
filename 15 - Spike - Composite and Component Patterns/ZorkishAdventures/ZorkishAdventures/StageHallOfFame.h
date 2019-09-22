#include "pch.h"

#ifndef STAGEHALLOFFAME_H
#define STAGEHALLOFFAME_H

class StageHallOfFame : Stage
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
	StageHallOfFame();

	//Public Methods
	std::string Update(std::string input);
};

#endif
