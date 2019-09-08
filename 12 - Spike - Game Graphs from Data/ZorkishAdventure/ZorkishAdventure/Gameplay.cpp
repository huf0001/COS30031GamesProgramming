#include "Gameplay.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

std::string Gameplay::GetCurrentWorldName()
{
	return world->GetName();
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

Gameplay::Gameplay()
{
	name = "Gameplay";
	worlds = std::map<std::string, World*>();
	worlds["Void World"] = new World("Void World");
	world = nullptr;
	player = new Player("Player 1");
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

std::string Gameplay::Setup()
{
	setup = true;
	std::string result;

	result += "Zorkish :: " + world->GetName();
	result += "\n--------------------------------------------------------";
	result += "\n";
	result += "\n" + world->DescribeCurrentLocation();
	result += "\n:> ";

	return result;
}

std::string Gameplay::SetWorld(std::string world)
{
	if (worlds.find(world) == worlds.end())
	{
		return "Error";
	}
	else
	{
		this->world = worlds[world];
		return "Success";
	}
}

std::string Gameplay::Update(std::string input)
{
	if (!setup)
	{
		return Setup();
	}

	std::vector<std::string> inputStrings = StringManager::Instance()->StringToVector(input, ' ');


	if (inputStrings[0] == "hiscore")
	{
		Game::Instance()->SetNextStage("NewHighScore");
		return "You have entered the magic word and will now see the \"New High Score\" screen.\n\n";
	}
	else if (inputStrings[0] == "quit")
	{
		Game::Instance()->SetNextStage("MainMenu");
		return "Your adventure has ended without fame or fortune.\n\n";
	}
	else if (inputStrings[0] == "look")
	{
		return Look(inputStrings) + "\n:> ";
	}
	else if (inputStrings[0] == "inventory")
	{
		return Look(StringManager::Instance()->StringToVector("look in inventory", ' ')) + "\n:> ";
	}
	else if (inputStrings[0] == "take")
	{
		return TakeFrom(inputStrings) + "\n:> ";
	}
	else if (inputStrings[0] == "pick" && inputStrings.size() >= 3 && inputStrings[1] == "up")
	{
		inputStrings.erase(inputStrings.begin());
		inputStrings[0] = "take";
		return TakeFrom(inputStrings) + "\n:> ";
	}
	else if (inputStrings[0] == "put")
	{
		return PutIn(inputStrings) + "\n:> ";
	}
	else if (inputStrings[0] == "drop")
	{
		return Drop(inputStrings) + "\n:> ";
	}

	return "I'm sorry, that is not valid input.\n:> ";
}

std::string Gameplay::Look(std::vector<std::string> input)
{
	if (input.size() == 1)
	{
		return "At your current location, you can see" + world->ViewItemsInCurrentLocation();
	}
	else if (input.size() >= 3)
	{
		if (input[1] == "at")
		{
			if (input[2] == "inventory")
			{
				return "In your inventory, you have" + player->ViewItems();
			}
			else if (input[2] == "location")
			{
				return "At your current location, you can see" + world->ViewItemsInCurrentLocation();
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
				return "In your inventory, you have" + player->ViewItems();
			}
			else if (input[2] == "location")
			{
				return "At your current location, you can see" + world->ViewItemsInCurrentLocation();
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

std::string Gameplay::TakeFrom(std::vector<std::string> input)
{
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
			for (int i = input.size() - 1; i >= 0; i--)
			{
				if (input[i] == "from")
				{
					//Get item and container names
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

	return "You can't take stuff like that.";
}

std::string Gameplay::PutIn(std::vector<std::string> input)
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
		for (int i = input.size() - 1; i >= 0; i--)
		{
			if (input[i] == "in")
			{
				//Get item and container names
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

				break;
			}
		}

		if (containerName.size() == 0)
		{
			return "What do you want to put '" + StringManager::Instance()->VectorToString(itemName, ' ') +"' in?";
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

std::string Gameplay::Drop(std::vector<std::string> input)
{
	input.erase(input.begin());

	/*if (StringManager::Instance()->VectorContainsString(input, "from") && StringManager::Instance()->VectorContainsString(input, "in"))
	{
		
	}
	else if (StringManager::Instance()->VectorContainsString(input, "in"))
	{
		
	}*/
	//if (StringManager::Instance()->VectorContainsString(input, "from"))
	//{
	//	std::vector<std::string> itemName = std::vector<std::string>();
	//	std::vector<std::string> containerName = std::vector<std::string>();

	//	//Find cut-off of item and container names
	//	for (int i = input.size() - 1; i >= 0; i--)
	//	{
	//		if (input[i] == "from")
	//		{
	//			//Get item and container names
	//			for (int j = 0; j < input.size(); j++)
	//			{
	//				if (j < i)
	//				{
	//					itemName.push_back(input[j]);
	//				}
	//				else if (j > i)
	//				{
	//					containerName.push_back(input[j]);
	//				}
	//			}

	//			break;
	//		}
	//	}

	//	if (containerName.size() == 0)
	//	{
	//		return "What do you want to take '" + StringManager::Instance()->VectorToString(itemName, ' ') + "' out of to drop it?";
	//	}

	//	if (!player->HasItem(containerName))
	//	{
	//		return "'" + StringManager::Instance()->VectorToString(containerName, ' ') + "' is not in your inventory";
	//	}

	//	Item* containerItemAsItem = player->GetItem(containerName);

	//	if (!containerItemAsItem->GetIsContainer())
	//	{
	//		return containerItemAsItem->GetName() + " is not a container.";
	//	}

	//	ContainerItem* containerItem = (ContainerItem*)containerItemAsItem;

	//	if (!containerItem->HasItem(itemName))
	//	{
	//		return "Item '" + StringManager::Instance()->VectorToString(itemName, ' ') + "' is not in " + containerItem->GetName() + ".";
	//	}

	//	Item* item = containerItem->GetItem(itemName);
	//	containerItem->RemoveItem(itemName);
	//	world->GetCurrentLocation()->AddItem(item);
	//	return "You dropped " + item->GetName() + ".";
	//}
	//else
	//{
		if (!player->HasItem(input))
		{
			return "Item '" + StringManager::Instance()->VectorToString(input, ' ') + "' is not in your inventory";
		}

		Item* item = player->GetItem(input);
		player->RemoveItem(input);
		world->GetCurrentLocation()->AddItem(item);
		return "You dropped " + item->GetName() + ".";
	//}
}
