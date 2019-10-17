#include "pch.h"

#ifndef TIMER_H
#define TIMER_H

class Timer
{
private:
	//Private Fields
	static Timer* instance;

	unsigned int startTicks;
	unsigned int elapsedTicks;
	float deltaTime;
	float timeScale;

	//Constructor
	Timer();

	//Destructor
	~Timer();

	//Private Methods

protected:
	//Protected Fields

	//Protected Methods

public:
	//Public Properties
	static Timer* Instance();
	float GetDeltaTime();
	float GetTimeScale();
	void SetTimeScale(float t);

	//Public Methods
	void Update();
	void Reset();
	static void Release();

};

#endif
