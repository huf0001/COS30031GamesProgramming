#include "Description.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

std::string Description::GetDescription()
{
	return description;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

Description::Description(GameObject* gameObject, std::string description) : Component("description", gameObject)
{
	this->description = description;
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------
