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

Location::Location(std::string name, std::string description)
{
	this->name = name;
	this->description = description;
	neighbours = std::map<std::string, Location*>();
}

//Public Methods-------------------------------------------------------------------------------------------------------------------------------------

//std::string Location::Move(std::string direction)
//{
//	return "";
//}