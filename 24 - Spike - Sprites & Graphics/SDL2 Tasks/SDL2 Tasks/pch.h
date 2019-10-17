#ifndef PCH_H
#define PCH_H

//Basic classes / libraries of C++ in the standard library-------------------------------------------------------------------------------------------

//Basic data types
#include <string>

//Data Structures
#include <map>

//Maths
#include <math.h>

//Output to terminal
#include <iostream>
#include <stdio.h>

//SDL library----------------------------------------------------------------------------------------------------------------------------------------

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

//Classes unique to this project---------------------------------------------------------------------------------------------------------------------

#include "MathHelper.h"
#include "AssetManager.h"
#include "AudioManager.h"
#include "GameEntity.h"
#include "Graphics.h"
#include "Timer.h"
#include "GameManager.h"

#endif