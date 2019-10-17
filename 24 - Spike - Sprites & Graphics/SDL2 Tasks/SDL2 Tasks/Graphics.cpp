#include "Graphics.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

Graphics* Graphics::instance = NULL;
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
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	IMG_Quit();
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

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL)
	{
		std::cout << "Renderer Creation Error: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	int flags = IMG_INIT_PNG;
	
	if (!(IMG_Init(flags) & flags))
	{
		std::cout << "Image Initialisation Error: " << IMG_GetError() << std::endl;
		return false;
	}

	backBuffer = SDL_GetWindowSurface(window);
	return true;
}


SDL_Texture* Graphics::LoadTexture(std::string path)
{
	SDL_Texture* texture = NULL;
	SDL_Surface* surface = IMG_Load(path.c_str());

	if (surface == NULL)
	{
		std::cout << "Image Load Error: Path(" << path << ") - Error(" << IMG_GetError() << ")" << std::endl;
	}

	texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (texture == NULL)
	{
		std::cout << "Create Texture Error: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_FreeSurface(surface);
	return texture;
}

void Graphics::ClearBackBuffer()
{
	SDL_RenderClear(renderer);
}

void Graphics::DrawTexture(SDL_Texture* texture, SDL_Rect* clip, SDL_Rect* rend)
{
	SDL_RenderCopy(renderer, texture, clip , rend);
}

void Graphics::Render()
{
	SDL_RenderPresent(renderer);
}

void Graphics::Release()
{
	delete instance;
	instance = NULL;
	initialised = false;
}