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
	//std::string SetDescription(std::string value);

	//Constructor
	//Description(GameObject* gameObject);
	Description(GameObject* gameObject, std::string description);

	//Public Methods

};

#endif
