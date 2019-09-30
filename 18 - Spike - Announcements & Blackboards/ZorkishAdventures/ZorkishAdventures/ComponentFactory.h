#include "pch.h"

#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

class ComponentFactory
{
private:
	//Enum
	enum ComponentID
	{
		ContainerID,
		//DescriptionID,
		LockID,
		MovableID
	};

	//Private Fields
	static ComponentFactory* instance;
	std::map<std::string, ComponentID> componentIds;

	//Constructor
	ComponentFactory();

	//Private Methods

protected:
	//Protected Fields

	//Protected Methods

public:
	//Public Properties
	static ComponentFactory* Instance();

	//Methods
	Component* CreateComponent(std::string componentId, GameObject* gameObject);
	//Component* CreateComponent(std::string componentId, GameObject* gameObject, std::string);
};

#endif
