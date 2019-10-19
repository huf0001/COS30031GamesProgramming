#include "Shape.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

SDL_Color Shape::GetColour()
{
	return colour;
}

void Shape::SetColour(SDL_Color value)
{
	colour = value;
}

bool Shape::GetOutlined()
{
	return outlined;
}

void Shape::SetOutlined(bool value)
{
	outlined = value;
}

Shape::ShapeType Shape::GetType()
{
	return type;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

Shape::Shape(ShapeType type, SDL_Color colour, bool outlined, float x, float y) : GameEntity(x, y)
{
	this->graphics = Graphics::Instance();
	this->type = type;
	this->colour = colour;
	this->outlined = outlined;
}

Shape::Shape(ShapeType type, SDL_Color colour, bool outlined, Vector2 pos)
{
	Shape(type, colour, pos.x, pos.y);
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

void Shape::Render()
{

}
