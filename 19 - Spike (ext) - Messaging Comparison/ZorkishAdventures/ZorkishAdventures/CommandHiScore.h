#include "pch.h"

#ifndef COMMANDHISCORE_H
#define COMMANDHISCORE_H

class CommandHiScore : Command
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
	CommandHiScore();

	//Public Methods
	std::string Process(std::vector<std::string> input, World* world, Player* player);
};

#endif
