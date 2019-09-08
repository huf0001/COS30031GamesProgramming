#include "Path.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

std::string Path::GetDescription()
{
	return description;
}

std::string Path::GetDestination()
{
	return destination;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

Path::Path(std::string destination, std::string description)
{
	this->description = description;
	this->destination = destination;
}


//Methods--------------------------------------------------------------------------------------------------------------------------------------------
