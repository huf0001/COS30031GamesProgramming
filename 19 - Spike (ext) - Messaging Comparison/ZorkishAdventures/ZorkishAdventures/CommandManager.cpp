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
	allCommands = std::map<std::string, Command*>();
	allCommands["look"] = (Command*) new CommandLook();
	allCommands["move"] = (Command*) new CommandMove();
	allCommands["open"] = (Command*) new CommandOpen();
	allCommands["take"] = (Command*) new CommandTake();
	allCommands["put"] = (Command*) new CommandPut();
	allCommands["drop"] = (Command*) new CommandDrop();
	allCommands["use"] = (Command*) new CommandUse();
	allCommands["help"] = (Command*) new CommandHelp();
	allCommands["quit"] = (Command*) new CommandQuit();
	allCommands["alias"] = (Command*) new CommandAlias();
	allCommands["debug"] = (Command*) new CommandDebug();
	allCommands["hiscore"] = (Command*) new CommandHiScore();

	availableCommands = std::map<std::string, Command*>();
	availableCommands["look"] = allCommands["look"];
	availableCommands["help"] = allCommands["help"];
	availableCommands["quit"] = allCommands["quit"];

	unavailableCommands = std::map<std::string, Command*>();
	unavailableCommands["move"] = allCommands["move"];
	unavailableCommands["open"] = allCommands["open"];
	unavailableCommands["take"] = allCommands["take"];
	unavailableCommands["put"] = allCommands["put"];
	unavailableCommands["drop"] = allCommands["drop"];
	unavailableCommands["use"] = allCommands["use"];
	unavailableCommands["alias"] = allCommands["alias"];
	unavailableCommands["debug"] = allCommands["debug"];
	unavailableCommands["hiscore"] = allCommands["hiscore"];
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
					result += "\nError: Command " + pair.second->GetName() + " is already unlocked.";
				}
				else if (!unavailableCommands.count(pair.first))
				{
					result += "\nError: Command " + pair.second->GetName() + " is not available to be unlocked.";
				}
				else
				{
					unlockedCommands.push_back(pair.first);
					availableCommands[pair.first] = pair.second;
					result += "\nNew command unlocked: Command " + pair.second->GetName() + ".";
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

std::string CommandManager::GetCommandSyntaxes(bool getAllCommands)
{
	std::string result;
	std::map<std::string, Command*> commands;

	if (getAllCommands)
	{
		commands = allCommands;
	}
	else
	{
		commands = availableCommands;
	}

	for (std::pair<std::string, Command*> pair : commands)
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

void CommandManager::LockCommands()
{
	for (std::pair<std::string, Command*> pair : availableCommands)
	{
		if (pair.first != "look" && pair.first != "help" && pair.first != "quit")
		{
			unavailableCommands[pair.first] = pair.second;
		}
	}

	for (std::pair<std::string, Command*> pair : unavailableCommands)
	{
		if (availableCommands.count(pair.first))
		{
			availableCommands.erase(pair.first);
		}
	}
}

void CommandManager::ResetAliases()
{
	for (std::pair<std::string, Command*> pair : availableCommands)
	{
		pair.second->ResetAliases();
	}
}