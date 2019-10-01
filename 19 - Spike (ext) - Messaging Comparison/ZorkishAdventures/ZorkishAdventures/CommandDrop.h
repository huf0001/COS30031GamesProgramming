#include "pch.h"

#ifndef COMMANDDROP_H
#define COMMANDDROP_H

class CommandDrop : Command
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
	CommandDrop();

	//Public Methods
	std::string Process(std::vector<std::string> input, World* world, Player* player);
};

#endif
