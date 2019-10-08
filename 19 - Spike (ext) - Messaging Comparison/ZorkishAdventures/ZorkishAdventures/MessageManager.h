#include "pch.h"

#ifndef MESSAGEMANAGER_H
#define MESSAGEMANAGER_H

class GameObject;
class Command;
class Location;
class Path;
class Item;
class Player;
class World;

class MessageManager
{
private:
	//Enum
	enum ReceiverType
	{
		ReceiverPlayer,
		ReceiverWorld,
		ReceiverCommand,
		ReceiverLocation,
		ReceiverPath,
		ReceiverGameObject,
		ReceiverItem,
		ReceiverButton,
		ReceiverContainer,
		ReceiverDescription,
		ReceiverFlammable,
		ReceiverLandmine,
		ReceiverLock,
		ReceiverMovable
	};
	
	//Private Fields
	static MessageManager* instance;
	Player* subscribedPlayer;
	World* subscribedWorld;
	std::map<std::string, Command*> subscribedCommands;
	std::map<std::string, Location*> subscribedLocations;
	std::map<std::string, std::map<std::string, Path*>> subscribedPathsInLocation;
	std::map<std::string, std::map<std::string, Item*>> subscribedItemsInContainer;
	std::map<std::string, ReceiverType> receiverTypes;

	//Constructor
	MessageManager();

	//Private Methods

protected:
	//Protected Fields

	//Protected Methods

public:
	//Public Properties
	static MessageManager* Instance();

	//Public Methods
	void Subscribe(Player* player);
	void Subscribe(World* world);
	void Subscribe(Command* command);
	void Subscribe(Location* location);
	void Subscribe(std::string location, Path* path);
	void Subscribe(std::string container, Item* item);
	void Unsubscribe(std::string type);
	void Unsubscribe(std::string type, std::string subscriberId);
	void Unsubscribe(std::string type, std::string subscriberId, std::string containerId);
	void UnsubscribeAll();
	Message* SendMessage(Message* message);
	Message* SendMessage(Message* message, std::string);
};

#endif