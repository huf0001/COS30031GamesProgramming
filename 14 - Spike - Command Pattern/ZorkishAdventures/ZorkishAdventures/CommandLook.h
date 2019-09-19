#include "pch.h"

#ifndef COMMANDLOOK_H
#define COMMANDLOOK_H

class CommandLook : Command
{
private:
	//Private Fields

	//Private Methods
	std::string LookAtLocation(World* world);
	std::string LookAtInventory(Player* player);
protected:
	//Protected Fields

	//Protected Methods

public:
	//Public Properties

	//Constructor
	CommandLook();

	//Public Methods
	std::string Process(std::vector<std::string> input, World* world, Player* player);
};

#endif
