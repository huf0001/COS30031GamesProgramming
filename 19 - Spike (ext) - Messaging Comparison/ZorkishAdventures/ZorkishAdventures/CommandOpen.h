#include "pch.h"

#ifndef COMMANDOPEN_H
#define COMMANDOPEN_H

class CommandOpen : Command
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
	CommandOpen();

	//Public Methods
	std::string Process(std::vector<std::string> input, World* world, Player* player);
};

#endif
