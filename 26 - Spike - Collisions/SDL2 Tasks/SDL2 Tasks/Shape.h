#include "pch.h"

#ifndef SHAPE_H
#define SHAPE_H

class Shape : public GameEntity
{
public:
	//Enums
	enum ShapeType
	{
		ShapeCircle,
		ShapeRectangle
	};

private:
	//Private Fields

	//Private Methods

protected:
	//Protected Fields
	ShapeType type;
	SDL_Color colour;
	bool outlined;
	Graphics* graphics;

	//Protected Methods

public:
	//Public Properties
	SDL_Color GetColour();
	void SetColour(SDL_Color value);
	bool GetOutlined();
	void SetOutlined(bool value);
	ShapeType GetType();

	//Constructor
	Shape(ShapeType type, SDL_Color colour, bool outlined, float x = 0.0f, float y = 0.0f);
	Shape(ShapeType type, SDL_Color colour, bool outlined, Vector2 pos);

	//Public Methods
	virtual void Render();
};

#endif
