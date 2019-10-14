#include "pch.h"

#ifndef FLAMMABLE_H
#define FLAMMABLE_H

class Flammable : Component
{
private:
	//Private Fields
	bool ignited;

	//Private Methods

protected:
	//Protected Fields
	
	//Protected Methods

public:
	//Public Properties

	//Constructor
	Flammable(GameObject* gameObject);

	//Public Methods
	virtual Message* Notify(Message* message);
};

#endif
