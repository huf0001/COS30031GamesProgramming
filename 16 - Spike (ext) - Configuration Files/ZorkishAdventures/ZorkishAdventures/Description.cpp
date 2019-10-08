#include "Description.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

std::string Description::GetDescription()
{
	return description;
}

//std::string Description::SetDescription(std::string value)
//{
//	description = value;
//}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

//Description::Description(GameObject* gameObject) : Component("description", gameObject)
//{
//
//}

Description::Description(GameObject* gameObject, std::string description) : Component("description", gameObject)
{
	this->description = description;
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------
