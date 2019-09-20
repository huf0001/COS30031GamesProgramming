#include "pch.h"

#ifndef COMMANDPUT_H
#define COMMANDPUT_H

class CommandPut : Command
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
	CommandPut();

	//Public Methods
	std::string Process(std::vector<std::string> input, World* world, Player* player);
};

#endif
