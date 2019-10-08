#include "pch.h"

#ifndef STAGEHELP_H
#define STAGEHELP_H

class StageHelp : Stage
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
	StageHelp();

	//Public Methods
	std::string Update(std::string input);
};

#endif
