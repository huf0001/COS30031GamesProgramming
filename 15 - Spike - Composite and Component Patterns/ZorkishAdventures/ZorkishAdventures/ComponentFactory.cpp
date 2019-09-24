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
	componentIds = std::map<std::string, ComponentID>();
	componentIds["container"] = ComponentID::ContainerID;
	//componentIds["description"] = ComponentID::DescriptionID;
	componentIds["lock"] = ComponentID::LockID;
	componentIds["movable"] = ComponentID::MovableID;
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

Component* ComponentFactory::CreateComponent(std::string componentId, GameObject* gameObject)
{
	switch (componentIds[componentId])
	{
		case ComponentID::ContainerID:
			return (Component*) new Container(gameObject);
		//case ComponentID::DescriptionID:
		//	return (Component*) new Description(gameObject);
		/*case ComponentID::LockID:
			return (Component*) new Lock(gameObject);*/
		case ComponentID::MovableID:
			return (Component*) new Movable(gameObject);
		default:
			return nullptr;
	}
}
