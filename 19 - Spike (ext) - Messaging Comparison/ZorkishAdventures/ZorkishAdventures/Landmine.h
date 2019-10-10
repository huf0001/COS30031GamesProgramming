#include "pch.h"

#ifndef LANDMINE_H
#define LANDMINE_H

class Landmine : Component
{
private:
	//Private Fields

	//Private Methods

protected:
	//Protected Fields

	//Protected Methods

public:
	//Public Properties

	//Constructor
	Landmine(GameObject* gameObject);

	//Public Methods
	virtual Message* Notify(Message* message);
};

#endif
