#include "pch.h"

#ifndef HELP_H
#define HELP_H

#include "Stage.h"

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
	Help();

	//Public Methods
	std::string Update(std::string input);
};

#endif
