#include "pch.h"

#ifndef GRAPHICS_H
#define GRAPHICS_H

class Graphics
{
private:
	//Private Constants
	static const int SCREEN_WIDTH = 1200;
	static const int SCREEN_HEIGHT = 600;

	//Private Fields
	static Graphics* instance;
	SDL_Window* window;
	SDL_Surface* backBuffer;
	SDL_Renderer* renderer;
	static bool initialised;

	//Constructor
	Graphics();

	//Destructor
	~Graphics();

	//Private Methods

protected:
	//Protected Fields

	//Protected Methods

public:
	//Public Properties
	static Graphics* Instance();
	static bool GetInitialised();
	static int GetScreenWidth();
	static int GetScreenHeight();

	//Public Methods
	bool Init();
	SDL_Texture* LoadTexture(std::string path);
	void ClearBackBuffer();
	void DrawTexture(SDL_Texture* texture, SDL_Rect* clip = NULL, SDL_Rect* rend = NULL);
	void Render();
	static void Release();
};

#endif
