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
	std::string receiverId;
	std::string forComponent;
	std::any* content;

	//Private Methods

protected:
	//Protected Fields

	//Protected Methods

public:
	//Public Properties
	std::string GetID();
	std::string GetSenderID();
	std::string GetReceiverID();
	std::string GetForComponent();
	std::any* GetContent();

	/*template <typename T>
	void SetContent(const std::vector<T>& content);*/
	//void SetContent(std::any content);

	//Constructor
	Message(std::string senderId, std::string receiverId, std::string forComponent, std::any* content);

	//Public Methods

};

#endif
