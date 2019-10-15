#ifndef PCH_H
#define PCH_H

//Basic classes / libraries of C++ in the standard library-------------------------------------------------------------------------------------------

//Basic data types
#include <string>

//Data Structures
#include <map>

//Output to terminal
#include <iostream>
#include <stdio.h>

//SDL library----------------------------------------------------------------------------------------------------------------------------------------

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

//Classes unique to this project---------------------------------------------------------------------------------------------------------------------

#include "AssetManager.h"
#include "AudioManager.h"
#include "Graphics.h"
#include "GameManager.h"

#endif