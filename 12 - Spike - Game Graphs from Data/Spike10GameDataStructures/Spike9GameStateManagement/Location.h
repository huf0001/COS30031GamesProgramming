#include "pch.h"

#ifndef LOCATION_H
#define LOCATION_H

#include "Container.h"

#include <map>
#include <string>

class Location : public Container
{
private:
	//Private Fields
	std::string id;
	std::string name;
	std::string description;
	std::map<std::string, Location*> neighbours;

	//Private Methods

public:
	//Public Properties
	std::string GetName();
	std::string GetDescription();

	//Constructor
	Location(std::string id, std::string name, std::string description);

	//Public Methods
	//std::string Move(std::string direction);
};

#endif
