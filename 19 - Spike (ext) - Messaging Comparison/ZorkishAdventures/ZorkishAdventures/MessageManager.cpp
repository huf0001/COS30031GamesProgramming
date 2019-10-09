#include "MessageManager.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

MessageManager* MessageManager::instance = 0;

MessageManager* MessageManager::Instance()
{
	if (!instance)
	{
		instance = new MessageManager();
	}

	return instance;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

MessageManager::MessageManager()
{
	subscribedPlayer = nullptr;
	subscribedWorld = nullptr;
	subscribedCommands = std::map<std::string, Command*>();
	subscribedLocations = std::map<std::string, Location*>();
	subscribedPathsInLocation = std::map<std::string, std::map<std::string, Path*>>();
	subscribedItemsInContainer = std::map<std::string, std::map<std::string, Item*>>();

	receiverTypes = std::map<std::string, ReceiverType>();
	receiverTypes["player"] = ReceiverPlayer;
	receiverTypes["world"] = ReceiverWorld;
	receiverTypes["command"] = ReceiverCommand;
	receiverTypes["location"] = ReceiverLocation;
	receiverTypes["path"] = ReceiverPath;
	receiverTypes["gameobject"] = ReceiverGameObject;
	receiverTypes["item"] = ReceiverItem;
	receiverTypes["button"] = ReceiverButton;
	receiverTypes["container"] = ReceiverContainer;
	receiverTypes["description"] = ReceiverDescription;
	receiverTypes["flammable"] = ReceiverFlammable;
	receiverTypes["landmine"] = ReceiverLandmine;
	receiverTypes["lock"] = ReceiverLock;
	receiverTypes["movable"] = ReceiverMovable;
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

void MessageManager::Subscribe(Player* player)
{
	if (subscribedPlayer != nullptr)
	{
		std::cout << "Warning: a player is already subscribed to MessageManager.\n";
	}
	else
	{
		subscribedPlayer = player;
	}
}

void MessageManager::Subscribe(World* world)
{
	if (subscribedWorld != nullptr)
	{
		std::cout << "Warning: a world is already subscribed to MessageManager.\n";
	}
	else
	{
		subscribedWorld = world;
	}
}

void MessageManager::Subscribe(Command* command)
{
	if (subscribedCommands.count(command->GetName()))
	{
		std::cout << "Warning: a command with name \"" + command->GetName() + "\" is already subscribed to MessageManager.\n";
	}
	else
	{
		subscribedCommands[command->GetName()] = command;
	}
}

void MessageManager::Subscribe(Location* location)
{
	if (subscribedLocations.count(location->GetID()))
	{
		std::cout << "Warning: a location with ID \"" + location->GetID() + "\" is already subscribed to MessageManager.\n";
	}
	else
	{
		subscribedLocations[location->GetID()] = location;
	}
}

void MessageManager::Subscribe(std::string location, Path* path)
{
	if (!subscribedPathsInLocation.count(location))
	{
		subscribedPathsInLocation[location] = std::map<std::string, Path*>();
	}
	
	if (!subscribedPathsInLocation[location].count(path->GetID()))
	{
		subscribedPathsInLocation[location][path->GetID()] = path;
	}
	else
	{
		std::cout << "Warning: a path with ID \"" + path->GetID() + "\" in location \"" + location + "\" is already subscribed to MessageManager.\n";
	}
}

void MessageManager::Subscribe(std::string container, Item* item)
{
	if (!subscribedItemsInContainer.count(container))
	{
		subscribedItemsInContainer[container] = std::map<std::string, Item*>();
	}

	if (!subscribedItemsInContainer[container].count(item->GetID()))
	{
		subscribedItemsInContainer[container][item->GetID()] = item;
	}
	else
	{
		std::cout << "Warning: an Item with ID \"" + item->GetID() + "\" in container \"" + container + "\" is already subscribed to MessageManager.\n";
	}
}

void MessageManager::Unsubscribe(std::string type)
{
	if (type == "player")
	{
		subscribedPlayer = nullptr;
	}
	else if (type == "world")
	{
		subscribedWorld = nullptr;
	}
	else
	{
		std::cout << "Warning: can't unsubscribe subscriber of type \"" + type + "\". Invalid subscriber type \"" + type + "\".\n";
	}
}

void MessageManager::Unsubscribe(std::string type, std::string subscriberId)
{
	if (type == "command")
	{
		if (subscribedCommands.count(subscriberId))
		{
			subscribedCommands.erase(subscriberId);
		}
	}
	else if (type == "location")
	{
		if (subscribedLocations.count(subscriberId))
		{
			subscribedLocations.erase(subscriberId);
		}
	}
	else
	{
		std::cout << "Warning: can't unsubscribe subscriber with ID \"" + subscriberId + "\". Invalid subscriber type \"" + type + "\".\n";
	}
}

void MessageManager::Unsubscribe(std::string type, std::string subscriberId, std::string containerId)
{
	if (type == "path")
	{
		if (subscribedPathsInLocation.count(containerId) && subscribedPathsInLocation[containerId].count(subscriberId))
		{
			subscribedPathsInLocation[containerId].erase(subscriberId);
		}
	}
	else if (type == "item")
	{
		if (subscribedItemsInContainer.count(containerId) && subscribedItemsInContainer[containerId].count(subscriberId))
		{
			subscribedItemsInContainer[containerId].erase(subscriberId);
		}
	}
	else
	{
		std::cout << "Warning: can't unsubscribe subscriber with ID \"" + subscriberId + "\". Invalid subscriber type \"" + type + "\".\n";
	}
}

void MessageManager::UnsubscribeAll()
{
	subscribedPlayer;
	subscribedWorld;
	subscribedCommands.clear();
	subscribedLocations.clear();
	subscribedPathsInLocation.clear();
	subscribedItemsInContainer.clear();
}

Message* MessageManager::SendMessage(Message* message)
{
	switch (receiverTypes[message->GetReceiverType()])
	{
		case ReceiverPlayer:
			if (subscribedPlayer != nullptr)
			{
				return subscribedPlayer->Notify(message);
			}

			return nullptr;
		/*case ReceiverWorld:
			if (subscribedWorld != nullptr)
			{
				return subscribedWorld->Notify(message);
			}
			else
			{
				return nullptr;
			}

			break;*/
		/*case ReceiverCommand:
			if (subscribedCommands.count(message->GetReceiverID()))
			{
				return subscribedCommands[message->GetReceiverID()].Notify(message);
			}

			return nullptr;*/
		case ReceiverLocation:
			if (subscribedLocations.count(message->GetReceiverID()))
			{
				return subscribedLocations[message->GetReceiverID()]->Notify(message);
			}

			return nullptr;
		case ReceiverPath:
			if (subscribedPathsInLocation.count(message->GetReceiverParentID()) && subscribedPathsInLocation[message->GetReceiverParentID()].count(message->GetReceiverID()))
			{
				return subscribedPathsInLocation[message->GetReceiverParentID()][message->GetReceiverID()]->Notify(message);
			}

			return nullptr;
		case ReceiverGameObject:
		case ReceiverItem:
		case ReceiverButton:
		case ReceiverContainer:
		case ReceiverDescription:
		case ReceiverFlammable:
		case ReceiverLandmine:
		case ReceiverLock:
		case ReceiverMovable:
			if (subscribedItemsInContainer.count(message->GetReceiverParentID()) && subscribedItemsInContainer[message->GetReceiverParentID()].count(message->GetReceiverID()))
			{
				return subscribedItemsInContainer[message->GetReceiverParentID()][message->GetReceiverID()]->Notify(message);
			}

			return nullptr;
		default:
			return nullptr;
	}
}

//Message* MessageManager::SendMessage(Message* message, std::string container)
//{
//	switch (receiverTypes[message->GetReceiverType()])
//	{
//		
//		default:
//			return nullptr;
//	}
//}

