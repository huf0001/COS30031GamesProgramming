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
	std::vector<std::string> containerNameVector = std::vector<std::string>();
	std::string containerID;
	std::string containerName;
	std::string containerParentID;
	std::string containerParentType;

	Item* keyItem = nullptr;
	std::vector<std::string> keyNameVector = std::vector<std::string>();
	std::string keyID;
	std::string keyName;
	std::string keyParentID;
	std::string keyParentType;

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

		//Validate Key exists via messages
		Message* msgAccessKeyItemFromLocation = new Message(
			"OPEN", "command",
			"null", "null",
			"messageManager", "messageManager",
			"null", "null",
			(void*) new std::vector<std::string>({ "access item from location", StringManager::Instance()->VectorToString(keyNameVector, ' '), world->GetCurrentLocation()->GetID()})
		);
		Message* resultAccessKeyItemFromLocation = MessageManager::Instance()->SendMessage(msgAccessKeyItemFromLocation);
		std::vector<std::string> outcome = *(std::vector<std::string>*)resultAccessKeyItemFromLocation->GetContent();

		if (outcome[0] == "null")
		{
			return "You cannot find \"" + StringManager::Instance()->VectorToString(keyNameVector, ' ') + "\" at your current location or in your inventory.";
		}
		else
		{
			keyID = outcome[0];
			keyName = outcome[1];
			keyParentID = outcome[2];
			keyParentType = outcome[3];
			messageContent.push_back(keyID);
		}
	}

	//Validate container exists via messages
	Message* msgAccessContainerItemFromLocation = new Message(
		"OPEN", "command",
		"null", "null",
		"messageManager", "messageManager",
		"null", "null",
		(void*) new std::vector<std::string>({ "access item from location", StringManager::Instance()->VectorToString(containerNameVector, ' '), world->GetCurrentLocation()->GetID() })
	);
	Message* resultAccessContainerItemFromLocation = MessageManager::Instance()->SendMessage(msgAccessContainerItemFromLocation);
	std::vector<std::string> outputVector = *(std::vector<std::string>*)resultAccessContainerItemFromLocation->GetContent();

	if (outputVector[0] == "null")
	{
		return "You cannot find \"" + StringManager::Instance()->VectorToString(containerNameVector, ' ') + "\" at your current location or in your inventory.";
	}
	
	containerID = outputVector[0];
	containerName = outputVector[1];
	containerParentID = outputVector[2];
	containerParentType = outputVector[3];

	//Validate container is actually a container via messages
	Message* msgHasContainerComponent = new Message(
		"OPEN", "command",
		"null", "null",
		containerID, "gameObject",
		containerParentID, containerParentType,
		(void*) new std::vector<std::string>({ "has component", "container" })
	);
	Message* resultHasContainerComponent = MessageManager::Instance()->SendMessage(msgHasContainerComponent);

	if (*(std::string*) resultHasContainerComponent->GetContent() == "No")
	{
		return containerName + " is not a container; you cannot open it.";
	}

	//Open / unlock container via messages
	Message* msgOpenContainerItem = new Message(
		"OPEN", "command", 
		"null", "null", 
		containerID, "container", 
		containerParentID, containerParentType, 
		(void*)& messageContent);
	Message* resultOpenContainerItem = MessageManager::Instance()->SendMessage(msgOpenContainerItem);
	std::string output = *(std::string*)resultOpenContainerItem->GetContent();

	//Handle results
	if (output == "already unlocked")
	{
		return containerName + " is already unlocked. Try looking inside it normally.";
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
		//Verify via messages that the container was opened / unlocked
		Message* msgContainerOpen = new Message(
			"OPEN", "command",
			"null", "null",
			containerID, "container",
			containerParentID, containerParentType,
			(void*) new std::vector<std::string>({ "is open" }));
		Message* resultContainerOpen = MessageManager::Instance()->SendMessage(msgContainerOpen);
		std::string outputContainerOpen = *(std::string*)resultContainerOpen->GetContent();

		if (outputContainerOpen == "open")
		{
			return "You unlocked and opened " + containerName + ". " + CommandManager::Instance()->Process(StringManager::Instance()->StringToVector("look in " + StringManager::Instance()->ToLowercase(containerName), ' '), world, player);
		}
		else if (outputContainerOpen == "locked")
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
		return "Error: invalid message \"" + output + "\" sent to / received from " + containerName + "'s container component.";
	}
}