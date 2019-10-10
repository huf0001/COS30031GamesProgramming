#include "pch.h"

#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;

class Component : public Notifiable
{
private:
	//Private Fields

	//Private Methods

protected:
	//Protected Fields
	std::string componentId;
	GameObject* gameObject;

	//Protected Methods

public:
	//Public Properties
	std::string GetComponentID();
	GameObject* GetGameObject();

	//Constructor
	Component(std::string id, GameObject* gameObject);

	//Public Methods

};

#endif