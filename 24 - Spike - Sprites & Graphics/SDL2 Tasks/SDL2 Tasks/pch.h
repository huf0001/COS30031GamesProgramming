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

//Utility Stuff
#include "MathHelper.h"
#include "Timer.h"

//Media Managers
#include "AssetManager.h"
#include "AudioManager.h"
#include "Graphics.h"

//Game Entities
#include "GameEntity.h"
#include "Texture.h"

//Game Manager
#include "GameManager.h"

#endif