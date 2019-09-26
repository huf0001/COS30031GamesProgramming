#include "GameObject.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

std::string GameObject::GetID()
{
	return id;
}

std::string GameObject::GetName()
{
	return name;
}

std::string GameObject::GetType()
{
	return type;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

GameObject::GameObject(std::string id, std::string name, std::string type)
{
	this->id = id;
	this->name = name;
	this->type = type;
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

bool GameObject::HasComponent(std::string component)
{
	for (std::pair<std::string, Component*> pair : components)
	{
		if (pair.first == component)
		{
			return true;
		}
	}

	return false;
}

void GameObject::AddComponent(Component* component)
{
	if (HasComponent(component->GetComponentID()))
	{
		std::cout << "GameObject " + id + " already has a " + component->GetComponentID();
	}
	else
	{
		components[component->GetComponentID()] = component;
	}
}

Component* GameObject::GetComponent(std::string component)
{
	for (std::pair<std::string, Component*> pair : components)
	{
		if (pair.first == component)
		{
			return pair.second;
		}
	}

	return nullptr;
}

void GameObject::RemoveComponent(std::string component)
{
	components.erase(component);
}
