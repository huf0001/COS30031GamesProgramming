#include "pch.h"

#ifndef LOCATION_H
#define LOCATION_H

#include <map>
#include <string>

class Location
{
private:
	//Private Fields
	std::string name;
	std::string description;
	std::map<std::string, Location*> neighbours;

	//Private Methods

public:
	//Public Properties
	std::string GetName();
	std::string GetDescription();

	//Constructor
	Location(std::string name, std::string description);

	//Public Methods
	//std::string Move(std::string direction);
};

#endif
