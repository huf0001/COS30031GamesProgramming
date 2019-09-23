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
				Item* item = ((Container*)world->GetCurrentLocation()->GetComponent("container"))->GetItem(itemName);
				((Container*)world->GetCurrentLocation()->GetComponent("container"))->RemoveItem(itemName);
				((Container*)player->GetComponent("container"))->AddItem(item);
				return "You put " + item->GetName() + " in your inventory.";
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
				Item* item = ((Container*)player->GetComponent("container"))->GetItem(itemName);
				((Container*)player->GetComponent("container"))->RemoveItem(itemName);
				((Container*)world->GetCurrentLocation()->GetComponent("container"))->AddItem(item);
				return "You put down " + item->GetName() + " at your current location.";
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

			if (itemLocation == "inventory")
			{
				((Container*)player->GetComponent("container"))->RemoveItem(itemName);
				((Container*)item->GetComponent("container"))->AddItem(item);
				return "You took " + item->GetName() + " from your inventory and put it in " + containerItem->GetName() + ".";
			}
			else if (itemLocation == "current location")
			{
				((Container*)world->GetCurrentLocation()->GetComponent("container"))->RemoveItem(itemName);
				((Container*)item->GetComponent("container"))->AddItem(item);
				return "You took " + item->GetName() + " from your current location and put it in " + containerItem->GetName() + ".";
			}
		}
	}

	return "You can't put an item in something else like that.";
}
