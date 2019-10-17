#include "Graphics.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

Graphics* Graphics::instance = 0;
bool Graphics::initialised = false;

Graphics* Graphics::Instance()
{
	if (!instance)
	{
		instance = new Graphics();
	}

	return instance;
}

bool Graphics::GetInitialised()
{
	return initialised;
}

int Graphics::GetScreenHeight()
{
	return SCREEN_HEIGHT;
}

int Graphics::GetScreenWidth()
{
	return SCREEN_WIDTH;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

Graphics::Graphics()
{
	backBuffer = NULL;
	initialised = Init();
}

//Destructor-----------------------------------------------------------------------------------------------------------------------------------------

Graphics::~Graphics()
{
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

bool Graphics::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL Initialisation Error: " << SDL_GetError() << std::endl;
		return false;
	}

	window = SDL_CreateWindow("SDL2 Tasks", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		std::cout << "Window Creation Error: " << SDL_GetError() << std::endl;
		return false;
	}

	backBuffer = SDL_GetWindowSurface(window);
	return true;
}

void Graphics::Render()
{
	SDL_UpdateWindowSurface(window);
}

void Graphics::Release()
{
	delete instance;
	instance = 0;
	initialised = false;
}