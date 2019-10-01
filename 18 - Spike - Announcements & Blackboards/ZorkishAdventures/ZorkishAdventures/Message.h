#include "pch.h"

#ifndef MESSAGE_H
#define MESSAGE_H

class GameObject;

class Message
{
private:
	//Private Fields
	std::string id;
	std::string senderId;
	std::string senderType;
	std::string receiverId;
	std::string receiverType;
	void* content;

	//Private Methods

protected:
	//Protected Fields

	//Protected Methods

public:
	//Public Properties
	std::string GetID();
	std::string GetSenderID();
	std::string GetSenderType();
	std::string GetReceiverID();
	std::string GetReceiverType();
	void* GetContent();

	//Constructor
	Message(std::string senderId, std::string senderType, std::string receiverId, std::string receiverType, void* content);

	//Public Methods

};

#endif
