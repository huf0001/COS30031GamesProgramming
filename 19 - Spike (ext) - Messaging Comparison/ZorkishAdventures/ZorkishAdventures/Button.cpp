#include "Button.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

Button::Button(GameObject* gameObject, std::string triggersType, std::string triggersAtLocation) : Component("button", gameObject)
{
	this->triggersType = triggersType;
	this->triggersAtLocation = triggersAtLocation;
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

Message* Button::Notify(Message* message)
{
	std::string messageContent = *(std::string*)message->GetContent();

	if (messageContent == "use")
	{
		Message* msgTrigger = new Message(
			gameObject->GetID(), gameObject->GetType(),
			gameObject->GetParentID(), gameObject->GetParentType(),
			"all", triggersType,
			triggersAtLocation, "location",
			(void*) new std::string("trigger")
		);
		Message* replyTrigger = MessageManager::Instance()->SendMessage(msgTrigger);
		std::vector<std::string> replyStrings;

		if (replyTrigger != nullptr)
		{
			std::vector<Message*> replyMessages = *(std::vector<Message*>*)replyTrigger->GetContent();

			for (Message* replyMessage : replyMessages)
			{
				std::vector<std::string> replyVector = *(std::vector<std::string>*)replyMessage->GetContent();

				for (std::string replyString : replyVector)
				{
					replyStrings.push_back(replyString);
				}
			}	
		}		

		if (replyStrings.size() == 0)
		{
			replyStrings.push_back(std::string("Nothing happens."));
		}

		return new Message(
			gameObject->GetID(), "button",
			gameObject->GetParentID(), gameObject->GetParentType(),
			message->GetSenderID(), message->GetSenderType(),
			message->GetSenderParentID(), message->GetSenderParentType(),
			(void*) new std::vector<std::string>(replyStrings)
		);
	}

	return nullptr;
}
