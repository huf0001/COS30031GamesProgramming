#include "pch.h"

#ifndef LOCATION_H
#define LOCATION_H

#include "Container.h"
#include "Path.h"

#include <map>
#include <string>
#include <iostream>

class Location : public Container
{
private:
	//Private Fields
	std::string id;
	std::string name;
	std::string description;
	std::map<std::string, Path*> paths;

	//Private Methods

public:
	//Public Properties
	std::string GetName();
	std::string GetDescription();
	void AddPath(std::string direction, Path* path);

	//Constructor
	Location(std::string id, std::string name, std::string description);

	//Public Methods
	//std::string Move(std::string direction);
};

#endif
