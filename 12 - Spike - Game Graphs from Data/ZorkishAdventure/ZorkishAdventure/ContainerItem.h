#ifndef CONTAINERITEM_H
#define CONTAINERITEM_H

#include "Container.h"
#include "Item.h"

class ContainerItem : public Container, public Item
{
private:
protected:
public:
	//Constructor
	ContainerItem(std::string id, std::string name, std::string description);
};

#endif
