#include "pch.h"

#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

class AssetManager
{
private:
	//Private Fields
	static AssetManager* instance;

	std::map<std::string, Mix_Music*> music;
	std::map<std::string, Mix_Chunk*> sfx;

	//Constructor
	AssetManager();
	~AssetManager();

	//Private Methods

protected:
	//Protected Fields

	//Protected Methods

public:
	//Public Properties
	static AssetManager* Instance();

	//Public Methods
	Mix_Music* GetMusic(std::string filename);
	Mix_Chunk* GetChunk(std::string filename);

	static void Release();
};

#endif
