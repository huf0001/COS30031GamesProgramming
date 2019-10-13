#include "Flammable.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

Flammable::Flammable(GameObject* gameObject) : Component("flammable", gameObject)
{

}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

Message* Flammable::Notify(Message* message)
{
	std::string messageContent = *(std::string*)message->GetContent();
	
	if (messageContent == "ignite")
	{
		MessageManager::Instance()->QueueMessage(new Message(
			gameObject->GetID(), gameObject->GetType(),
			gameObject->GetParentID(), gameObject->GetParentType(),
			gameObject->GetParentID(), gameObject->GetParentType(),
			"override", "any",
			(void*) new std::vector<void*>({ (void*)new std::string("remove"), (void*)new int(0) })
		));

		return new Message(
			gameObject->GetID(), gameObject->GetType(),
			gameObject->GetParentID(), gameObject->GetParentType(),
			message->GetSenderID(), message->GetSenderType(),
			message->GetSenderParentID(), message->GetSenderParentType(),
			(void*) new std::string(gameObject->GetName() + " bursts into flames and is destroyed.")
		);
	}

	return nullptr;
}
