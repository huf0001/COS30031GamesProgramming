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
	running = true;
	assetManager = AssetManager::Instance();
	audioManager = AudioManager::Instance();
	graphics = Graphics::Instance();
	timer = Timer::Instance();

	if (!Graphics::GetInitialised())
	{
		running = false;
	}

	std::string path = SDL_GetBasePath();
	path.append("Assets/Images/LyokoBinaryWall.png");
	background = new Texture(path);
	displayBackground = true;
}

//Destructor-----------------------------------------------------------------------------------------------------------------------------------------

GameManager::~GameManager()
{
	AssetManager::Release();
	assetManager = NULL;
	AudioManager::Release();
	audioManager = NULL;
	Graphics::Release();
	graphics = NULL;
	delete background;
	background = NULL;
	Timer::Release();
	timer = NULL;
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

void GameManager::Run()
{
	while (running)
	{
		timer->Update();

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

						//Background
						case SDL_SCANCODE_0:
							displayBackground = !displayBackground;
							break;

						//Images
						case SDL_SCANCODE_1:
							displayBackground = !displayBackground;
							break;
						case SDL_SCANCODE_2:
							displayBackground = !displayBackground;
							break;
						case SDL_SCANCODE_3:
							displayBackground = !displayBackground;
							break;

						//Music
						case SDL_SCANCODE_8:
							audioManager->HandleMusic("FogOfWar1.mp3");
							break;
						case SDL_SCANCODE_9:
							audioManager->HandleMusic("Var_3.mp3");
							break;

						//SFX
						case SDL_SCANCODE_5:
							audioManager->PlaySFX("BuildingDestroyed.wav", 0, 1);
							break;
						case SDL_SCANCODE_6:
							audioManager->PlaySFX("MortarHit.wav", 0, 2);
							break;
						case SDL_SCANCODE_7:
							audioManager->PlaySFX("MortarLaunch.wav", 0, 3);
							break;
					}

					break;
			}
		}

		if (timer->GetDeltaTime() >= 1.0f / FRAME_RATE)
		{
			graphics->ClearBackBuffer();

			if (displayBackground)
			{
				background->Render();
			}

			graphics->Render();
			timer->Reset();
		}
	}

	Release();
}

void GameManager::Release()
{
	delete instance;
	instance = 0;
}