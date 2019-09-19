#include "pch.h"

#ifndef COMMAND_H
#define COMMAND_H

class Command
{
private:
	//Private Fields

	//Private Methods

protected:
	//Protected Fields
	std::string name;
	std::vector<std::string> keywords;

	//Protected Methods
public:
	//Public Properties
	std::string GetName();

	//Constructor
	Command();

	//Public Methods
	void AddKeyword(std::string keyword);
	bool HasKeyword(std::string string);
	virtual bool CanProcess(std::vector<std::string> input, World* world, Player* player);
	virtual std::string Process(std::vector<std::string> input, World* world, Player* player) = 0;
};

#endif
