#include "pch.h"

#ifndef BUTTON_H
#define BUTTON_H

class Button : Component
{
private:
	//Private Fields
	std::string triggersType;
	std::string triggersAtLocation;

	//Private Methods

protected:
	//Protected Fields

	//Protected Methods

public:
	//Public Properties

	//Constructor
	Button(GameObject* gameObject, std::string triggersType, std::string triggersAtLocation);

	//Public Methods
	virtual Message* Notify(Message* message);
};

#endif
