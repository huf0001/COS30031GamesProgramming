#include "Rectangle.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

float Rectangle::GetWidth()
{
	return width;
}

void Rectangle::SetWidth(float value)
{
	width = value;
	renderRect.w = value;
}

float Rectangle::GetHeight()
{
	return height;
}

void Rectangle::SetHeight(float value)
{
	height = value;
	renderRect.h = value;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

Rectangle::Rectangle(int w, int h, SDL_Color colour, bool outlined, float x, float y) : Shape(ShapeRectangle, colour, outlined, x, y)
{
	this->renderRect = SDL_Rect();
	this->width = w;
	this->renderRect.w = w;
	this->height = h;
	this->renderRect.h = h;
}

Rectangle::Rectangle(int w, int h, SDL_Color colour, bool outlined, Vector2 pos) : Shape(ShapeRectangle, colour, outlined, pos)
{
	this->renderRect = SDL_Rect();
	this->width = w;
	this->renderRect.w = w;
	this->height = h;
	this->renderRect.h = h;
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

void Rectangle::Render()
{
	//Treats position as the centre of the rectangle
	Vector2 pos = GetPos(world);
	renderRect.x = (int)(pos.x - width * 0.5f);
	renderRect.y = (int)(pos.y - height * 0.5f);

	//Draw rectangle of width width and height height, and of colour Rectangle.colour
	graphics->DrawRectangle(colour, outlined, &renderRect);
}