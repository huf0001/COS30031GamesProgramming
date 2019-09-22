#include "pch.h"

#ifndef DESCRIPTION_H
#define DESCRIPTION_H

class Description : Component
{
private:
	//Private Fields
	std::string description;

	//Private Methods

protected:
	//Protected Fields

	//Protected Methods

public:
	//Public Properties
	std::string GetDescription();

	//Constructor
	Description(GameObject* gameObject, std::string description);

	//Public Methods

};

#endif
