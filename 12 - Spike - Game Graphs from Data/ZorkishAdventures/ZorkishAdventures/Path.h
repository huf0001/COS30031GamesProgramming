#include "pch.h"

#ifndef PATH_H
#define PATH_H

#include "Location.h"

#include <string>

class Path
{
private:
	//Private fields
	std::string description;
	std::string destination;
protected:
public:
	//Public properties
	std::string GetDescription();
	std::string GetDestination();

	//Constructor
	Path(std::string destination, std::string description);
};

#endif
