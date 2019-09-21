#include "pch.h"

#ifndef LOCATION_H
#define LOCATION_H

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
	std::string GetID();
	std::string GetName();
	std::string GetDescription();
	void AddPath(std::string direction, Path* path);
	std::map<std::string, Path*> GetPaths();	//For testing only

	//Constructor
	Location(std::string id, std::string name, std::string description);

	//Public Methods
	std::string ViewPaths();
	bool HasPath(std::string);
	Path* GetPath(std::string);
};

#endif
