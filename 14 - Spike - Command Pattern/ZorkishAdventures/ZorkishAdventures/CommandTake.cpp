#include "CommandTake.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

std::string CommandTake::GetSyntax()
{
	std::string result;

	result += "TAKE\n";
	result += "----------------------------\n";
	result += "Function:\n";
	result += "\t- Take an item from your location or a container and put it in your inventory.\n";
	result += "Syntax:\n";
	result += "\t- \"take [item]\"\n"; 
	result += "\t- \"take [item] from [container]\"\n"; 
	result += "\t- \"pick up [item]\"\n"; 
	result += "\t- \"pick up [item] from [container]\"\n"; 

	if (aliases.size() > 0)
	{
		result += "Aliases for \"take\":\n";

		for (std::string alias : aliases)
		{
			result += "\t- \"" + alias + "\"\n";
		}
	}

	return result;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

CommandTake::CommandTake()
{
	AddKeyword("take");
	AddKeyword("pick");
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

std::vector<std::string> CommandTake::StandardiseInput(std::vector<std::string> input)
{
	if (input[0] == "pick" && input.size() >= 3 && input[1] == "up")
	{
		input.erase(input.begin());
		input[0] = "take";
	}

	return input;
}

std::string CommandTake::Process(std::vector<std::string> input, World* world, Player* player)
{
	input = StandardiseInput(input);

	if (input.size() >= 2)
	{
		input.erase(input.begin());

		if (!StringManager::Instance()->VectorContainsString(input, "from"))
		{
			//Find item in location
			if (!world->GetCurrentLocation()->HasItem(input))
			{
				return "You cannot find item '" + StringManager::Instance()->VectorToString(input, ' ') + "' at your current location";
			}
			else
			{
				//Add item to inventory
				Item* item = world->GetCurrentLocation()->GetItem(input);
				world->GetCurrentLocation()->RemoveItem(input);
				player->AddItem(item);
				return "You added " + item->GetName() + " to your inventory.";
			}
		}
		else
		{
			std::vector<std::string> itemName = std::vector<std::string>();
			std::vector<std::string> containerName = std::vector<std::string>();

			//Taking item from container in inventory or location
			//Find cut-off of item and container names
			for (int i = (int)input.size() - 1; i >= 0; i--)
			{
				if (input[i] == "from")
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
				return "What do you want to take '" + StringManager::Instance()->VectorToString(itemName, ' ') + "' from?";
			}
			else if (StringManager::Instance()->VectorToString(containerName, ' ') == "inventory")
			{
				if (player->HasItem(itemName))
				{
					return "You remove " + StringManager::Instance()->VectorToString(itemName, ' ') + " from your inventory, and add it back to your inventory";
				}
				else
				{
					return "'" + StringManager::Instance()->VectorToString(itemName, ' ') + "' is not in your inventory. Even if it was, you would merely be putting it right back.";
				}
			}
			else if (StringManager::Instance()->VectorToString(containerName, ' ') == "location")
			{
				if (world->GetCurrentLocation()->HasItem(itemName))
				{
					//Add item to inventory
					Item* item = world->GetCurrentLocation()->GetItem(itemName);
					world->GetCurrentLocation()->RemoveItem(itemName);
					player->AddItem(item);
					return "You added " + item->GetName() + " to your inventory.";
				}
				else
				{
					return "'" + StringManager::Instance()->VectorToString(itemName, ' ') + "' is not at your current location.";
				}
			}
			else
			{
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
					return "You cannot take '" + StringManager::Instance()->VectorToString(itemName, ' ') + "' from '" + StringManager::Instance()->VectorToString(containerName, ' ') + "'. '" +
						StringManager::Instance()->VectorToString(containerName, ' ') + "' is not a container.";
				}
				else
				{
					//Find item in container
					ContainerItem* containerItem = (ContainerItem*)containerItemAsItem;

					if (!containerItem->HasItem(itemName))
					{
						return "You cannot find '" + StringManager::Instance()->VectorToString(itemName, ' ') + "' inside '" + StringManager::Instance()->VectorToString(containerName, ' ') + "'.";
					}
					else
					{
						//Take item from container
						Item* item = containerItem->GetItem(itemName);
						containerItem->RemoveItem(itemName);
						player->AddItem(item);
						return "You added " + item->GetName() + " to your inventory";
					}
				}
			}
		}
	}

	return "You can't take stuff like that.";
}

