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

//Time-related classes
#include <chrono>
#include <ctime>

//Include files from this project--------------------------------------------------------------------------------------------------------------------

//String manager
#include "StringManager.h"

//Messaging System
#include "Message.h"
#include "Notifiable.h"							
#include "MessageManager.h"	

//Components
#include "Component.h"	
#include "Button.h"
#include "Container.h"				
#include "Description.h"
#include "Flammable.h"
#include "Landmine.h"
#include "Lock.h"					
#include "Movable.h"	
#include "UnlockCommands.h"			

//GameObjects
#include "GameObject.h"							
#include "Item.h"						
#include "Player.h"					
#include "Path.h"					
#include "Location.h"				

//World
#include "ComponentFactory.h"
#include "World.h"						

//Commands
#include "Command.h"
#include "CommandManager.h"					
#include "CommandAlias.h"		
#include "CommandDebug.h"		
#include "CommandLook.h"				
#include "CommandOpen.h"				
#include "CommandMove.h"							
#include "CommandTake.h"							
#include "CommandPut.h"							
#include "CommandDrop.h"
#include "CommandUse.h"
#include "CommandHelp.h"			
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
