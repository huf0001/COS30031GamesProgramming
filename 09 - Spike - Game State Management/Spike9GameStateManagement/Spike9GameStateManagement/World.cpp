#include "pch.h"

#include "World.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

std::string World::GetName()
{
	return name;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

World::World(std::string name)
{
	//Assign to fields
	this->name = name;
	locations = std::map<std::string, Location*>();

	//Setup locations in world
	locations["Void"] = new Location("The Void", "This world is simple and pointless. Used to test Zorkish phase 1 spec.");

	//Set starting location
	currentLocation = locations["Void"];
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

std::string World::DescribeCurrentLocation()
{
	return (*currentLocation).GetDescription();
}