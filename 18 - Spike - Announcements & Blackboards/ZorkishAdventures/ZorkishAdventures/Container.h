#include "pch.h"

#ifndef CONTAINER_H
#define CONTAINER_H

class Item;

class Container : Component
{
private:
	//Private Fields
	std::vector<Item*> items;
	bool isOpen;
	bool alwaysOpen;

	//Private Methods

protected:
	//Protected Fields

	//Protected Methods

public:
	//Public Properties
	bool GetAlwaysOpen();
	bool GetIsOpen();
	void SetIsOpen(bool value);

	//Constructor
	Container(GameObject* gameObject, bool alwaysOpen, bool isOpen);

	//Public Methods
	bool HasItem(std::vector<std::string> input);
	void AddItem(Item* item);
	Item* GetItem(std::vector<std::string> input);
	std::vector<Item*> GetItems();	//for testing only
	std::string ViewItem(std::vector<std::string> input);
	std::string ViewItems();
	void RemoveItem(std::vector<std::string> input);
	virtual Message* Notify(Message* message);
};

#endif