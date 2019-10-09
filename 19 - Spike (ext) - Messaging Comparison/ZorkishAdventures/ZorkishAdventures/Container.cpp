#include "pch.h"

#include "Container.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

bool Container::GetAlwaysOpen()
{
	return alwaysOpen;
}

bool Container::GetIsOpen()
{
	if (alwaysOpen)
	{
		return true;
	}

	if (gameObject->HasComponent("lock") && ((Lock*)gameObject->GetComponent("lock"))->GetIsLocked())
	{
		return false;
	}
	
	return isOpen;
}

void Container::SetIsOpen(bool value)
{
	if(!alwaysOpen)
	{
		if (value && gameObject->HasComponent("lock") && ((Lock*)gameObject->GetComponent("lock"))->GetIsLocked())
		{
			return;
		}

		isOpen = value;		
	}
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

Container::Container(GameObject* gameObject, bool alwaysOpen, bool isOpen) : Component("container", gameObject)
{
	items = std::vector<Item*>();
	this->alwaysOpen = alwaysOpen;
	this->isOpen = isOpen;
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

bool Container::HasItem(std::vector<std::string> input)
{
	if (!items.empty())
	{
		std::string string = StringManager::Instance()->VectorToString(input, ' ');

		for (int i = 0; i < (int)items.size(); i++)
		{
			if (StringManager::Instance()->ToLowercase(items[i]->GetName()) == string)
			{
				return true;
			}
		}
	}

	return false;
}

void Container::AddItem(Item* item)
{
	items.push_back(item);
	MessageManager::Instance()->Subscribe(gameObject->GetID(), item);
	item->SetContainerID(gameObject->GetID());
}

void Container::RemoveItem(std::vector<std::string> input)
{
	if (!items.empty())
	{
		std::string string = StringManager::Instance()->VectorToString(input, ' ');

		for (int i = 0; i < (int)items.size(); i++)
		{
			if (StringManager::Instance()->ToLowercase(items[i]->GetName()) == string)
			{
				MessageManager::Instance()->Unsubscribe("item", items[i]->GetID(), gameObject->GetID());
				items[i]->SetContainerID("null");
				items.erase(items.begin() + i);
				break;
			}
		}
	}
}

Message* Container::Notify(Message* message)
{
	if (message->GetSenderID() == "OPEN")
	{
		std::vector<std::string> messageContent = *(std::vector<std::string>*)message->GetContent();

		if (messageContent[0] == "open")
		{
			if (gameObject->HasComponent("lock"))
			{
				if (!((Lock*)gameObject->GetComponent("lock"))->GetIsLocked())
				{
					isOpen = true;
					return new Message(
						gameObject->GetID(), "container", 
						gameObject->GetParentID(), gameObject->GetParentType(),
						message->GetSenderID(), message->GetSenderType(), 
						message->GetSenderParentID(), message->GetSenderParentType(),
						(void*) new std::string("already unlocked")
					);
				}
				else if (messageContent.size() == 1)
				{
					return new Message(
						gameObject->GetID(), "container",
						gameObject->GetParentID(), gameObject->GetParentType(),
						message->GetSenderID(), message->GetSenderType(),
						message->GetSenderParentID(), message->GetSenderParentType(),
						(void*) new std::string("locked")
					);
				}
				else
				{
					Message* msg = new Message(
						gameObject->GetID(), "container",
						gameObject->GetParentID(), gameObject->GetParentType(),
						gameObject->GetID(), "lock",
						gameObject->GetParentID(), gameObject->GetParentType(),
						(void*) new std::vector<std::string>({ "unlock", messageContent[1] })
					);
					Message* result = MessageManager::Instance()->SendMessage(msg);
					std::string messageContent = *(std::string*)result->GetContent();

					if (messageContent == "unlocked")
					{
						isOpen = true;
					}

					return new Message(
						gameObject->GetID(), "container", 
						gameObject->GetParentID(), gameObject->GetParentType(),
						message->GetSenderID(), message->GetSenderType(), 
						message->GetSenderParentID(), message->GetSenderParentType(),
						result->GetContent()
					);
				}				
			}
			else
			{
				if (messageContent.size() > 1)
				{
					return new Message(
						gameObject->GetID(), "container",
						gameObject->GetParentID(), gameObject->GetParentType(),
						message->GetSenderID(), message->GetSenderType(),
						message->GetSenderParentID(), message->GetSenderParentType(),
						(void*) new std::string("no lock")
					);
				}
				else if (isOpen)
				{
					return new Message(
						gameObject->GetID(), "container",
						gameObject->GetParentID(), gameObject->GetParentType(),
						message->GetSenderID(), message->GetSenderType(),
						message->GetSenderParentID(), message->GetSenderParentType(), 
						(void*) new std::string("already open")
					);
				}
				else
				{
					isOpen = true;
					return new Message(
						gameObject->GetID(), "container",
						gameObject->GetParentID(), gameObject->GetParentType(),
						message->GetSenderID(), message->GetSenderType(),
						message->GetSenderParentID(), message->GetSenderParentType(),
						(void*) new std::string("opened")
					);
				}
			}			
		}
	}

	return nullptr;
}
