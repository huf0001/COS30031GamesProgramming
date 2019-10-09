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
	std::string senderParentId;
	std::string senderParentType;
	std::string receiverId;
	std::string receiverType;
	std::string receiverParentId;
	std::string receiverParentType;
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
	std::string GetSenderParentID();
	std::string GetSenderParentType();
	std::string GetReceiverID();
	std::string GetReceiverType();
	std::string GetReceiverParentID();
	std::string GetReceiverParentType();
	void* GetContent();

	//Constructor
	Message(std::string senderId, std::string senderType, std::string senderContainerId, std::string senderContainerType, std::string receiverId, std::string receiverType, std::string receiverContainerId, std::string receiverContainerType, void* content);

	//Public Methods

};

#endif
