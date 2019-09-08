#ifndef SELECTADVENTURE_H
#define SELECTADVENTURE_H

#include "Stage.h"
#include "Game.h"
#include "StageManager.h"
#include "Gameplay.h"
#include "StringManager.h"

#include <fstream>
#include <string>
#include <map>
#include <vector>

class SelectAdventure : Stage
{
private:
	//Private Fields
	std::string worldsFilename;
	std::vector<std::string> worldNames;
	std::vector<std::string> worldFilenames;
	//Private Methods

protected:
	//Protected Fields

	//Protected Methods
	std::string Setup();
public:
	//Constructor
	SelectAdventure();

	//Public Methods
	std::string Update(std::string input);
	std::string SelectWorld(std::string world);
};

#endif
