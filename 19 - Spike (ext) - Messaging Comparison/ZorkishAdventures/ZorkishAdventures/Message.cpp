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

std::string Message::GetReceiverID()
{
	return receiverId;
}

std::string Message::GetReceiverType()
{
	return receiverType;
}

void* Message::GetContent()
{
	return content;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

Message::Message(std::string senderId, std::string senderType, std::string receiverId, std::string receiverType, void* content)
{
	this->id = std::to_string(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
	this->senderId = senderId;
	this->senderType = senderType;
	this->receiverId = receiverId;
	this->receiverType = receiverType;
	this->content = content;
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------
