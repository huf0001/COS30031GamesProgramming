#include "AssetManager.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

AssetManager* AssetManager::instance = 0;

AssetManager* AssetManager::Instance()
{
	if (!instance)
	{
		instance = new AssetManager();
	}

	return instance;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

AssetManager::AssetManager()
{

}

//Destructor-----------------------------------------------------------------------------------------------------------------------------------------

AssetManager::~AssetManager()
{

}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

//Load a .mp3 music file
Mix_Music* AssetManager::GetMusic(std::string filename)
{
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Assets/Audio/" + filename);

	if (music[fullPath] == nullptr)
	{
		music[fullPath] = Mix_LoadMUS(fullPath.c_str());
	
		if (music[fullPath] == NULL)
		{
			std::cout << "Music Loading Error: " << filename.c_str() << " Error " << Mix_GetError() << std::endl;
		}
	}

	return music[fullPath];
}

//Load a .wav audio file
Mix_Chunk* AssetManager::GetChunk(std::string filename)
{
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Assets/Audio/" + filename);

	if (sfx[fullPath] == nullptr)
	{
		sfx[fullPath] = Mix_LoadWAV(fullPath.c_str());

		if (sfx[fullPath] == NULL)
		{
			std::cout << "Music Loading Error: File: " << filename.c_str() << "; Error: " << Mix_GetError() << ";" << std::endl;
		}
	}

	return sfx[fullPath];
}

void AssetManager::Release()
{
	delete instance;
	instance = 0;
}