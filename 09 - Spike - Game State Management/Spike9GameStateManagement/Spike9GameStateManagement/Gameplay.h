#include "pch.h"

#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "Game.h"
#include "Stage.h"
#include "World.h"

#include <map>

class Gameplay : Stage
{
private:
	//Private Fields
	std::map<std::string, World*> worlds;
	World* currentWorld;

	//Private Methods

protected:
	//Protected Fields

	//Protected Methods
	std::string Setup();
public:
	//Public Properties
	std::string GetCurrentWorldName();

	//Constructor
	Gameplay();

	//Public Methods
	std::string SetWorld(std::string world);
	std::string Update(std::string input);
};

#endif
