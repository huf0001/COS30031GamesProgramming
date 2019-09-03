#include "pch.h"

#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "Game.h"
#include "Stage.h"
#include "World.h"
#include "Player.h"
#include "StringManager.h"

#include <map>
#include <vector>
#include <string>
#include <sstream>

class Gameplay : Stage
{
private:
	//Private Fields
	std::map<std::string, World*> worlds;
	World* world;
	Player* player;
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
	std::string Look(std::vector<std::string> input);
	std::string TakeFrom(std::vector<std::string> input);
	std::string PutIn(std::vector<std::string> input);
	std::string Drop(std::vector<std::string> input);
};

#endif
