#ifndef PLAYER_H
#define PLAYER_H

#include "Container.h"
#include <string>

class Player : public Container
{
private:
	//Private Fields
	std::string name;
protected:
public:
	//Public Properties
	std::string GetName();

	//Constructor
	Player(std::string name);
};

#endif
