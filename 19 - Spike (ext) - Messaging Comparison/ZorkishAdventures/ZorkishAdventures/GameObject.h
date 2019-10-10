#include "pch.h"

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject : public Notifiable
{
private:
	//Private Fields

	//Private Methods

protected:
	//Protected Fields
	std::string id;
	std::string name;
	std::string type;
	std::map<std::string, Component*> components;
	std::string parentId;
	std::string parentType;

	//Protected Methods

public:
	//Public Properties
	std::string GetID();
	std::string GetName();
	std::string GetType();
	std::string GetParentID();
	void SetParentID(std::string value);
	std::string GetParentType();
	void SetParentType(std::string value);

	//Constructor
	GameObject(std::string id, std::string name, std::string type);

	//Public Methods
	bool HasComponent(std::string component);
	void AddComponent(Component* component);
	Component* GetComponent(std::string component);
	void RemoveComponent(std::string component);
	virtual Message* Notify(Message* message);
};

#endif