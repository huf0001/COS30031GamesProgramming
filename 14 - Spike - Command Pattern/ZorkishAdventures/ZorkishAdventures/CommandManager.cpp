#include "pch.h"

#include "CommandManager.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

CommandManager* CommandManager::instance = 0;

CommandManager* CommandManager::Instance()
{
	if (!instance)
	{
		instance = new CommandManager();
	}

	return instance;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

CommandManager::CommandManager()
{
	commands = std::map<std::string, Command*>();
	commands["look"] = (Command*) new CommandLook();
	commands["move"] = (Command*) new CommandMove();
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

Command* CommandManager::GetCommand(std::string command)
{
	if (commands.find(command) == commands.end())
	{
		return nullptr;
	}
	else
	{
		return commands[command];
	}
}

bool CommandManager::CanProcess(std::vector<std::string> input, World* world, Player* player)
{
	for (std::pair<std::string, Command*> pair : commands)
	{
		if (pair.second->CanProcess(input, world, player))
		{
			return true;
		}
	}

	return false;
}

std::string CommandManager::Process(std::vector<std::string> input, World* world, Player* player)
{
	for (std::pair<std::string, Command*> pair : commands)
	{
		if (pair.second->CanProcess(input, world, player))
		{
			return pair.second->Process(input, world, player);
		}
	}

	return "Error";
}