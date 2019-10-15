#include "AudioManager.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

AudioManager* AudioManager::instance = 0;

AudioManager* AudioManager::Instance()
{
	if (!instance)
	{
		instance = new AudioManager();
	}

	return instance;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

AudioManager::AudioManager()
{
	assetManager = AssetManager::Instance();

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
	{
		std::cout << "Mixer Initialisation Error: Error: " << Mix_GetError() << std::endl;
	}
}

//Destructor-----------------------------------------------------------------------------------------------------------------------------------------

AudioManager::~AudioManager()
{
	assetManager = NULL;
	Mix_Quit();
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

void AudioManager::PlayMusic(std::string filename, int loops) 
{
	currentlyPlaying = filename;
	Mix_PlayMusic(assetManager->GetMusic(filename), loops);
}

bool AudioManager::IsCurrentlyPlaying(std::string filename)
{
	return filename == currentlyPlaying;
}

void AudioManager::PauseMusic() 
{
	if (Mix_PlayingMusic() != 0)
	{
		Mix_PauseMusic();
	}
}

void AudioManager::ResumeMusic() 
{
	if (Mix_PausedMusic() != 0)
	{
		Mix_ResumeMusic();
	}
}

void AudioManager::PlaySFX(std::string filename, int loops, int channel) 
{
	Mix_PlayChannel(channel, assetManager->GetChunk(filename), loops);
}

void AudioManager::Release() 
{
	delete instance;
	instance = 0;
}
