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
	/*std::string LookAtLocation();
	std::string LookAtInventory();*/
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
	/*std::string Look(std::vector<std::string> input);*/
	std::string TakeFrom(std::vector<std::string> input);
	std::string PutIn(std::vector<std::string> input);
	std::string Drop(std::vector<std::string> input);
	/*std::string Move(std::vector<std::string> input);*/
};

#endif
