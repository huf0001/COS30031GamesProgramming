#include "CommandOpen.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

std::string CommandOpen::GetSyntax()
{
	std::string result;

	result += "OPEN\n";
	result += "----------------------------\n";
	result += "Function:\n";
	result += "\t- Opens a container.\n";
	result += "Syntax:\n";
	result += "\t- \"open [container]\"\n";
	//result += "\t- \"open [container] with [key]\"\n";

	if (aliases.size() > 0)
	{
		result += "Aliases for \"open\":\n";

		for (std::string alias : aliases)
		{
			result += "\t- \"" + alias + "\"\n";
		}
	}

	return result;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

CommandOpen::CommandOpen() : Command("OPEN")
{
	AddKeyword("open");
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

std::string CommandOpen::Process(std::vector<std::string> input, World* world, Player* player)
{
	input.erase(input.begin());

	std::vector<std::string> messageContent = std::vector<std::string>({ "open" });

	Item* containerItem = nullptr;
	Item* keyItem = nullptr;

	std::vector<std::string> containerNameVector = std::vector<std::string>();
	std::vector<std::string> keyNameVector = std::vector<std::string>();

	std::string containerName;
	std::string keyName;
	std::string holdsContainer;

	if (!StringManager::Instance()->VectorContainsString(input, "with"))
	{
		//Don't need to worry about a key, just skip to the container stuff
		containerNameVector = input;
	}
	else
	{
		//Split input into containerName and keyName
		for (int i = (int)input.size() - 1; i >= 0; i--)
		{
			if (input[i] == "with")
			{
				for (int j = 0; j < (int)input.size(); j++)
				{
					if (j < i)
					{
						containerNameVector.push_back(input[j]);
					}
					else if (j > i)
					{
						keyNameVector.push_back(input[j]);
					}
				}

				break;
			}
		}

		//Validate key exists
		if (((Container*)world->GetCurrentLocation()->GetComponent("container"))->HasItem(keyNameVector))
		{
			keyItem = ((Container*)world->GetCurrentLocation()->GetComponent("container"))->GetItem(keyNameVector);
			holdsContainer = world->GetCurrentLocation()->GetID();
		}
		else if (((Container*)player->GetComponent("container"))->HasItem(keyNameVector))
		{
			keyItem = ((Container*)player->GetComponent("container"))->GetItem(keyNameVector);
			holdsContainer = player->GetID();
		}

		if (keyItem == nullptr)
		{
			return "You cannot find \"" + StringManager::Instance()->VectorToString(keyNameVector, ' ') + "\" at your current location or in your inventory.";
		}
		else
		{
			keyName = keyItem->GetName();
			messageContent.push_back(keyItem->GetID());
		}
	}

	//Validate container exists and is a container
	if (((Container*)world->GetCurrentLocation()->GetComponent("container"))->HasItem(containerNameVector))
	{
		containerItem = ((Container*)world->GetCurrentLocation()->GetComponent("container"))->GetItem(containerNameVector);
		holdsContainer = world->GetCurrentLocation()->GetID();
	}
	else if (((Container*)player->GetComponent("container"))->HasItem(containerNameVector))
	{
		containerItem = ((Container*)player->GetComponent("container"))->GetItem(containerNameVector);
		holdsContainer = player->GetID();
	}

	if (containerItem == nullptr)
	{
		return "You cannot find \"" + StringManager::Instance()->VectorToString(containerNameVector, ' ') + "\" at your current location or in your inventory.";
	}
	else
	{
		containerName = containerItem->GetName();
		
		if (!containerItem->HasComponent("container"))
		{
			return containerName + " is not a container; you cannot open it.";
		}
	}	

	//Send Message
	Message* msg = new Message("OPEN", "command", containerItem->GetID(), "container", (void*)& messageContent);
	Message* result = MessageManager::Instance()->SendMessage(msg, holdsContainer);
	std::string output = *(std::string*)result->GetContent();

	//Handle results
	if (output == "already unlocked")
	{
		return containerName + " is already unlocked. Just open it normally.";
	}
	else if (output == "locked")	//Tried to open with "open [container]"
	{
		return "You cannot open " + containerName + "; it's locked.";
	}
	else if (output == "can't unlock")	//Key doesn't unlock container	
	{
		return "You try to unlock " + containerName + " with " + keyName + ", but it doesn't fit the lock.";
	}
	else if (output == "unlocked")
	{
		if (((Container*)containerItem->GetComponent("container"))->GetIsOpen())
		{
			return "You unlocked and opened " + containerName + ". " + CommandManager::Instance()->Process(StringManager::Instance()->StringToVector("look in " + StringManager::Instance()->ToLowercase(containerName), ' '), world, player);
		}
		else if (((Lock*)containerItem->GetComponent("lock"))->GetIsLocked())
		{
			return "You try to unlock " + containerName + " with " + keyName + ", but the lock stays locked. It seems stuck. It shouldn't be. This is not right at all.";
		}
		else
		{
			return "You unlock " + containerName + " with " + keyName + ", but " + containerName + " doesn't open. It seems stuck. It shouldn't be. This is not right at all.";
		}
	}
	else if (output == "no lock")
	{
		return "You don't need " + keyName + " to open " + containerName + "; it doesn't have a lock. Just open it normally.";
	}
	else if (output == "already open")
	{
		return containerName + " is already open.";
	}
	else if (output == "opened")
	{
		return "You opened " + containerName + ". " + CommandManager::Instance()->Process(StringManager::Instance()->StringToVector("look in " + StringManager::Instance()->ToLowercase(containerName), ' '), world, player);
	}
	else
	{
		return "Error: invalid message \"" + output + "\" sent to / received from " + containerItem->GetID() + "'s component container.";
	}
}