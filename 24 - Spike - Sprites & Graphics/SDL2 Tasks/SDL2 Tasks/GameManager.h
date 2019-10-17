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
	Timer* timer;
	SDL_Event events;
	bool running;

	Texture* background;
	bool displayBackground;

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
	static void Release();
};

#endif
