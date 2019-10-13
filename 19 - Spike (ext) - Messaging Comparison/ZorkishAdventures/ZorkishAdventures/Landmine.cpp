#include "Landmine.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

Landmine::Landmine(GameObject* gameObject) : Component("landmine", gameObject)
{

}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

Message* Landmine::Notify(Message* message)
{
	std::string messageContent = *(std::string*)message->GetContent();

	if (messageContent == "trigger")
	{
		std::string output = "";
		Message* msgIgnite = new Message(
			gameObject->GetID(), gameObject->GetType(),
			gameObject->GetParentID(), gameObject->GetParentType(),
			"all", "flammable",
			gameObject->GetParentID(), gameObject->GetParentType(),
			(void*) new std::string("ignite")
		);
		Message* replyIgnite = MessageManager::Instance()->SendMessage(msgIgnite);
		std::vector<Message*>* replies = (std::vector<Message*>*)replyIgnite->GetContent();

		if (replies->size() == 0)
		{
			output = "Nothing happens.\n";
		}
		else
		{
			for (Message* message : *replies)
			{
				//TODO: process message replies
			}
		}

		MessageManager::Instance()->SendQueuedMessages("remove");

		return new Message(
			//TODO: compile output into reply message
		);
	}

	return nullptr;
}
