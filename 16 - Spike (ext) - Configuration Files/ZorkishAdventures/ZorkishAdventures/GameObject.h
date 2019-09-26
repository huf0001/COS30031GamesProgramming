#include "pch.h"

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject
{
private:
	//Private Fields

	//Private Methods

protected:
	//Protected Fields
	std::string id;
	std::string name;
	std::map<std::string, Component*> components;

	//Protected Methods

public:
	//Public Properties
	std::string GetID();
	std::string GetName();

	//Constructor
	GameObject(std::string id, std::string name);

	//Public Methods
	bool HasComponent(std::string component);
	void AddComponent(Component* component);
	Component* GetComponent(std::string component);
	void RemoveComponent(std::string component);
};

#endif