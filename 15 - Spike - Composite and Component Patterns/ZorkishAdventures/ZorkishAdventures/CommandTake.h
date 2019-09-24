#include "pch.h"

#ifndef COMMANDTAKE_H
#define COMMANDTAKE_H

class CommandTake : Command
{
private:
	//Private Fields

	//Private Methods
	std::vector<std::string> StandardiseInput(std::vector<std::string> input);
	std::string TakeFromContainer(std::vector<std::string> item, GameObject* containerFrom, Player* player);
protected:
	//Protected Fields

	//Protected Methods

public:
	//Public Properties
	std::string GetSyntax();

	//Constructor
	CommandTake();

	//Public Methods
	std::string Process(std::vector<std::string> input, World* world, Player* player);
};

#endif
