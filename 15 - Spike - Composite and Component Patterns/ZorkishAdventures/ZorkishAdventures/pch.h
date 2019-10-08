// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#ifndef PCH_H
#define PCH_H

//Include standard library classes / external libraries----------------------------------------------------------------------------------------------

//Streams
#include <fstream>
#include <iostream>
#include <sstream>

//Basic data types
#include <string>

//Data structures
#include <array>
#include <map>
#include <vector>

//Include files from this project--------------------------------------------------------------------------------------------------------------------

//String manager
#include "StringManager.h"

//Components
#include "Component.h"					//Implemented
#include "Container.h"					//Updated
#include "Description.h"				//Implemented
#include "Lock.h"			//Not Implemented	Wait until everything else is implemented before adding
#include "Movable.h"					//Implemented

//GameObjects
#include "GameObject.h"
#include "Item.h"						//Updated
#include "Player.h"						//Updated
#include "Path.h"						//Updated
#include "Location.h"					//Updated

//World
#include "ComponentFactory.h"
#include "World.h"						//Updated

//Commands
#include "Command.h"
#include "CommandManager.h"
#include "CommandAlias.h"
#include "CommandDebug.h"				//Updated
#include "CommandLook.h"				//Updated
#include "CommandOpen.h"	//Not Implemented	Wait until everything else is implemented before adding
#include "CommandMove.h"				//Updated
#include "CommandTake.h"				//Updated
#include "CommandPut.h"					//Updated
#include "CommandDrop.h"				//Updated
#include "CommandHelp.h"				//Updated
#include "CommandHiScore.h"
#include "CommandQuit.h"

//Stages
#include "Stage.h"
#include "StageManager.h"
#include "StageAbout.h"
#include "StageGameplay.h"
#include "StageHallOfFame.h"
#include "StageHelp.h"
#include "StageMainMenu.h"
#include "StageNewHighScore.h"
#include "StageSelectAdventure.h"

//Game
#include "Game.h"

#endif //PCH_H
