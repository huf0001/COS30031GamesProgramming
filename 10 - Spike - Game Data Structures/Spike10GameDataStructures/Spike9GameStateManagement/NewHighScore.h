#include "pch.h"

#ifndef NEWHIGHSCORE_H
#define NEWHIGHSCORE_H

#include "Stage.h"
#include "Gameplay.h"

class NewHighScore : Stage
{
private:
	//Private Fields

	//Private Methods

protected:
	//Protected Fields

	//Protected Methods
	std::string Setup();
public:
	//Constructor
	NewHighScore();

	//Public Methods
	std::string Update(std::string input);
};

#endif
