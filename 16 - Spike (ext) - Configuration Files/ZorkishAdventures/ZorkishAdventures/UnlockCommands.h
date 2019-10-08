#include "pch.h"

#ifndef UNLOCKCOMMANDS_H
#define UNLOCKCOMMANDS_H

class UnlockCommands : Component
{
private:
	//Private Fields
	std::vector<std::string> commands;

	//Private Methods

protected:
	//Protected Fields

	//Protected Methods

public:
	//Public Properties
	std::vector<std::string> GetCommands();

	//Constructor
	UnlockCommands(GameObject* gameObject, std::vector<std::string>);

	//Public Methods

};

#endif
