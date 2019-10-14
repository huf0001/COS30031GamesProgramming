#include "Landmine.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

Landmine::Landmine(GameObject* gameObject) : Component("landmine", gameObject)
{
	detonated = false;
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

Message* Landmine::Notify(Message* message)
{
	if (!detonated)
	{
		std::string messageContent = *(std::string*)message->GetContent();
		std::vector<std::string> flammableReplies = std::vector<std::string>();
		flammableReplies.push_back(std::string("A landmine EXPLODES!"));

		if (messageContent == "trigger")
		{
			detonated = true;

			Message* msgRemove = new Message(
				gameObject->GetID(), "landmine",
				gameObject->GetParentID(), gameObject->GetParentType(),
				gameObject->GetParentID(), gameObject->GetParentType(),
				"override", "any",
				(void*) new std::vector<void*>({ (void*)new std::string("remove"), (void*)new int(0) , (void*) new std::vector<std::string>({ StringManager::Instance()->ToLowercase(gameObject->GetName()) }) })
			);
			MessageManager::Instance()->QueueMessage(msgRemove);

			Message* msgIgnite = new Message(
				gameObject->GetID(), "landmine",
				gameObject->GetParentID(), gameObject->GetParentType(),
				"all", "flammable",
				gameObject->GetParentID(), gameObject->GetParentType(),
				(void*) new std::string("ignite")
			);
			Message* replyIgnite = MessageManager::Instance()->SendMessage(msgIgnite);
			std::vector<Message*>* replies = (std::vector<Message*>*)replyIgnite->GetContent();

			for (Message* reply : *replies)
			{
				if (reply != nullptr)
				{
					flammableReplies.push_back(*(std::string*)reply->GetContent());
				}
			}

			return new Message(
				gameObject->GetID(), "landmine",
				gameObject->GetParentID(), gameObject->GetParentType(),
				message->GetSenderID(), message->GetSenderType(),
				message->GetSenderParentID(), message->GetSenderParentType(),
				(void*) new std::vector<std::string>(flammableReplies)
			);
		}
	}

	return nullptr;
}
