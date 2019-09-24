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

CommandOpen::CommandOpen()
{
	name = "open";
	AddKeyword("open");
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

std::string CommandOpen::Process(std::vector<std::string> input, World* world, Player* player)
{
	input.erase(input.begin());

	Item* containerItem = nullptr;		
	std::vector<std::string> containerName = std::vector<std::string>();
	std::vector<std::string> keyName = std::vector<std::string>();

	if (!StringManager::Instance()->VectorContainsString(input, "with"))
	{
		containerName = input;
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
						containerName.push_back(input[j]);
					}
					else if (j > i)
					{
						keyName.push_back(input[j]);
					}
				}

				break;
			}
		}
	}

	if (((Container*)world->GetCurrentLocation()->GetComponent("container"))->HasItem(containerName))
	{
		containerItem = ((Container*)world->GetCurrentLocation()->GetComponent("container"))->GetItem(containerName);
	}
	else if (((Container*)player->GetComponent("container"))->HasItem(containerName))
	{
		containerItem = ((Container*)player->GetComponent("container"))->GetItem(containerName);
	}

	if (containerItem == nullptr)
	{
		return "You cannot find \"" + StringManager::Instance()->VectorToString(containerName, ' ') + "\" at your current location or in your inventory.";
	}
	else if (!containerItem->HasComponent("container"))
	{
		return containerItem->GetName() + " is not a container; you cannot open it.";
	}

	Container* container = (Container*)containerItem->GetComponent("container");

	if (container->GetIsOpen())
	{
		return containerItem->GetName() + " is already open.";
	}
	else if (!StringManager::Instance()->VectorContainsString(input, "with"))	//Player's input was "open containerName"
	{
		container->SetIsOpen(true);

		if (container->GetIsOpen())
		{
			return "You opened " + containerItem->GetName() + ". " + CommandManager::Instance()->Process(StringManager::Instance()->StringToVector("look in " + StringManager::Instance()->ToLowercase(containerItem->GetName()), ' '), world, player);
		}
		else
		{
			return "You cannot open " + containerItem->GetName() + "; it's locked.";
		}
	}
	else	//Player's input was "open containerName with keyName"
	{
		Item* keyItem = nullptr;

		if (((Container*)world->GetCurrentLocation()->GetComponent("container"))->HasItem(keyName))
		{
			keyItem = ((Container*)world->GetCurrentLocation()->GetComponent("container"))->GetItem(keyName);
		}
		else if (((Container*)player->GetComponent("container"))->HasItem(keyName))
		{
			keyItem = ((Container*)player->GetComponent("container"))->GetItem(keyName);
		}

		if (keyItem == nullptr)
		{
			return "You cannot find \"" + StringManager::Instance()->VectorToString(keyName, ' ') + "\" at your current location or in your inventory.";
		}
		else if (!containerItem->HasComponent("lock"))
		{
			return "You don't need " + keyItem->GetName() + " to open " + containerItem->GetName() + "; it doesn't have a lock. Just open it normally.";
		}
		
		Lock* lock = (Lock*)containerItem->GetComponent("lock");
		
		if (!lock->GetIsLocked())
		{
			return containerItem->GetName() + " is already unlocked. Just open it normally.";
		}
		else if (!lock->UnlockableWith(keyItem->GetID()))
		{
			return "You try to unlock " + containerItem->GetName() + " with " + keyItem->GetName() + ", but it doesn't fit the lock.";
		}
		
		lock->Unlock(keyItem->GetID());

		if (lock->GetIsLocked())
		{
			return "You try to unlock " + containerItem->GetName() + " with " + keyItem->GetName() + ", but the lock stays locked.";
		}

		container->SetIsOpen(true);

		if (container->GetIsOpen())
		{
			return "You unlocked and opened " + containerItem->GetName() + ". " + CommandManager::Instance()->Process(StringManager::Instance()->StringToVector("look in " + StringManager::Instance()->ToLowercase(containerItem->GetName()), ' '), world, player);
		}
		else
		{
			return "You unlock " + containerItem->GetName() + " with " + keyItem->GetName() + ", but " + containerItem->GetName() + " doesn't open. It seems stuck. It shouldn't be. This is not right at all.";
		}
	}
	
}