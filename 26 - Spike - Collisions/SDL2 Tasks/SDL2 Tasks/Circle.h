#include "pch.h"

#ifndef CIRCLE_H
#define CIRCLE_H

class Circle : public Shape
{
private:
	//Private Fields
	float radius;

	//Private Methods

protected:
	//Protected Fields

	//Protected Methods

public:
	//Public Properties
	float GetRadius();
	void SetRadius(float value);

	//Constructor
	Circle(float radius, SDL_Color colour, bool outlined, float x = 0.0f, float y = 0.0f);
	Circle(float radius, SDL_Color colour, bool outlined, Vector2 pos);

	//Public Methods
	virtual void Render();
};

#endif
