#include "pch.h"

#ifndef GRAPHICS_H
#define GRAPHICS_H

class Graphics
{
private:
	//Private Fields
	static Graphics* instance;
	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 600;
	static bool initialised;

	SDL_Window* window;
	SDL_Surface* backBuffer;

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
	void Render();
	static void Release();
};

#endif
