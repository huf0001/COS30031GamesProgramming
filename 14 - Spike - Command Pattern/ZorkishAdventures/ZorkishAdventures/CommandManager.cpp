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
	commands["take"] = (Command*) new CommandTake();
	commands["put"] = (Command*) new CommandPut();
	commands["drop"] = (Command*) new CommandDrop();
	commands["help"] = (Command*) new CommandHelp();
	commands["hiscore"] = (Command*) new CommandHiScore();
	commands["quit"] = (Command*) new CommandQuit();
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

std::string CommandManager::GetCommandSyntaxes()
{
	std::string result;

	for (std::pair<std::string, Command*> pair : commands)
	{
		result += "\n" + pair.second->GetSyntax();
	}

	return result;
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

void CommandManager::ResetAliases()
{
	for (std::pair<std::string, Command*> pair : commands)
	{
		pair.second->ResetAliases();
	}
}