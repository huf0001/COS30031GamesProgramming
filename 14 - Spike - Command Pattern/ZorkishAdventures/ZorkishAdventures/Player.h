#include "pch.h"

#ifndef PLAYER_H
#define PLAYER_H

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
