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
	std::vector<std::string> aliases;

	//Protected Methods

public:
	//Public Properties
	std::string GetName();
	virtual std::string GetSyntax() = 0;

	//Constructor
	Command();

	//Public Methods
	void AddKeyword(std::string keyword);
	void AddAlias(std::string alias);
	bool HasKeyword(std::string string);
	bool HasAlias(std::string string);
	virtual bool CanProcess(std::vector<std::string> input, World* world, Player* player);
	virtual std::string Process(std::vector<std::string> input, World* world, Player* player) = 0;
	virtual void ResetAliases();
};

#endif
