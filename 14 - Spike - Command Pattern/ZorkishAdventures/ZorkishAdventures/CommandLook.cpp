#include "CommandLook.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

CommandLook::CommandLook()
{
	AddKeyword("look");
	AddKeyword("inventory");
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------
std::string CommandLook::LookAtLocation(World* world)
{
	//Assume the description ends in a full stop.
	std::string visible = ":" + world->ViewItemsInCurrentLocation() + world->ViewPathsAtCurrentLocation();

	if (visible == ":")
	{
		visible = " nothing; it's empty.";
	}

	return "You are in " + world->DescribeCurrentLocation() + " There, you can see" + visible;
}

std::string CommandLook::LookAtInventory(Player* player)
{
	std::string visible = ":" + player->ViewItems();

	if (visible == ":")
	{
		visible = " nothing; it's empty.";
	}

	return "In your inventory, you have" + visible;
}

std::string CommandLook::Process(std::vector<std::string> input, World* world, Player* player)
{
	if (input.size() == 1)
	{
		if (input[0] == "inventory")
		{
			return LookAtInventory(player);
		}
		else
		{
			return LookAtLocation(world);
		}
	}
	else if (input.size() >= 3)
	{
		if (input[1] == "at")
		{
			if (input[2] == "inventory")
			{
				return LookAtInventory(player);
			}
			else if (input[2] == "location")
			{
				return LookAtLocation(world);
			}

			input.erase(input.begin());
			input.erase(input.begin());

			for (int i = input.size() - 1; i >= 0; i--)
			{
				if (input[i] == "in")
				{
					std::vector<std::string> itemName = std::vector<std::string>();
					std::vector<std::string> containerName = std::vector<std::string>();

					for (int j = 0; j < input.size(); j++)
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

					if (i == input.size() - 1)
					{
						return "What do you want to look inside to look for '" + StringManager::Instance()->VectorToString(itemName, ' ') + "'?";
					}
					else
					{
						Item* item = nullptr;

						if (StringManager::Instance()->VectorToString(containerName, ' ') == "inventory")
						{
							if (player->HasItem(itemName))
							{
								return player->ViewItem(itemName);
							}
							else
							{
								return "You can't find '" + StringManager::Instance()->VectorToString(itemName, ' ') + "' in your inventory.";
							}
						}
						else if (StringManager::Instance()->VectorToString(containerName, ' ') == "location")
						{
							if (world->GetCurrentLocation()->HasItem(itemName))
							{
								return world->GetCurrentLocation()->ViewItem(itemName);
							}
							else
							{
								return "You can't find '" + StringManager::Instance()->VectorToString(itemName, ' ') + "' at your current location.";
							}
						}
						else
						{
							if (player->HasItem(containerName))
							{
								item = player->GetItem(containerName);
							}
							else if (world->GetCurrentLocation()->HasItem(containerName))
							{
								item = world->GetCurrentLocation()->GetItem(containerName);
							}

							if (item == nullptr)
							{
								return "You can't look in '" + StringManager::Instance()->VectorToString(containerName, ' ') + "'.";
							}
							else if (!item->GetIsContainer())
							{
								return "You can't look in '" + item->GetName() + "'; it's not a container.";
							}
							else
							{
								ContainerItem* containerItem = (ContainerItem*)item;
								return containerItem->ViewItem(itemName);
							}
						}
					}
				}
			}

			Item* item = nullptr;

			if (player->HasItem(input))
			{
				item = player->GetItem(input);
			}
			else if (world->GetCurrentLocation()->HasItem(input))
			{
				item = world->GetCurrentLocation()->GetItem(input);
			}

			if (item == nullptr)
			{
				return "You cannot find '" + StringManager::Instance()->VectorToString(input, ' ') + "'.";
			}
			else
			{
				return item->GetDescription();
			}
		}
		else if (input[1] == "in")
		{
			if (input[2] == "inventory")
			{
				return LookAtInventory(player);
			}
			else if (input[2] == "location")
			{
				return LookAtLocation(world);
			}

			input.erase(input.begin());
			input.erase(input.begin());
			Item* item = nullptr;

			if (player->HasItem(input))
			{
				item = player->GetItem(input);
			}
			else if (world->GetCurrentLocation()->HasItem(input))
			{
				item = world->GetCurrentLocation()->GetItem(input);
			}

			if (item == nullptr)
			{
				return "You cannot look in '" + StringManager::Instance()->VectorToString(input, ' ') + "'.";
			}
			else if (!item->GetIsContainer())
			{
				return "You can't look in '" + item->GetName() + "'; it's not a container.";
			}
			else
			{
				ContainerItem* containerItem = (ContainerItem*)item;
				return "In " + StringManager::Instance()->VectorToString(input, ' ') + ", you can see" + containerItem->ViewItems();
			}
		}
	}
	else if (input.size() == 2)
	{
		if (input[1] == "at")
		{
			return "What do you want to look at?";
		}
		else if (input[1] == "in")
		{
			return "What do you want to look in?";
		}
	}

	return "You can't look like that.";
}
