#include "Component.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

std::string Component::GetComponentID()
{
	return componentId;
}

GameObject* Component::GetGameObject()
{
	return gameObject;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

Component::Component(std::string id, GameObject* gameObject)
{
	this->componentId = id;
	this->gameObject = gameObject;
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------


