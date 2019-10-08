#include "pch.h"

#ifndef LOCATION_H
#define LOCATION_H

class Location : public GameObject //: public Container
{
private:
	//Private Fields
	//std::string id;
	/*std::string name;
	std::string description;*/
	std::map<std::string, Path*> paths;

	//Private Methods

public:
	//Public Properties
	//std::string GetID();
	/*std::string GetName();
	std::string GetDescription();*/

	//Constructor
	Location(std::string id, std::string name, std::string description);

	//Public Methods
	bool HasPath(std::string);
	void AddPath(std::string direction, Path* path);
	Path* GetPath(std::string);
	std::map<std::string, Path*> GetPaths();	//For testing only
	std::string ViewPaths();
};

#endif
