#include "pch.h"

#ifndef CONTAINER_H
#define CONTAINER_H

#include "Item.h"
#include "StringManager.h"
#include <vector>

class Container
{
private:
	//Private Fields
	std::vector<Item*> items;

	//Private Methods

protected:
	//Protected Fields

	//Constructor
	Container();
public:
	//Public Properties

	//Public Methods
	void AddItem(Item* item);
	bool HasItem(std::vector<std::string> input);
	Item* GetItem(std::vector<std::string> input);
	std::string ViewItem(std::vector<std::string> input);
	void RemoveItem(std::vector<std::string> input);
	std::string ViewItems();
};

#endif