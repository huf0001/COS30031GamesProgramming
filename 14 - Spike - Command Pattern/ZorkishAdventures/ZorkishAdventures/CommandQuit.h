#include "pch.h"

#ifndef COMMANDQUIT_H
#define COMMANDQUIT_H

class CommandQuit : Command
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
	CommandQuit();

	//Public Methods
	std::string Process(std::vector<std::string> input, World* world, Player* player);
};

#endif
