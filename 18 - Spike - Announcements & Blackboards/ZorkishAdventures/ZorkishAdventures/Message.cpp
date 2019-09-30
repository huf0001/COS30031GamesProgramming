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

std::string Message::GetReceiverID()
{
	return receiverId;
}

std::string Message::GetForComponent()
{
	return forComponent;
}

std::any* Message::GetContent()
{
	return content;
}

//void Message::SetContent(std::any content)
//{
//	this->content = content;
//}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

Message::Message(std::string senderId, std::string receiverId, std::string forComponent, std::any* content)
{
	this->id = std::to_string(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
	this->senderId = senderId;
	this->receiverId = receiverId;
	this->forComponent = forComponent;
	this->content = content;
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------
