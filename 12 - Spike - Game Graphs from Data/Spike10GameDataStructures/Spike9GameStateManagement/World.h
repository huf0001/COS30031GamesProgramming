#include "pch.h"

#ifndef WORLD_H
#define WORLD_H

#include "Location.h"
#include "Item.h"
#include "ContainerItem.h"
#include <map>
#include <string>

class World
{
private:
	//Private Fields
	std::string name;
	std::map<std::string, Location*> locations;
	Location* currentLocation;

	//Private Methods

public:
	//Public Properties
	std::string GetName();
	Location* GetCurrentLocation();

	//Constructor
	World(std::string name);

	//Public Methods
	std::string DescribeCurrentLocation();
	std::string ViewItemsInCurrentLocation();
};

#endif
