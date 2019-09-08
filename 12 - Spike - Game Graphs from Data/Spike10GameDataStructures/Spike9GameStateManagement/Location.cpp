#include "pch.h"

#include "Location.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

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
	neighbours = std::map<std::string, Location*>();
}

//Public Methods-------------------------------------------------------------------------------------------------------------------------------------

//std::string Location::Move(std::string direction)
//{
//	return "";
//}