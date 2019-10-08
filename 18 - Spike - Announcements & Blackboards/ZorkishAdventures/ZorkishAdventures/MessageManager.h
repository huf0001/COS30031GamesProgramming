#include "pch.h"

#ifndef MESSAGEMANAGER_H
#define MESSAGEMANAGER_H

class GameObject;

class MessageManager
{
private:
	//Private Fields
	static MessageManager* instance;
	std::map<std::string, GameObject*> subscribers;

	//Constructor
	MessageManager();

	//Private Methods

protected:
	//Protected Fields

	//Protected Methods

public:
	//Public Properties
	static MessageManager* Instance();

	//Public Methods
	void Subscribe(GameObject* subscriber);
	void Unsubscribe(std::string subscriberId);
	void UnsubscribeAll();
	Message* SendMessage(Message* message);
};

#endif