#include "AssetManager.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

AssetManager* AssetManager::instance = NULL;

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
	for (auto texture : textures)
	{
		if (texture.second != NULL)
		{
			SDL_DestroyTexture(texture.second);
		}
	}

	textures.clear();
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

//Load a .png file
SDL_Texture* AssetManager::GetTexture(std::string filename)
{
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Assets/Images/" + filename);

	if (textures[fullPath] == nullptr)
	{
		textures[fullPath] = Graphics::Instance()->LoadTexture(fullPath);
	}

	return textures[fullPath];
}

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
	instance = NULL;
}