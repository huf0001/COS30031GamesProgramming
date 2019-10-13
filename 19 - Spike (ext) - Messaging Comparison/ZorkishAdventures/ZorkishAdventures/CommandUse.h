#include "pch.h"

#ifndef COMMANDUSE_H
#define COMMANDUSE_H

class CommandUse : Command
{
	//Private Fields

	//Private Methods
protected:
	//Protected Fields

	//Protected Methods

public:
	//Public Properties
	std::string GetSyntax();

	//Constructor
	CommandUse();

	//Public Methods
	std::string Process(std::vector<std::string> input, World* world, Player* player);
};

#endif
