#include "Item.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

//std::string Item::GetID()
//{
//	return id;
//}

//std::string Item::GetName()
//{
//	return name;
//}
//
//std::string Item::GetDescription()
//{
//	return description;
//}

//bool Item::GetIsContainer()
//{
//	return HasComponent("container");
//}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

Item::Item(std::string id, std::string name, std::string description) : GameObject(id, name, "item")
{
	/*this->id = id;
	this->name = name;*/
	AddComponent((Component*) new Description((GameObject*)this, description));
	//this->description = description;
	//this->isContainer = false;
}

//Item::Item(std::string id, std::string name, std::string description, bool isContainer)
//{
//	this->id = id;
//	this->name = name;
//	this->description = description;
//	//this->isContainer = isContainer;
//
//	if (isContainer)
//	{
//		AddComponent((Component*) new Container());
//	}
//}
