#include "Rectangle.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

//Y-axis starts at top and goes to bottom, therefore bottom and top to the computer are inverted compared to our perception
//Assumes rectangles don't themselves rotate but might be rotated around a parent but remain axis-aligned
Vector2 Rectangle::GetTopRight(SPACE space)
{
	Vector2 localPos = GetPos(local);
	Vector2 localOffset = Vector2(width * 0.5, height * 0.5);

	if (space == local || GetParent() == NULL)
	{
		return localPos + localOffset;
	}

	//Parent pos + rotated offset relative to parent + local offset of bottom right
	return GetParent()->GetPos(world) + RotateVector(localPos, GetParent()->GetRotation(local)) + localOffset;
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

bool Rectangle::GetOutlined()
{
	return outlined;
}

void Rectangle::SetOutlined(bool value)
{
	outlined = value;
}

//Y-axis starts at top and goes to bottom, therefore bottom and top to the computer are inverted compared to our perception
//Assumes rectangles don't themselves rotate but might be rotated around a parent but remain axis-aligned
Vector2 Rectangle::GetBottomLeft(SPACE space)
{
	Vector2 localPos = GetPos(local);
	Vector2 localOffset = Vector2(width * 0.5, height * 0.5);

	if (space == local || GetParent() == NULL)
	{
		return localPos - localOffset;
	}

	//Parent pos + rotated offset relative to parent + local offset of top left
	return GetParent()->GetPos(world) + RotateVector(localPos, GetParent()->GetRotation(local)) - localOffset;
}

float Rectangle::GetWidth()
{
	return width;
}

void Rectangle::SetWidth(float value)
{
	width = value;
	renderRect.w = value;
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
	
	////Check axis-aligned rotation of GetBottomLeft() and GetTopRight()
	//graphics->DrawCircle(graphics->GetColour("green"), true, 10, GetBottomLeft(world));
	//graphics->DrawCircle(graphics->GetColour("blue"), true, 10, GetTopRight(world));
}