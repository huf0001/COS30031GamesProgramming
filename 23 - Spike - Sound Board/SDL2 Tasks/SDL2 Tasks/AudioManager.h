#include "pch.h"

#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

class AudioManager
{
private:
	//Private Fields
	static AudioManager* instance;
	AssetManager* assetManager;
	std::string currentlyPlaying;

	//Constructor
	AudioManager();
	~AudioManager();

	//Private Methods
	
protected:
	//Protected Fields

	//Protected Methods

public:
	//Public Properties
	static AudioManager* Instance();

	//Public Methods
	void PlayMusic(std::string filename, int loops = -1);	//-1: by default loops infinitely; if passed > -1, it will play once, then play again the specified no. of times; presumably plays on channel 0?
	bool IsCurrentlyPlaying(std::string filename);	
	void PauseMusic();
	//void StopMusic();
	void ResumeMusic();
	void PlaySFX(std::string filename, int loops = 0, int channel = 0);		//plays once then plays again the specified no. of times; plays on the specified channel
	static void Release();
};

#endif