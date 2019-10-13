#include "ComponentFactory.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

ComponentFactory* ComponentFactory::instance = 0;

ComponentFactory* ComponentFactory::Instance()
{
	if (!instance)
	{
		instance = new ComponentFactory();
	}

	return instance;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

ComponentFactory::ComponentFactory()
{
	componentTypes = std::map<std::string, ComponentType>();
	componentTypes["button"] = ComponentType::ComponentButton;
	componentTypes["container"] = ComponentType::ComponentContainer;
	componentTypes["description"] = ComponentType::ComponentDescription;
	componentTypes["flammable"] = ComponentType::ComponentFlammable;
	componentTypes["landmine"] = ComponentType::ComponentLandmine;
	componentTypes["lock"] = ComponentType::ComponentLock;
	componentTypes["movable"] = ComponentType::ComponentMovable;
	componentTypes["unlock_commands"] = ComponentType::ComponentUnlockCommands;
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

Component* ComponentFactory::CreateComponent(std::string componentId, GameObject* gameObject)
{
	switch (componentTypes[componentId])
	{
		//case ComponentType::ComponentButton:
		//	return (Component*) new Button(gameObject);
		case ComponentType::ComponentContainer:
			return (Component*) new Container(gameObject, false, false);
		//case ComponentType::ComponentDescription:
		//	return (Component*) new Description(gameObject);
		case ComponentType::ComponentFlammable:
			return (Component*) new Flammable(gameObject);
		case ComponentType::ComponentLandmine:
			return (Component*) new Landmine(gameObject);
		//case ComponentType::ComponentLock:
		//	return (Component*) new Lock(gameObject, true, std::vector<std::string>());
		case ComponentType::ComponentMovable:
			return (Component*) new Movable(gameObject);
		//case ComponentType::ComponentUnlockCommands:
		//	return (Component*) new UnlockCommands(gameObject);
		default:
			return nullptr;
	}
}

bool ComponentFactory::ComponentTypeExists(std::string type)
{
	return componentTypes.count(type);
}
