#include "Message.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

std::string Message::GetID()
{
	return id;
}

std::string Message::GetSenderID()
{
	return senderId;
}

std::string Message::GetSenderType()
{
	return senderType;
}

std::string Message::GetSenderParentID()
{
	return senderParentId;
}

std::string Message::GetSenderParentType()
{
	return senderParentType;
}

std::string Message::GetReceiverID()
{
	return receiverId;
}

std::string Message::GetReceiverType()
{
	return receiverType;
}

std::string Message::GetReceiverParentID()
{
	return receiverParentId;
}

std::string Message::GetReceiverParentType()
{
	return receiverParentType;
}

void* Message::GetContent()
{
	return content;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

Message::Message(std::string senderId, std::string senderType, std::string senderParentId, std::string senderParentType, std::string receiverId, std::string receiverType, std::string receiverParentId, std::string receiverParentType, void* content)
{
	this->id = std::to_string(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
	this->senderId = senderId;
	this->senderType = senderType;
	this->senderParentId = senderParentId;
	this->senderParentType = senderParentType;
	this->receiverId = receiverId;
	this->receiverType = receiverType;
	this->receiverParentId = receiverParentId;
	this->receiverParentType = receiverParentType;
	this->content = content;
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------
