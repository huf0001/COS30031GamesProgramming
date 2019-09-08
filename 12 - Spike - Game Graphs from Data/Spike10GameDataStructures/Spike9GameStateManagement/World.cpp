#include "pch.h"

#include "World.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

std::string World::GetName()
{
	return name;
}

Location* World::GetCurrentLocation()
{
	return currentLocation;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

World::World(std::string name)
{
	//Assign to fields
	this->name = name;
	locations = std::map<std::string, Location*>();

	//Setup locations in world
	locations["Void"] = new Location("Void", "The Void", "This world is simple and pointless. Used to test Zorkish phase 1 spec.");

	//Set starting location
	currentLocation = locations["Void"];

	//Flesh out testing location "Void"
	currentLocation->AddItem(new Item("book", "Book", "A dusty old book."));
	currentLocation->AddItem(new Item("pencil", "Pencil", "A short, used pencil."));
	currentLocation->AddItem(new Item("glasses", "Glasses", "A pair of glasses."));
	currentLocation->AddItem(new Item("quill", "Quill", "A black and grey quill."));

	currentLocation->AddItem((Item*) new ContainerItem("bag", "Bag", "A red bag."));
	ContainerItem* bag = (ContainerItem*)currentLocation->GetItem(StringManager::Instance()->StringToVector("bag", ' '));
	bag->AddItem(new Item("gold coin", "Gold Coin", "A gold coin. This is valuable."));
	bag->AddItem(new Item("silver coin", "Silver Coin", "A silver coin. This is worth a bit."));
	bag->AddItem(new Item("copper coin", "Copper Coin", "A copper coin. This is not worth much."));
	bag->AddItem(new ContainerItem("box", "Box", "A small wooden box."));
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

std::string World::DescribeCurrentLocation()
{
	return currentLocation->GetDescription();
}

std::string World::ViewItemsInCurrentLocation()
{
	return currentLocation->ViewItems();
}
