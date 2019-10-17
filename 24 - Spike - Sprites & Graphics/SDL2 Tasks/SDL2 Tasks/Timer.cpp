#include "Timer.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

Timer* Timer::instance = NULL;

Timer* Timer::Instance()
{
	if (!instance)
	{
		instance = new Timer();
	}

	return instance;
}

float Timer::GetDeltaTime()
{
	return deltaTime;
}

float Timer::GetTimeScale()
{
	return timeScale;
}

void Timer::SetTimeScale(float value)
{
	timeScale = value;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

Timer::Timer()
{
	Reset();
	timeScale = 1.0f;
}

//Destructor-----------------------------------------------------------------------------------------------------------------------------------------

Timer::~Timer()
{

}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

void Timer::Update()
{
	elapsedTicks = SDL_GetTicks() - startTicks;
	deltaTime = elapsedTicks * 0.001f;
}

void Timer::Reset()
{
	startTicks = SDL_GetTicks();
	elapsedTicks = 0;
	deltaTime = 0.0f;
}

void Timer::Release()
{
	delete instance;
	instance = NULL;
}