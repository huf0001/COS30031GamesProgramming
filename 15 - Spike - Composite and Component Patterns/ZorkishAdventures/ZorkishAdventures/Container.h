#include "pch.h"

#ifndef CONTAINER_H
#define CONTAINER_H

class Item;

class Container : Component
{
private:
	//Private Fields
	std::vector<Item*> items;

	//Private Methods

protected:
	//Protected Fields

	//Protected Methods

public:
	//Public Properties

	//Constructor
	Container(GameObject* gameObject);

	//Public Methods
	bool HasItem(std::vector<std::string> input);
	void AddItem(Item* item);
	Item* GetItem(std::vector<std::string> input);
	std::vector<Item*> GetItems();	//for testing only
	std::string ViewItem(std::vector<std::string> input);
	std::string ViewItems();
	void RemoveItem(std::vector<std::string> input);
};

#endif