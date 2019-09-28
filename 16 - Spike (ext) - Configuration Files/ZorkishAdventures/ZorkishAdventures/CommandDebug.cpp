#include "CommandDebug.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

std::string CommandDebug::GetSyntax()
{
	std::string result;

	result += "DEBUG\n";
	result += "----------------------------\n";
	result += "Function:\n";
	result += "\t- Provides all information on the current location, its paths and items, and the player's inventory.\n";
	result += "Syntax:\n";
	result += "\t- \"debug\"\n";

	if (aliases.size() > 0)
	{
		result += "Aliases for \"debug\":\n";

		for (std::string alias : aliases)
		{
			result += "\t- \"" + alias + "\"\n";
		}
	}

	return result;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

CommandDebug::CommandDebug() : Command("DEBUG")
{
	AddKeyword("debug");
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

std::string CommandDebug::DebugPlayer(Player* player)
{
	std::string result;
	std::vector<Item*> items = ((Container*)player->GetComponent("container"))->GetItems();

	result += "Debugging Player\n";
	result += "----------------------------\n";
	result += "Name: " + player->GetName() + "\n";
	result += "Inventory Item Count: " + std::to_string(items.size()) + "\n";

	for (Item* i : items)
	{
		result += "\n";
		result += DebugItem(i, "player");
	}	

	return result;
}

std::string CommandDebug::DebugWorld(World* world)
{
	std::string result;

	result += "Debugging World\n";
	result += "----------------------------\n";
	result += "Name: " + world->GetName() + "\n";

	if (world->GetLoadedSuccessfully())
	{
		result += "Loaded Successfully: Yes\n";
	}
	else
	{
		result += "Loaded Successfully: No\n";
	}

	result += "Current Location: " + world->GetCurrentLocation()->GetName() + "\n";
	result += "\n";
	result += DebugLocation(world->GetCurrentLocation());

	return result;
}

std::string CommandDebug::DebugLocation(Location* location)
{
	std::string result;
	std::vector<Item*> items = ((Container*)location->GetComponent("container"))->GetItems();
	std::map<std::string, Path*> paths = location->GetPaths();

	result += "Debugging Location\n";
	result += "----------------------------\n";
	result += "ID: " + location->GetID() + "\n";
	result += "Name: " + location->GetName() + "\n";
	result += "Description: " + ((Description*)location->GetComponent("description"))->GetDescription() + "\n";
	result += "Path Count: " + std::to_string(paths.size()) + "\n";
	result += "Item Count: " + std::to_string(items.size()) + "\n";

	for (std::pair<std::string, Path*> pair : paths)
	{
		result += "\n";
		result += DebugPath(pair.second, location->GetID(), pair.first);
	}

	for (Item* i : items)
	{
		result += "\n";
		result += DebugItem(i, location->GetID());
	}

	return result;
}

std::string CommandDebug::DebugPath(Path* path, std::string locationId, std::string pathDirection)
{
	std::string result;

	result += "Debugging Path\n";
	result += "----------------------------\n";
	result += "Location ID: " + locationId + "\n";
	result += "Path Direction: " + pathDirection + "\n";
	result += "Description: " + ((Description*)path->GetComponent("description"))->GetDescription() + "\n";
	result += "Destination ID: " + path->GetDestination() + "\n";

	return result;
}

std::string CommandDebug::DebugItem(Item* item, std::string containerId)
{
	std::string result;

	result += "Debugging Item\n";
	result += "----------------------------\n";
	result += "Container ID: " + containerId +"\n";
	result += "ID: " + item->GetID() + "\n";
	result += "Name: " + item->GetName() + "\n";
	result += "Description: " + ((Description*)item->GetComponent("description"))->GetDescription() + "\n";

	if (item->HasComponent("container"))
	{
		std::vector<Item*> items = ((Container*)item->GetComponent("container"))->GetItems();

		result += "Is Container?: Yes\n";
		result += "Item Count: " + std::to_string(items.size()) + "\n";

		for (Item* i : items)
		{
			result += "\n";
			result += DebugItem(i, item->GetID());
		}
	}
	else
	{
		result += "Is Container?: No\n";
	}

	return result;
}

std::string CommandDebug::Process(std::vector<std::string> input, World* world, Player* player)
{
	std::string result;

	result += "DEBUGGING\n";
	result += "--------------------------------------------------------\n";
	result += "\n";
	result += DebugPlayer(player);
	result += "\n";
	result += DebugWorld(world);
	result += "\n";
	result += "DEBUGGING COMPLETE";

	return result;
}