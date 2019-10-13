#include "pch.h"

#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

class ComponentFactory
{
private:
	//Enum
	enum ComponentType
	{
		ComponentButton,
		ComponentContainer,
		ComponentDescription,
		ComponentFlammable,
		ComponentLandmine,
		ComponentLock,
		ComponentMovable,
		ComponentUnlockCommands
	};

	//Private Fields
	static ComponentFactory* instance;
	std::map<std::string, ComponentType> componentTypes;

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
	bool ComponentTypeExists(std::string type);
};

#endif
