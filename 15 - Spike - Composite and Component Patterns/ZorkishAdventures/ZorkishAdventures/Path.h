#include "pch.h"

#ifndef PATH_H
#define PATH_H

class Path : public GameObject
{
private:
	//Private fields
	/*std::string description;*/
	std::string destination;
protected:
public:
	//Public properties
	//std::string GetDescription();
	std::string GetDestination();

	//Constructor
	Path(std::string id, std::string name, std::string destination, std::string description);
};

#endif
