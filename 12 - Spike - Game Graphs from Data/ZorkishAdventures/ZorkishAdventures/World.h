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
	std::map<std::string, std::string> directionAliases;
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
	bool HasDirectionWithAlias(std::string alias);
	std::string GetDirectionWithAlias(std::string alias);
};

#endif
