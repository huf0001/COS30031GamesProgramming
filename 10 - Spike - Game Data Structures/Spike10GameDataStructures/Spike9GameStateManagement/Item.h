#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item
{
private:
	//Private Fields
	std::string id;
	std::string name;
	std::string description;
	bool isContainer;
public:
	//Public Properties
	std::string GetID();
	std::string GetName();
	std::string GetDescription();
	bool GetIsContainer();

	//Constructor
	Item(std::string id, std::string name, std::string description);
	Item(std::string id, std::string name, std::string description, bool isContainer);
};

#endif
