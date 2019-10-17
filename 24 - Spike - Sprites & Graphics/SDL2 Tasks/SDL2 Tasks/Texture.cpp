#include "Texture.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

Texture::Texture(std::string path)
{
	graphics = Graphics::Instance();
	texture = graphics->LoadTexture(path);
}

//Destructor-----------------------------------------------------------------------------------------------------------------------------------------

Texture::~Texture()
{
	SDL_DestroyTexture(texture);
	texture = NULL;
	graphics = NULL;
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

void Texture::Render()
{
	graphics->DrawTexture(texture);
}