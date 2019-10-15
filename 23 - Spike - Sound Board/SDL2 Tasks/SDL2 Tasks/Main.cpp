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
				case SDL_SCANCODE_ESCAPE:
					running = false;
					break;
				case SDL_SCANCODE_1:
					//Toggle Serra Guardian at random position
					break;
				case SDL_SCANCODE_2:
					//Toggle Tezzeret at random position
					break;
				case SDL_SCANCODE_3:
					//Toggl Murder at random position
					break;
				case SDL_SCANCODE_6:
					audioManager->PlaySFX("Audio/BuildingDestroyed.wav", 0, 1);
					break;
				case SDL_SCANCODE_7:
					audioManager->PlaySFX("Audio/MortarHit.wav", 0, 2);
					break;
				case SDL_SCANCODE_8:
					audioManager->PlaySFX("Audio/MortarLaunch.wav", 0, 3);
					break;
				case SDL_SCANCODE_9:
					if (!audioManager->IsCurrentlyPlaying("Audio/FogOfWar1.mp3"))
					{
						audioManager->PlayMusic("Audio/FogOfWar1.mp3");
					}
					else if (Mix_PausedMusic())
					{
						audioManager->ResumeMusic();
					}
					else if (Mix_PlayingMusic())
					{
						audioManager->PauseMusic();
					}
					else
					{
						audioManager->PlayMusic("Audio/FogOfWar1.mp3");
					}

					break;
				case SDL_SCANCODE_0:
					if (!audioManager->IsCurrentlyPlaying("Audio/Var_3.mp3"))
					{
						audioManager->PlayMusic("Audio/Var_3.mp3");
					}
					else if (Mix_PausedMusic())
					{
						audioManager->ResumeMusic();
					}
					else if (Mix_PlayingMusic())
					{
						audioManager->PauseMusic();
					}
					else
					{
						audioManager->PlayMusic("Audio/Var_3.mp3");
					}
					break;
				}

				break;
			}
		}

		SDL_RenderClear(renderer);
		//SDL_RenderCopy(renderer, text, NULL, &dest);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderPresent(renderer);
		SDL_Delay(1000 / 60);
	}

	audioManager->Release();
	audioManager = 0;
	AssetManager::Release();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	return 0;
}