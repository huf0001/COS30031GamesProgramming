#include "GameManager.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

GameManager* GameManager::instance = 0;

GameManager* GameManager::Instance()
{
	if (!instance)
	{
		instance = new GameManager();
	}

	return instance;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

GameManager::GameManager()
{
				/*if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
				{
					std::cerr << "Error initialising SDL: " << SDL_GetError() << std::endl;
				}*/

				//renderer = SDL_CreateRenderer(window, -1, 0);

	running = true;
	assetManager = AssetManager::Instance();
	audioManager = AudioManager::Instance();
	graphics = Graphics::Instance();
	timer = Timer::Instance();

	if (!Graphics::GetInitialised())
	{
		running = false;
	}
}

//Destructor-----------------------------------------------------------------------------------------------------------------------------------------

GameManager::~GameManager()
{
	AssetManager::Release();
	assetManager = 0;
	AudioManager::Release();
	audioManager = 0;
	Graphics::Release();
	graphics = 0;
	Timer::Release();
	timer = 0;
				//SDL_DestroyRenderer(renderer);
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

void GameManager::Run()
{
	while (running)
	{
		timer->Update();
				//SDL_Event* event;

		while (SDL_PollEvent(&events) != 0)
		{
			switch (events.type)
			{
				case SDL_QUIT:
					running = false;
					break;
				case SDL_KEYDOWN:
					switch (events.key.keysym.scancode)
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

		if (timer->GetDeltaTime() >= 1.0f / FRAME_RATE)
		{
			//std::cout << "DeltaTime: " << timer->GetDeltaTime() << std::endl;
			graphics->Render();
			timer->Reset();
		}
				//SDL_RenderClear(renderer);
					//SDL_RenderCopy(renderer, text, NULL, &dest);
				//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				//SDL_RenderPresent(renderer);
		//SDL_Delay(1000 / 60);
	}

	Release();
}

void GameManager::Release()
{
	delete instance;
	instance = 0;
}