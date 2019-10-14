#include "Flammable.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

Flammable::Flammable(GameObject* gameObject) : Component("flammable", gameObject)
{
	ignited = false;
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

Message* Flammable::Notify(Message* message)
{
	if (!ignited)
	{
		std::string messageContent = *(std::string*)message->GetContent();
	
		if (messageContent == "ignite")
		{
			ignited = true;

			Message* msgRemove = new Message(
				gameObject->GetID(), "flammable",
				gameObject->GetParentID(), gameObject->GetParentType(),
				gameObject->GetParentID(), gameObject->GetParentType(),
				"override", "any",
				(void*) new std::vector<void*>({ (void*)new std::string("remove"), (void*)new int(0) , (void*) new std::vector<std::string>({ StringManager::Instance()->ToLowercase(gameObject->GetName()) }) })
			);

			MessageManager::Instance()->QueueMessage(msgRemove);

			return new Message(
				gameObject->GetID(), "flammable",
				gameObject->GetParentID(), gameObject->GetParentType(),
				message->GetSenderID(), message->GetSenderType(),
				message->GetSenderParentID(), message->GetSenderParentType(),
				(void*) new std::string(gameObject->GetName() + " bursts into flames and is destroyed.")
			);
		}
	}

	return nullptr;
}
