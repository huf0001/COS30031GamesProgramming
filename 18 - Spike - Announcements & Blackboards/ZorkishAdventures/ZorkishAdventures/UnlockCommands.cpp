#include "UnlockCommands.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

std::vector<std::string> UnlockCommands::GetCommands()
{
	return commands;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

UnlockCommands::UnlockCommands(GameObject* gameObject, std::vector<std::string> commands) : Component("unlock_commands", gameObject)
{
	this->commands = commands;
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

