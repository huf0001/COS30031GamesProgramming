#include "pch.h"

int main(int args, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cerr << "error initialising SDL: " << SDL_GetError() << "\n" << std::endl;
	}

	SDL_Window* window = SDL_CreateWindow("SDL2 Tasks", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	AudioManager* audioManager = AudioManager::Instance();
	bool running = true;

	while (running)
	{
		SDL_Event event;

		//Events management
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					running = false;
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.scancode)
					{
						//Quit
						case SDL_SCANCODE_ESCAPE:
							running = false;
							break;
						
						//Music
						case SDL_SCANCODE_9:
							audioManager->HandleMusic("FogOfWar1.mp3");
							break;
						case SDL_SCANCODE_0:
							audioManager->HandleMusic("Var_3.mp3");
							break;	
						
						//SFX
						case SDL_SCANCODE_6:
							audioManager->PlaySFX("BuildingDestroyed.wav", 0, 1);
							break;
						case SDL_SCANCODE_7:
							audioManager->PlaySFX("MortarHit.wav", 0, 2);
							break;
						case SDL_SCANCODE_8:
							audioManager->PlaySFX("MortarLaunch.wav", 0, 3);
							break;										
					}

					break;
			}
		}
		
		SDL_RenderClear(renderer);
		//SDL_RenderCopy(renderer, text, NULL, &dest);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderPresent(renderer);
		SDL_Delay(1000/60);
	}

	audioManager->Release();
	audioManager = 0;
	AssetManager::Release();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	return 0;
}