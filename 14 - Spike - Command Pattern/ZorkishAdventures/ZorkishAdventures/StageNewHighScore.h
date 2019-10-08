#include "pch.h"

#ifndef STAGENEWHIGHSCORE_H
#define STAGENEWHIGHSCORE_H

class StageNewHighScore : Stage
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
	StageNewHighScore();

	//Public Methods
	std::string Update(std::string input);
};

#endif
