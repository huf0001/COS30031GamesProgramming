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
	commands["open"] = (Command*) new CommandOpen();
	commands["take"] = (Command*) new CommandTake();
	commands["put"] = (Command*) new CommandPut();
	commands["drop"] = (Command*) new CommandDrop();
	commands["help"] = (Command*) new CommandHelp();
	commands["alias"] = (Command*) new CommandAlias();
	commands["debug"] = (Command*) new CommandDebug();
	commands["hiscore"] = (Command*) new CommandHiScore();
	commands["quit"] = (Command*) new CommandQuit();
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

bool CommandManager::HasCommand(std::string command)
{
	for (std::pair<std::string, Command*> pair : commands)
	{
		if (pair.second->HasKeyword(command) || pair.second->HasAlias(command))
		{
			return true;
		}
	}

	return false;
}

Command* CommandManager::GetCommand(std::string command)
{

	for (std::pair<std::string, Command*> pair : commands)
	{
		if (pair.second->HasKeyword(command) || pair.second->HasAlias(command))
		{
			return pair.second;
		}
	}

	return nullptr;
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