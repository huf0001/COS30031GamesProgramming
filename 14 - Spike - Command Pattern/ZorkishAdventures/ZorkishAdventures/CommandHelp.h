#include "pch.h"

#ifndef COMMANDHELP_H
#define COMMANDHELP_H

class CommandHelp : Command
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
	CommandHelp();

	//Public Methods
	std::string Process(std::vector<std::string> input, World* world, Player* player);
};

#endif
