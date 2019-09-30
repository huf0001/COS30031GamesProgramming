#include "MessageManager.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

MessageManager* MessageManager::instance = 0;

MessageManager* MessageManager::Instance()
{
	if (!instance)
	{
		instance = new MessageManager();
	}

	return instance;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

MessageManager::MessageManager()
{
	subscribers = std::map<std::string, GameObject*>();
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

void MessageManager::Subscribe(GameObject* subscriber)
{
	if (subscribers.count(subscriber->GetID()))
	{
		std::cout << "Warning: GameObject \"" + subscriber->GetID() + "\" is already subscribed to MessageManager.\n";
	}
	else
	{
		subscribers[subscriber->GetID()] = subscriber;
	}
}

void MessageManager::Unsubscribe(std::string subscriberId)
{
	if (subscribers.count(subscriberId))
	{
		subscribers.erase(subscriberId);
	}
}

Message* MessageManager::SendMessage(Message* message)
{
	return !subscribers.count(message->GetReceiverID()) ? nullptr : subscribers[message->GetReceiverID()]->Notify(message);

	/*if (!subscribers.count(message->GetReceiverID()))
	{
		return nullptr;
	}
	else
	{
		return subscribers[message->GetReceiverID()]->Notify(message);
	}*/
}
