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
			if (world->GetCurrentLocation()->HasItem(itemName))
			{
				Item* item = world->GetCurrentLocation()->GetItem(itemName);
				world->GetCurrentLocation()->RemoveItem(itemName);
				player->AddItem(item);
				return "You put " + item->GetName() + " in your inventory.";
			}
			else
			{
				return "You cannot find '" + StringManager::Instance()->VectorToString(itemName, ' ') + "' at your current location.";
			}
		}
		else if (StringManager::Instance()->VectorToString(containerName, ' ') == "location")
		{
			if (player->HasItem(itemName))
			{
				Item* item = player->GetItem(itemName);
				player->RemoveItem(itemName);
				world->GetCurrentLocation()->AddItem(item);
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

			if (player->HasItem(itemName))
			{
				item = player->GetItem(itemName);
				itemLocation = "inventory";
			}
			else if (world->GetCurrentLocation()->HasItem(itemName))
			{
				item = world->GetCurrentLocation()->GetItem(itemName);
				itemLocation = "current location";
			}

			if (item == nullptr)
			{
				return "You can't find '" + StringManager::Instance()->VectorToString(itemName, ' ') + "' at your current location or in your inventory.";
			}

			//Find container in inventory or location
			Item* containerItemAsItem = nullptr;

			if (world->GetCurrentLocation()->HasItem(containerName))
			{
				containerItemAsItem = world->GetCurrentLocation()->GetItem(containerName);
			}
			else if (player->HasItem(containerName))
			{
				containerItemAsItem = player->GetItem(containerName);
			}

			if (containerItemAsItem == nullptr)
			{
				return "You can't find '" + StringManager::Instance()->VectorToString(containerName, ' ') + "' at your current location or in your inventory.";
			}
			else if (!containerItemAsItem->GetIsContainer())
			{
				return "You cannot put " + item->GetName() + " in " + containerItemAsItem->GetName() + ". '" +
					containerItemAsItem->GetName() + "' is not a container.";
			}
			else if (containerItemAsItem == item)
			{
				return "You cannot put " + item->GetName() + " inside itself.";
			}

			//Put item in container
			ContainerItem* containerItem = (ContainerItem*)containerItemAsItem;

			if (itemLocation == "inventory")
			{
				player->RemoveItem(itemName);
				containerItem->AddItem(item);
				return "You took " + item->GetName() + " from your inventory and put it in " + containerItem->GetName() + ".";
			}
			else if (itemLocation == "current location")
			{
				world->GetCurrentLocation()->RemoveItem(itemName);
				containerItem->AddItem(item);
				return "You took " + item->GetName() + " from your current location and put it in " + containerItem->GetName() + ".";
			}
		}
	}

	return "You can't put an item in something else like that.";
}

