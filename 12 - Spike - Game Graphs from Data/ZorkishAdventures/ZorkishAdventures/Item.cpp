#include "pch.h"

#include "Item.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

std::string Item::GetID()
{
	return id;
}

std::string Item::GetName()
{
	return name;
}

std::string Item::GetDescription()
{
	return description;
}

bool Item::GetIsContainer()
{
	return isContainer;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

Item::Item(std::string id, std::string name, std::string description)
{
	this->id = id;
	this->name = name;
	this->description = description;
	this->isContainer = false;
}

Item::Item(std::string id, std::string name, std::string description, bool isContainer)
{
	this->id = id;
	this->name = name;
	this->description = description;
	this->isContainer = isContainer;
}
