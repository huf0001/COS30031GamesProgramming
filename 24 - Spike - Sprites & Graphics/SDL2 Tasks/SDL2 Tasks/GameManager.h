#include "pch.h"

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

class GameManager
{
private:
	//Private Fields
	static GameManager* instance;
	//SDL_Window* window;
	//SDL_Renderer* renderer;
	AssetManager* assetManager;
	AudioManager* audioManager;
	Graphics* graphics;
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
	static void Release();
};

#endif
