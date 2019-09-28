#include "pch.h"

#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

class CommandManager
{
private:
	static CommandManager* instance;
	std::map<std::string, Command*> allCommands;
	std::map<std::string, Command*> availableCommands;
	std::map<std::string, Command*> unavailableCommands;
	
	//Constructor
	CommandManager();
public:
	//Public Properties
	static CommandManager* Instance();	

	//Public Methods
	bool HasCommand(std::string command);
	std::string UnlockCommands(std::vector<std::string> commands);
	Command* GetCommand(std::string command);
	std::string GetCommandSyntaxes(bool getAllCommands);
	bool CanProcess(std::vector<std::string> input, World* world, Player* player);
	std::string Process(std::vector<std::string> input, World* world, Player* player);
	void ResetAliases();
};

#endif
