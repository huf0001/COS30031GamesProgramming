#include "pch.h"

#include "ContainerItem.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

ContainerItem::ContainerItem(std::string id, std::string name, std::string description):Container(),Item(id, name, description, true)
{
	
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------