#include "pch.h"

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

class GameManager
{
private:
	//Private Constants
	const int FRAME_RATE = 60;

	//Private Fields
	static GameManager* instance;
	AssetManager* assetManager;
	AudioManager* audioManager;
	Graphics* graphics;
	std::map<std::string, Texture*> textures;
	Timer* timer;
	SDL_Event events;
	bool running;


	//Constructor
	GameManager();

	//Destructor
	~GameManager();

	//Private Methods

protected:
	//Protected Fields

	//Protected Methods

public:
	//Public Properties
	static GameManager* Instance();

	//Public Methods
	void Run();
	void ToggleSprite(Texture* sprite);
	static void Release();
};

#endif
