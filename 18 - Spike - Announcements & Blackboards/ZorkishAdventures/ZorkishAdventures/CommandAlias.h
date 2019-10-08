#include "pch.h"

#ifndef COMMANDALIAS_H
#define COMMANDALIAS_H

class CommandAlias : Command
{
private:
	//Private Fields

	//Private Methods
protected:
	//Protected Fields

	//Protected Methods

public:
	//Public Properties
	std::string GetSyntax();

	//Constructor
	CommandAlias();

	//Public Methods
	std::string Process(std::vector<std::string> input, World* world, Player* player);
};

#endif
