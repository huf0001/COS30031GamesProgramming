#include "Texture.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

int Texture::GetWidth()
{
	return width;
}

void Texture::SetWidth(int value)
{
	width = value;
	renderRect.w = value;
}

int Texture::GetHeight()
{
	return height;
}

void Texture::SetHeight(int value)
{
	height = value;
	renderRect.h = value;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

//If rendering whole image
Texture::Texture(std::string filename)
{
	graphics = Graphics::Instance();
	texture = AssetManager::Instance()->GetTexture(filename);
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	clipped = false;
	renderRect.w = width;
	renderRect.h = height;
}

//If rendering only a particular area of the image
Texture::Texture(std::string filename, int x, int y, int w, int h)
{
	graphics = Graphics::Instance();
	texture = AssetManager::Instance()->GetTexture(filename);
	clipped = true;
	width = w;
	height = h;
	renderRect.w = width;
	renderRect.h = height;

	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = width;
	clipRect.h = height;
}

//Destructor-----------------------------------------------------------------------------------------------------------------------------------------

Texture::~Texture()
{
	texture = NULL;
	graphics = NULL;
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

void Texture::Render()
{
	//Position of Texture is the centre of the image
	Vector2 pos = GetPos(world);
	renderRect.x = (int)(pos.x - width * 0.5f);
	renderRect.y = (int)(pos.y - height * 0.5f);

	//If clipped, draw clipped area not whole image
	graphics->DrawTexture(texture, clipped ? &clipRect : NULL, &renderRect);
}