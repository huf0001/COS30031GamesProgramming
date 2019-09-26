#include "CommandDrop.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

std::string CommandDrop::GetSyntax()
{
	std::string result;

	result += "DROP\n";
	result += "----------------------------\n";
	result += "Function:\n";
	result += "\t- Drop an item from your inventory into your current location.\n";
	result += "Syntax:\n";
	result += "\t- \"drop [item]\"\n";

	if (aliases.size() > 0)
	{
		result += "Aliases for \"drop\":\n";

		for (std::string alias : aliases)
		{
			result += "\t- \"" + alias + "\"\n";
		}
	}

	return result;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

CommandDrop::CommandDrop()
{
	AddKeyword("drop");
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

std::string CommandDrop::Process(std::vector<std::string> input, World* world, Player* player)
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
	if (!((Container*)player->GetComponent("container"))->HasItem(input))
	{
		return "Item '" + StringManager::Instance()->VectorToString(input, ' ') + "' is not in your inventory";
	}

	Item* item = ((Container*)player->GetComponent("container"))->GetItem(input);
	((Container*)player->GetComponent("container"))->RemoveItem(input);
	((Container*)world->GetCurrentLocation()->GetComponent("container"))->AddItem(item);
	return "You dropped " + item->GetName() + ".";
	//}
}