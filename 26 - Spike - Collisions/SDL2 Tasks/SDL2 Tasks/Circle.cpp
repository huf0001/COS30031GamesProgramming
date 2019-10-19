#include "Circle.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

float Circle::GetRadius()
{
	return radius;
}

void Circle::SetRadius(float value)
{
	radius = value;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

Circle::Circle(float radius, SDL_Color colour, bool outlined, float x, float y) : Shape(ShapeCircle, colour, outlined, x, y)
{
	this->radius = radius;
}

Circle::Circle(float radius, SDL_Color colour, bool outlined, Vector2 pos) : Shape(ShapeCircle, colour, outlined, pos)
{
	this->radius = radius;
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

void Circle::Render()
{
	//Render circle of colour Circle.colour and radius Circle.radius
	graphics->DrawCircle(colour, outlined, radius, GetPos(world));
}
