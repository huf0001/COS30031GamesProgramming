#include "pch.h"

#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle : public Shape
{
private:
	//Private Fields
	float width;
	float height;
	SDL_Rect renderRect;

	//Private Methods

protected:
	//Protected Fields

	//Protected Methods

public:
	//Public Properties
	float GetWidth();
	void SetWidth(float value);
	float GetHeight();
	void SetHeight(float value);
	bool GetOutlined();
	void SetOutlined(bool value);

	//Constructor
	Rectangle(int w, int h, SDL_Color colour, bool outlined, float x = 0.0f, float y = 0.0f);
	Rectangle(int w, int h, SDL_Color colour, bool outlined, Vector2 pos);

	//Public Methods
	virtual void Render();
};

#endif
