#include "pch.h"

#ifndef ITEM_H
#define ITEM_H

class Item : public GameObject
{
private:
	//Private Fields
	//std::string id;
	/*std::string name;
	std::string description;*/
	//bool isContainer;
public:
	//Public Properties
	//std::string GetID();
	/*std::string GetName();
	std::string GetDescription();*/
	//bool GetIsContainer();

	//Constructor
	Item(std::string id, std::string name, std::string description);
	/*Item(std::string id, std::string name, std::string description, bool isContainer);*/
};

#endif
