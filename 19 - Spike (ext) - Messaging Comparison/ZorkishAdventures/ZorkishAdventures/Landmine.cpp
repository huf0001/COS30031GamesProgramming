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
		return MessageManager::Instance()->SendMessage(new Message(
			gameObject->GetID(), gameObject->GetType(),
			gameObject->GetParentID(), gameObject->GetParentType(),
			"all", "flammable",
			gameObject->GetParentID(), gameObject->GetParentType(),
			(void*) new std::string("ignite")
		));
	}
}
