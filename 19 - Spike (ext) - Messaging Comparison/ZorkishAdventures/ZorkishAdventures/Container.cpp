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
	item->SetParentID(gameObject->GetID());
	item->SetParentType(gameObject->GetType());
}

Item* Container::GetItem(std::vector<std::string> input)
{
	if (!items.empty())
	{
		std::string string = StringManager::Instance()->VectorToString(input, ' ');

		for (int i = 0; i < (int)items.size(); i++)
		{
			if (StringManager::Instance()->ToLowercase(items[i]->GetName()) == string)
			{
				return items[i];
			}
		}
	}

	return nullptr;
}

//For testing only
std::vector<Item*> Container::GetItems()
{
	return items;
}

std::string Container::ViewItem(std::vector<std::string> input)
{
	/*std::vector<std::string> inputCopy = std::vector<std::string>(input);
	std::vector<std::string> name;

	for(int i = input.size() - 1; i >= 0; i--)
	{
		inputCopy.pop_back();

		if (input[i] != "in")
		{
			name.insert(name.begin(), input[i]);
		}
		else
		{
			Container* container = (Container*)GetItem(name);

			if (container != nullptr)
			{
				return container->ViewItem(inputCopy);
			}

			return "You can't look in " + StringManager::Instance()->VectorToString(name, ' ') + "; it isn't there.";
		}
	}*/

	Item* item = GetItem(input);

	if (item != nullptr)
	{
		return ((Description*)item->GetComponent("description"))->GetDescription();
	}

	return "You cannot find '" + StringManager::Instance()->VectorToString(input, ' ') + "'; it isn't where you were looking.";
}

std::string Container::ViewItems()
{
	if (items.empty())
	{
		return "";
	}

	std::string result = "";

	for (int i = 0; i < (int)items.size(); i++)
	{
		result += "\n\t- " + items[i]->GetName();
	}

	return result;
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
				items[i]->SetParentID("null");
				items[i]->SetParentType("null");
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
		else if (messageContent[0] == "is open")
		{
			std::string result;

			if (gameObject->HasComponent("lock"))
			{
				Message* msgIsLocked = new Message(
					gameObject->GetID(), "container",
					gameObject->GetParentID(), gameObject->GetParentType(),
					gameObject->GetID(), "lock",
					gameObject->GetParentID(), gameObject->GetParentType(),
					(void*) new std::vector<std::string>({ "is locked" })
				);
				Message* resultIsLocked = MessageManager::Instance()->SendMessage(msgIsLocked);
				std::string messageContent = *(std::string*)resultIsLocked->GetContent();

				result = 
					(messageContent == "locked") ? "locked" 
					: isOpen ? "open" 
					: "closed";
			}
			else
			{
				result = isOpen ? "open" : "closed";
			}

			return new Message(
				gameObject->GetID(), gameObject->GetType(),
				gameObject->GetParentID(), gameObject->GetParentType(),
				message->GetSenderID(), message->GetSenderType(),
				message->GetSenderParentID(), message->GetSenderParentType(),
				(void*) new std::string(result)
			);
		}
	}

	return nullptr;
}
