#include "Path.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

std::string Path::GetDestination()
{
	return destination;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

Path::Path(std::string id, std::string name, std::string destination, std::string description) : GameObject(id, name, "path")
{
	this->destination = destination;
	AddComponent((Component*) new Description((GameObject*)this, description));
}


//Methods--------------------------------------------------------------------------------------------------------------------------------------------
