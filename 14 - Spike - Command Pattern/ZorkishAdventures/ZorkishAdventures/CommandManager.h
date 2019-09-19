#include "pch.h"

#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

class CommandManager
{
private:
	static CommandManager* instance;
	std::map<std::string, Command*> commands;
public:
	//Public Properties
	static CommandManager* Instance();

	//Constructor
	CommandManager();

	//Public Methods
	Command* GetCommand(std::string command);
	bool CanProcess(std::vector<std::string> input, World* world, Player* player);
	std::string Process(std::vector<std::string> input, World* world, Player* player);
};

#endif
