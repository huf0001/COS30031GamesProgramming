#include "pch.h"

#ifndef TEXTURE_H
#define TEXTURE_H

class Texture : public GameEntity
{
private:
	//Private Fields
	SDL_Texture* texture;
	Graphics* graphics;

	//Private Methods

protected:
	//Protected Fields

	//Protected Methods

public:
	//Public Properties

	//Constructor
	Texture(std::string path);

	//Destructor
	~Texture();

	//Public Methods
	virtual void Render();
};

#endif
