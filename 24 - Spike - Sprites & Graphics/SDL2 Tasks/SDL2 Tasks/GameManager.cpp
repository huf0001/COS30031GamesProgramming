#include "GameManager.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

GameManager* GameManager::instance = NULL;

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

	std::srand(std::time(0));	//Initialise std::rand

	textures["background"] = new Texture("LyokoBinaryWall.png");
	textures["background"]->SetPos(Vector2(Graphics::GetScreenWidth() * 0.5f, Graphics::GetScreenHeight() * 0.5f));
	textures["background"]->SetWidth(Graphics::GetScreenWidth());
	textures["background"]->SetHeight(Graphics::GetScreenHeight());

	textures["sprite1"] = new Texture("SpriteSheet.png", 0, 0, 136, 190);
	textures["sprite1"]->SetPos(Vector2(100, 0));
	textures["sprite1"]->SetActive(false);
	textures["sprite2"] = new Texture("SpriteSheet.png", 136, 0, 136, 190);
	textures["sprite2"]->SetPos(Vector2(100, 0));
	textures["sprite2"]->SetActive(false);
	textures["sprite3"] = new Texture("SpriteSheet.png", 272, 0, 136, 190);
	textures["sprite3"]->SetPos(Vector2(100, 0));
	textures["sprite3"]->SetActive(false);
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
	
	for (auto pair : textures)
	{
		if (pair.second != NULL)
		{
			delete pair.second;
			pair.second = NULL;
		}
	}

	textures.clear();

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
							textures["background"]->SetActive(!textures["background"]->GetActive());
							break;

						//Images
						case SDL_SCANCODE_1:
							ToggleSprite(textures["sprite1"]);
							break;
						case SDL_SCANCODE_2:
							ToggleSprite(textures["sprite2"]);
							break;
						case SDL_SCANCODE_3:
							ToggleSprite(textures["sprite3"]);
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

						//Included these for testing width and height changes; now no longer necessary
						/*case SDL_SCANCODE_W:
							textures["background"]->SetHeight(textures["background"]->GetHeight() + 10);
							break;
						case SDL_SCANCODE_S:
							textures["background"]->SetHeight(textures["background"]->GetHeight() - 10);
							break;
						case SDL_SCANCODE_A:
							textures["background"]->SetWidth(textures["background"]->GetWidth() - 10);
							break;
						case SDL_SCANCODE_D:
							textures["background"]->SetWidth(textures["background"]->GetWidth() + 10);
							break;*/
					}

					break;
			}
		}

		if (timer->GetDeltaTime() >= 1.0f / FRAME_RATE)
		{
			graphics->ClearBackBuffer();

			for (std::pair<std::string, Texture*> pair : textures)
			{
				if (pair.second->GetActive())
				{
					pair.second->Render();
				}
			}

			graphics->Render();
			timer->Reset();
		}
	}

	Release();
}

void GameManager::ToggleSprite(Texture* sprite)
{
	sprite->SetActive(!sprite->GetActive());

	if (sprite->GetActive())
	{
		sprite->SetPos(Vector2(std::rand() % Graphics::GetScreenWidth(), std::rand() % Graphics::GetScreenHeight()));
	}
}

void GameManager::Release()
{
	delete instance;
	instance = NULL;
}