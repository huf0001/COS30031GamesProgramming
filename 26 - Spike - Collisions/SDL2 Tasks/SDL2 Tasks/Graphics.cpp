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


SDL_Color Graphics::GetColour(std::string colour)
{
	if (colour == "red")
	{
		return GetColour(255, 0, 0);
	}

	if (colour == "green")
	{
		return GetColour(0, 255, 0);
	}

	if (colour == "blue")
	{
		return GetColour(0, 0, 255);
	}

	if (colour == "white")
	{
		return GetColour(255, 255, 255);
	}

	return GetColour(0, 0, 0);
}

SDL_Color Graphics::GetColour(int r, int g, int b, int a)
{
	SDL_Color colour = SDL_Color();

	colour.r = r;
	colour.g = g;
	colour.b = b;
	colour.a = a;

	return colour;
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
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
}

void Graphics::DrawCircle(SDL_Color colour, bool outlined, float radius, Vector2 pos)
{
	//Fill circle
	SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
		
	for (int w = 0; w < radius * 2; w++)
	{
		for (int h = 0; h < radius * 2; h++)
		{
			int dx = radius - w; // horizontal offset
			int dy = radius - h; // vertical offset

			if ((dx * dx + dy * dy) <= (radius * radius))
			{
				SDL_RenderDrawPoint(renderer, pos.x + dx, pos.y + dy);
			}
		}
	}

	//Draw outline
	if (outlined)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		for (int w = 0; w < radius * 2; w++)
		{
			for (int h = 0; h < radius * 2; h++)
			{
				int dx = radius - w; // horizontal offset
				int dy = radius - h; // vertical offset
				float dist = sqrt(dx * dx + dy * dy);

				if (radius - dist >= 0 && radius - dist < 1)
				{
					SDL_RenderDrawPoint(renderer, pos.x + dx, pos.y + dy);
				}
			}
		}
	}
}

void Graphics::DrawRectangle(SDL_Color colour, bool outlined, SDL_Rect* rect)
{
	SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
	SDL_RenderFillRect(renderer, rect);

	if (outlined)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderDrawRect(renderer, rect);
	}
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