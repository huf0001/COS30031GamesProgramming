#include "pch.h"

#ifndef CONTAINERITEM_H
#define CONTAINERITEM_H

class ContainerItem : public Container, public Item
{
private:
protected:
public:
	//Constructor
	ContainerItem(std::string id, std::string name, std::string description);
};

#endif
