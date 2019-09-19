#include "pch.h"

#ifndef COMMANDMOVE_H
#define COMMANDMOVE_H

class CommandMove : Command
{
private:
	//Private Fields
	std::map<std::string, std::string> directionAliases;

	//Private Methods
	std::string DeAliasDirection(std::string direction);
protected:
	//Protected Fields

	//Protected Methods

public:
	//Public Properties
	void SetDirectionAliases(std::map<std::string, std::string> directionAliases);

	//Constructor
	CommandMove();

	//Public Methods
	void AddDirectionAlias(std::string direction, std::string alias);
	bool HasDirectionWithAlias(std::string alias);
	std::string GetDirectionWithAlias(std::string alias);

	bool CanProcess(std::vector<std::string> input, World* world, Player* player);
	std::string Process(std::vector<std::string> input, World* world, Player* player);
};

#endif
