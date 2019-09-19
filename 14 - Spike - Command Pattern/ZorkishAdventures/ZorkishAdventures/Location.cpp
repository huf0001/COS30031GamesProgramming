#include "pch.h"

#include "Location.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

void Location::AddPath(std::string direction, Path* path)
{
	if (paths.count(direction))
	{
		std::cout << "Warning: overwriting paths[" << direction << "] with a new path.\n\n";
	}
	
	paths[direction] = path;
}


std::string Location::GetName()
{
	return name;
}

std::string Location::GetDescription()
{
	return description;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

Location::Location(std::string id, std::string name, std::string description)
{
	this->id = id;
	this->name = name;
	this->description = description;
	paths = std::map<std::string, Path*>();
}

//Public Methods-------------------------------------------------------------------------------------------------------------------------------------

std::string Location::ViewPaths()
{
	if (paths.empty())
	{
		return "";
	}

	std::string result = "";

	for (std::pair<std::string, Path*> p: paths)
	{
		result += "\n\t- " + p.second->GetDescription();
	}

	return result;
}

bool Location::HasPath(std::string direction)
{
	for(std::pair<std::string, Path*> p: paths)
	{
		if (p.first == direction)
		{
			return true;
		}
	}
	
	return false;
}

Path* Location::GetPath(std::string direction)
{
	for (std::pair<std::string, Path*> p : paths)
	{
		if (p.first == direction)
		{
			return p.second;
		}
	}
	
	return nullptr;
}

