#include "CommandLook.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

std::string CommandLook::GetSyntax()
{
	std::string result;

	result += "LOOK\n";
	result += "----------------------------\n";
	result += "Function:\n";
	result += "\t- Look at your current location. Directions you can move in are CAPITALISED.\n";
	result += "\t- Look at your inventory.\n";
	result += "\t- Look at an item.\n";
	result += "\t- Look at an item in a container (including your current location or inventory).\n";
	result += "Syntax:\n";
	result += "\t- \"look\" (same as \"look at location\")\n";
	result += "\t- \"look at [item]\"\n";
	result += "\t- \"look in [container]\"\n";
	//result += "\t- \"look inside ___\"\n";
	result += "\t- \"look at [item] in [container]\"\n";
	//result += "\t- \"look at ___ inside ___\"\n";
	//result += "\t- \"inspect ___\"\n";	==> inspect = alias of "look"
	//result += "\t- \"inspect in ___\"\n";
	//result += "\t- \"inspect inside ___\"\n";
	//result += "\t- \"inspect ___ in ___\"\n";
	//result += "\t- \"inspect ___ inside ___\"\n";
	result += "\t- \"inventory\" (same as \"look at inventory\")\n";

	if (aliases.size() > 0)
	{
		result += "Aliases for \"look\":\n";

		for (std::string alias : aliases)
		{
			result += "\t- \"" + alias + "\"\n";
		}
	}

	return result;
}

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
		visible = " nothing; it\"\ns empty.";
	}

	return "You are in " + world->DescribeCurrentLocation() + " There, you can see" + visible;
}

std::string CommandLook::LookAtInventory(Player* player)
{
	std::string visible = ":" + ((Container*)player->GetComponent("container"))->ViewItems();

	if (visible == ":")
	{
		visible = " nothing; it\"\ns empty.";
	}

	return "In your inventory, you have" + visible;
}

std::vector<std::string> CommandLook::StandardiseInput(std::vector<std::string> input)
{
	if (input.size() == 1 && input[0] == "inventory")
	{
		input = StringManager::Instance()->StringToVector("look at inventory", ' ');
	}

	return input;
}

std::string CommandLook::Process(std::vector<std::string> input, World* world, Player* player)
{
	input = StandardiseInput(input);

	if (input.size() == 1)
	{	
		return LookAtLocation(world);
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

			for (int i = (int)input.size() - 1; i >= 0; i--)
			{
				if (input[i] == "in")
				{
					std::vector<std::string> itemName = std::vector<std::string>();
					std::vector<std::string> containerName = std::vector<std::string>();

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

					if (i == input.size() - 1)
					{
						return "What do you want to look inside to look for \"\n" + StringManager::Instance()->VectorToString(itemName, ' ') + "\"\n?";
					}
					else
					{
						Item* item = nullptr;

						if (StringManager::Instance()->VectorToString(containerName, ' ') == "inventory")
						{
							if (((Container*)player->GetComponent("container"))->HasItem(itemName))
							{
								return ((Container*)player->GetComponent("container"))->ViewItem(itemName);
							}
							else
							{
								return "You can\"\nt find \"\n" + StringManager::Instance()->VectorToString(itemName, ' ') + "\"\n in your inventory.";
							}
						}
						else if (StringManager::Instance()->VectorToString(containerName, ' ') == "location")
						{
							if (((Container*)world->GetCurrentLocation()->GetComponent("container"))->HasItem(itemName))
							{
								return ((Container*)world->GetCurrentLocation()->GetComponent("container"))->ViewItem(itemName);
							}
							else
							{
								return "You can\"\nt find \"\n" + StringManager::Instance()->VectorToString(itemName, ' ') + "\"\n at your current location.";
							}
						}
						else
						{
							if (((Container*)player->GetComponent("container"))->HasItem(containerName))
							{
								item = ((Container*)player->GetComponent("container"))->GetItem(containerName);
							}
							else if (((Container*)world->GetCurrentLocation()->GetComponent("container"))->HasItem(containerName))
							{
								item = ((Container*)world->GetCurrentLocation()->GetComponent("container"))->GetItem(containerName);
							}

							if (item == nullptr)
							{
								return "You can\"\nt look in \"\n" + StringManager::Instance()->VectorToString(containerName, ' ') + "\"\n.";
							}
							else if (!item->HasComponent("container"))
							{
								return "You can\"\nt look in \"\n" + item->GetName() + "\"\n; it\"\ns not a container.";
							}
							else
							{
								return ((Container*)item->GetComponent("container"))->ViewItem(itemName);
							}
						}
					}
				}
			}

			Item* item = nullptr;

			if (((Container*)player->GetComponent("container"))->HasItem(input))
			{
				item = ((Container*)player->GetComponent("container"))->GetItem(input);
			}
			else if (((Container*)world->GetCurrentLocation()->GetComponent("container"))->HasItem(input))
			{
				item = ((Container*)world->GetCurrentLocation()->GetComponent("container"))->GetItem(input);
			}

			if (item == nullptr)
			{
				return "You cannot find \"\n" + StringManager::Instance()->VectorToString(input, ' ') + "\"\n.";
			}
			else
			{
				return ((Description*)item->GetComponent("description"))->GetDescription();
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

			if (((Container*)player->GetComponent("container"))->HasItem(input))
			{
				item = ((Container*)player->GetComponent("container"))->GetItem(input);
			}
			else if (((Container*)world->GetCurrentLocation()->GetComponent("container"))->HasItem(input))
			{
				item = ((Container*)world->GetCurrentLocation()->GetComponent("container"))->GetItem(input);
			}

			if (item == nullptr)
			{
				return "You cannot look in \"\n" + StringManager::Instance()->VectorToString(input, ' ') + "\"\n.";
			}
			else if (!item->HasComponent("container"))
			{
				return "You can\"\nt look in \"\n" + item->GetName() + "\"\n; it\"\ns not a container.";
			}
			else
			{
				return "In " + StringManager::Instance()->VectorToString(input, ' ') + ", you can see" + ((Container*)item->GetComponent("container"))->ViewItems();
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

	return "You can\"\nt look like that.";
}
