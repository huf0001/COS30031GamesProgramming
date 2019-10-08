#include "pch.h"

#ifndef COMMANDDEBUG_H
#define COMMANDDEBUG_H

class CommandDebug : Command
{
private:
	//Private Fields

	//Private Methods
	std::string DebugPlayer(Player* player);
	std::string DebugWorld(World* world);
	std::string DebugLocation(Location* location);
	std::string DebugPath(Path* path, std::string locationId, std::string pathDirection);
	std::string DebugItem(Item* item, std::string containerId);
protected:
	//Protected Fields

	//Protected Methods

public:
	//Public Properties
	std::string GetSyntax();

	//Constructor
	CommandDebug();

	//Public Methods
	std::string Process(std::vector<std::string> input, World* world, Player* player);
};

#endif
