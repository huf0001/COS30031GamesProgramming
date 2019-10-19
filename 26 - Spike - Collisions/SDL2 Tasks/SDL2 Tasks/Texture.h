#include "pch.h"

#ifndef TEXTURE_H
#define TEXTURE_H

class Texture : public GameEntity
{
private:
	//Private Fields
	SDL_Texture* texture;
	Graphics* graphics;

	int width;
	int height;

	bool clipped;
	SDL_Rect renderRect;
	SDL_Rect clipRect;

	//Private Methods

protected:
	//Protected Fields

	//Protected Methods

public:
	//Public Properties
	int GetWidth();
	void SetWidth(int value);
	int GetHeight();
	void SetHeight(int value);

	//Constructor
	Texture(std::string filename);
	Texture(std::string filename, int x, int y, int w, int h);

	//Destructor
	~Texture();

	//Public Methods
	virtual void Render();
};

#endif
