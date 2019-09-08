#ifndef SELECTADVENTURE_H
#define SELECTADVENTURE_H

#include "Stage.h"
#include "Game.h"
#include "StageManager.h"
#include "Gameplay.h"

class SelectAdventure : Stage
{
private:
	//Private Fields

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
