#include "pch.h"

#ifndef STAGEGAMEPLAY_H
#define STAGEGAMEPLAY_H

class StageGameplay : Stage
{
private:
	//Private Fields
	World* world;
	Player* player;

	//Private Methods

protected:
	//Protected Fields

	//Protected Methods
	std::string Setup();
public:
	//Public Properties
	std::string GetCurrentWorldName();
	void SetWorld(World* world);

	//Constructor
	StageGameplay();

	//Public Methods
	std::string Update(std::string input);
};

#endif
