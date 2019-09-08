#include "pch.h"

#ifndef WORLD_H
#define WORLD_H

#include "Item.h"
#include "ContainerItem.h"
#include "Location.h"
#include "Path.h"

#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

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
	bool GetLoadedSuccessfully();
	Location* GetCurrentLocation();
	std::string GetName();

	//Constructor
	World(std::string filename);

	//Public Methods
	std::string DescribeCurrentLocation();
	std::string ViewItemsInCurrentLocation();
};

#endif
