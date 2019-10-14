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

std::string GameObject::GetParentID()
{
	return parentId;
}

void GameObject::SetParentID(std::string value)
{
	parentId = value;
}

std::string GameObject::GetParentType()
{
	return parentType;
}

void GameObject::SetParentType(std::string value)
{
	parentType = value;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

GameObject::GameObject(std::string id, std::string name, std::string type)
{
	this->id = id;
	this->name = name;
	this->type = type;
	this->parentId = "null";
	this->parentType = "null";
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

Message* GameObject::Notify(Message* message)
{
	std::string receiverType = message->GetReceiverType();
	
	if (receiverType == "gameObject")
	{
		std::vector<std::string> messageContent = *(std::vector<std::string>*) message->GetContent();

		if (messageContent[0] == "has component")
		{
			return new Message(
				id, type,
				parentId, parentType,
				message->GetSenderID(), message->GetSenderType(),
				message->GetSenderParentID(), message->GetSenderParentType(),
				(void*) new std::string(HasComponent(messageContent[1]) ? "Yes" : "No")
			);
		}
	}
	else if (receiverType == type)
	{
		std::vector<void*> messageContent = *(std::vector<void*>*) message->GetContent();

		if (*(std::string*)messageContent[0] == "remove" && HasComponent("container"))
		{
			Container* containerComponent = (Container*)GetComponent("container");
			containerComponent->RemoveItem(*(std::vector<std::string>*)messageContent[2]);
		}
	}
	else if (HasComponent(receiverType))
	{
		return GetComponent(receiverType)->Notify(message);
	}

	return nullptr;
}
