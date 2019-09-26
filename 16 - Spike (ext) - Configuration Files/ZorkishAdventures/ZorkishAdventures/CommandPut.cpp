#include "CommandPut.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

std::string CommandPut::GetSyntax()
{
	std::string result;

	result += "PUT\n";
	result += "----------------------------\n";
	result += "Function:\n";
	result += "\t- Take an item from your inventory and put it in a container or your current location.\n";
	result += "Syntax:\n";
	result += "\t- \"put [item] in [container]\"\n";
	//result += "\t- \"put [item] into [container]\"\n";

	if (aliases.size() > 0)
	{
		result += "Aliases for \"put\":\n";

		for (std::string alias : aliases)
		{
			result += "\t- \"" + alias + "\"\n";
		}
	}

	return result;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

CommandPut::CommandPut()
{
	AddKeyword("put");
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

std::string CommandPut::PutInContainer(std::vector<std::string> itemName, GameObject* containerFrom, GameObject* containerTo, std::vector<std::string> successMessage)
{
	Item* item = ((Container*)containerFrom->GetComponent("container"))->GetItem(itemName);
	std::string result = "";

	if (!item->HasComponent("movable"))
	{
		result += "You cannot move " + item->GetName() + ".";
	}
	else
	{
		((Container*)containerFrom->GetComponent("container"))->RemoveItem(itemName);
		((Container*)containerTo->GetComponent("container"))->AddItem(item);
		
		for (int i = 0; i < (int)successMessage.size(); i++)
		{
			if (successMessage[i] == "[ITEM NAME]")
			{
				successMessage[i] = item->GetName();
			}
			else if (successMessage[i] == "[CONTAINER FROM NAME]")
			{
				successMessage[i] = containerFrom->GetName();
			}
			else if (successMessage[i] == "[CONTAINER TO NAME]")
			{
				successMessage[i] = containerTo->GetName();
			}
		}

		result += StringManager::Instance()->VectorToString(successMessage, ' ');

		if (containerTo->GetType() == "player" && item->HasComponent("unlock_commands"))
		{
			result += CommandManager::Instance()->UnlockCommands(((UnlockCommands*)item->GetComponent("unlock_commands"))->GetCommands());
			item->RemoveComponent("unlock_commands");
		}
	}

	return result;
}

std::string CommandPut::Process(std::vector<std::string> input, World* world, Player* player)
{
	input.erase(input.begin());

	if (!StringManager::Instance()->VectorContainsString(input, "in"))
	{
		return "Where do you want to put '" + StringManager::Instance()->VectorToString(input, ' ') + "'?";
	}

	if (input.size() >= 3)
	{
		std::vector<std::string> itemName = std::vector<std::string>();
		std::vector<std::string> containerName = std::vector<std::string>();

		//Taking item from container in inventory or location
		//Find cut-off of item and container names
		for (int i = (int)input.size() - 1; i >= 0; i--)
		{
			if (input[i] == "in")
			{
				//Get item and container names
				for (int j = 0; j < (int)input.size(); j++)
				{
					if (j < i)
					{
						itemName.push_back(input[j]);
					}
					else if (j > i)
					{
						containerName.push_back(input[j]);
					}
				}

				break;
			}
		}

		if (containerName.size() == 0)
		{
			return "What do you want to put '" + StringManager::Instance()->VectorToString(itemName, ' ') + "' in?";
		}
		else if (StringManager::Instance()->VectorToString(containerName, ' ') == "inventory")
		{
			if (((Container*)world->GetCurrentLocation()->GetComponent("container"))->HasItem(itemName))
			{
				std::vector<std::string> successMessage = { "You put", "[ITEM NAME]", "in your inventory." };
				return PutInContainer(itemName, (GameObject*)world->GetCurrentLocation(), (GameObject*)player, successMessage);
			}
			else
			{
				return "You cannot find '" + StringManager::Instance()->VectorToString(itemName, ' ') + "' at your current location.";
			}
		}
		else if (StringManager::Instance()->VectorToString(containerName, ' ') == "location")
		{
			if (((Container*)player->GetComponent("container"))->HasItem(itemName))
			{
				std::vector<std::string> successMessage = { "You put down", "[ITEM NAME]", "at your current location." };
				return PutInContainer(itemName, (GameObject*)player, (GameObject*)world->GetCurrentLocation(), successMessage);
			}
			else
			{
				return "You cannot find '" + StringManager::Instance()->VectorToString(itemName, ' ') + "' in your inventory.";
			}
		}
		else
		{
			//Find item in inventory or location
			Item* item = nullptr;
			std::string itemLocation;

			if (((Container*)player->GetComponent("container"))->HasItem(itemName))
			{
				item = ((Container*)player->GetComponent("container"))->GetItem(itemName);
				itemLocation = "inventory";
			}
			else if (((Container*)world->GetCurrentLocation()->GetComponent("container"))->HasItem(itemName))
			{
				item = ((Container*)world->GetCurrentLocation()->GetComponent("container"))->GetItem(itemName);
				itemLocation = "current location";
			}

			if (item == nullptr)
			{
				return "You can't find '" + StringManager::Instance()->VectorToString(itemName, ' ') + "' at your current location or in your inventory.";
			}

			//Find container in inventory or location
			Item* containerItem = nullptr;

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
				return "You can't find '" + StringManager::Instance()->VectorToString(containerName, ' ') + "' at your current location or in your inventory.";
			}
			else if (!containerItem->HasComponent("container"))
			{
				return "You cannot put " + item->GetName() + " in " + containerItem->GetName() + ". '" +
					containerItem->GetName() + "' is not a container.";
			}
			else if (containerItem == item)
			{
				return "You cannot put " + item->GetName() + " inside itself.";
			}
			else if (!((Container*)containerItem->GetComponent("container"))->GetIsOpen())
			{
				return "You cannot put " + item->GetName() + " inside " + containerItem->GetName() + "; " + containerItem->GetName() + " is closed.";
			}

			if (itemLocation == "inventory")
			{
				std::vector<std::string> successMessage = { "You took", "[ITEM NAME]", "from your inventory and put it in " + containerItem->GetName() + "." };
				return PutInContainer(itemName, (GameObject*)player, (GameObject*)containerItem, successMessage);
			}
			else if (itemLocation == "current location")
			{
				std::vector<std::string> successMessage = { "You took", "[ITEM NAME]", "from your current location and put it in " + containerItem->GetName() + "." };
				return PutInContainer(itemName, (GameObject*)world->GetCurrentLocation(), (GameObject*)containerItem, successMessage);
			}
		}
	}

	return "You can't put an item in something else like that.";
}

