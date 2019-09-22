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
#include "Movable.h"		//Not Implemented	Wait until everything else is implemented before adding

//GameObjects
#include "GameObject.h"
#include "Item.h"						//Updated
#include "Player.h"						//Update
#include "Path.h"						//Updated
#include "Location.h"					//Updated

//World
#include "World.h"			//Update

//Commands
#include "Command.h"
#include "CommandManager.h"
#include "CommandAlias.h"
#include "CommandDebug.h"	//Update
#include "CommandLook.h"	//Update
//#include "CommandOpen.h"	//Not Implemented	Wait until everything else is implemented before adding
#include "CommandMove.h"	//Update
#include "CommandTake.h"	//Update
#include "CommandPut.h"		//Update
#include "CommandDrop.h"	//Update
#include "CommandHelp.h"	//Update
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
