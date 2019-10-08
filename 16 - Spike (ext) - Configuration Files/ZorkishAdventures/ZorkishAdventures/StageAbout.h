#include "pch.h"

#ifndef STAGEABOUT_H
#define STAGEABOUT_H

class StageAbout : Stage
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
	StageAbout();

	//Public Methods
	std::string Update(std::string input);
};

#endif
