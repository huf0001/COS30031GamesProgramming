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
	availableCommands = std::map<std::string, Command*>();
	availableCommands["look"] = (Command*) new CommandLook();
	availableCommands["help"] = (Command*) new CommandHelp();
	availableCommands["quit"] = (Command*) new CommandQuit();

	unavailableCommands = std::map<std::string, Command*>();
	unavailableCommands["move"] = (Command*) new CommandMove();
	unavailableCommands["open"] = (Command*) new CommandOpen();
	unavailableCommands["take"] = (Command*) new CommandTake();
	unavailableCommands["put"] = (Command*) new CommandPut();
	unavailableCommands["drop"] = (Command*) new CommandDrop();
	unavailableCommands["alias"] = (Command*) new CommandAlias();
	unavailableCommands["debug"] = (Command*) new CommandDebug();
	unavailableCommands["hiscore"] = (Command*) new CommandHiScore();
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

bool CommandManager::HasCommand(std::string command)
{
	for (std::pair<std::string, Command*> pair : availableCommands)
	{
		if (pair.second->HasKeyword(command) || pair.second->HasAlias(command))
		{
			return true;
		}
	}

	return false;
}

std::string CommandManager::UnlockCommands(std::vector<std::string> commands)
{
	std::string result;
	std::vector<std::string> unlockedCommands = std::vector<std::string>();

	for (std::pair<std::string, Command*> pair : unavailableCommands)
	{
		for (std::string command : commands)
		{
			if (command == pair.first || command == "all")
			{
				if (HasCommand(pair.first))
				{
					result += "Error: Command " + pair.second->GetName() + " is already unlocked.\n";
				}
				else if (!unavailableCommands.count(pair.first))
				{
					result += "Error: Command " + pair.second->GetName() + " is not available to be unlocked.\n";
				}
				else
				{
					unlockedCommands.push_back(pair.first);
					availableCommands[pair.first] = pair.second;
					result += "New command unlocked: command " + pair.second->GetName() + ".\n";
				}
			}
		}
	}

	for (std::string command : unlockedCommands)
	{
		unavailableCommands.erase(command);
	}

	return result;
}

Command* CommandManager::GetCommand(std::string command)
{

	for (std::pair<std::string, Command*> pair : availableCommands)
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

	for (std::pair<std::string, Command*> pair : availableCommands)
	{
		result += "\n" + pair.second->GetSyntax();
	}

	return result;
}

bool CommandManager::CanProcess(std::vector<std::string> input, World* world, Player* player)
{
	for (std::pair<std::string, Command*> pair : availableCommands)
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
	for (std::pair<std::string, Command*> pair : availableCommands)
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
	for (std::pair<std::string, Command*> pair : availableCommands)
	{
		pair.second->ResetAliases();
	}
}