#include "pch.h"

#ifndef WORLD_H
#define WORLD_H

class World
{
private:
	//Private Fields
	std::string name;
	std::map<std::string, Location*> locations;
	Location* currentLocation;
	bool loadedSuccessfully;

	//Private Methods

public:
	//Public Properties
	Location* GetCurrentLocation();
	void SetCurrentLocation(Location* value);
	bool GetLoadedSuccessfully();
	std::string GetName();

	//Constructor
	World(std::string filename);

	//Public Methods
	std::string DescribeCurrentLocation();
	std::string ViewItemsInCurrentLocation();
	std::string ViewPathsAtCurrentLocation();
	bool HasLocation(std::string location);
	Location* GetLocation(std::string location);
};

#endif
