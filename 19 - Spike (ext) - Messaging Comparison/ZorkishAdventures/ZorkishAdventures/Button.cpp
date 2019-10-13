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
		return MessageManager::Instance()->SendMessage(new Message(
			gameObject->GetID(), gameObject->GetType(),
			gameObject->GetParentID(), gameObject->GetParentType(),
			"all", triggersType,
			triggersAtLocation, "location",
			(void*) new std::string("trigger")
		));
	}
}
