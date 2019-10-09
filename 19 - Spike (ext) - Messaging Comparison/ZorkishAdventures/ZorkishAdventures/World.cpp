#include "pch.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

Location* World::GetCurrentLocation()
{
	return currentLocation;
}

void World::SetCurrentLocation(Location* value)
{
	currentLocation = value;
}

bool World::GetLoadedSuccessfully()
{
	return loadedSuccessfully;
}

std::string World::GetName()
{
	return name;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

World::World(std::string filename)
{
	locations = std::map<std::string, Location*>();
	std::map<std::string, std::string> directionAliases = std::map<std::string, std::string>();

	loadedSuccessfully = true;
	name = "";
	currentLocation = nullptr;

	//Read available worlds from file
	std::ifstream ifs(filename);

	if (ifs.is_open())
	{
		std::string line;
		std::vector<std::string> splitLine;
		std::map<std::string, Container*> containers = std::map<std::string, Container*>();
		std::map<std::string, GameObject*> gameObjects = std::map<std::string, GameObject*>();
		int lineCount = 0;

		std::string worldNameFormat = "\tFormat: \"W:World Name\".\n";
		std::string startConfigurationFormat = "\tFormat: \"S:starting_location_id:command_id_1,command_id_2, . . .\".\n";
		std::string locationFormat = "\tFormat: \"L:location_id_:Location Name:location description\".\n";
		std::string pathFormat = "\tFormat: \"P:path_id:Path Name:location_from_id:direction:location_to_id:path description\". If Path ID and name are blank, they will be constructed from location_from_id and location_to_id.\n\n";
		std::string aliasFormat = "\tFormat: \"A:direction name:direction alias\".\n\n";
		std::string itemFormat = "\tFormat: \"I:container_id:item_id:Item Name:item description:component_id_1,component_id_2, . . .\".\n\n";
		std::string generalComponentFormat = "\tGeneral Format: \"C:component_type:game_object_id[:component specific parameters]\".\n\n";
		std::string containerComponentFormat = "\tContainer Format: \"C:container:game_object_id:is_open?:always_open?\".\n\n";
		std::string descriptionComponentFormat = "\tDescription Format: \"C:description:game_object_id:description of game object\".\n\n";
		std::string lockComponentFormat = "\tLock Format: \"C:lock:game_object_id:is_locked?:unlockable_with_item_id_1,unlockable_with_item_id_2, . . .\". If not unlockable, specify \"none\".\n\n";
		std::string movableComponentFormat = "\tMovable Format: \"C:movable:game_object_id\".\n\n";
		std::string unlockCommandsComponentFormat = "\tUnlock Commands Format: \"C:unlock_commands:game_object_id:command_id_1,command_id_2, . . .\".\n\n";

		while (std::getline(ifs, line))
		{
			lineCount++;

			//Check for blank lines and comments
			if (line.length() == 0 || line[0] == '#')
			{
				continue;
			}

			splitLine = StringManager::Instance()->StringToVector(line, ':');

			//Check prefixes
			if (splitLine[0] == "W")
			{		
				//Check Formatting
				if (splitLine.size() != 2)
				{
					std::cout << "Error, '" << filename << "', line " << lineCount << ": Wrong number of values for loading world name. Values required (including prefix 'W'): 2. Values given: " << splitLine.size() << ".\n";
					std::cout << worldNameFormat;
					loadedSuccessfully = false;
				}
				else if (splitLine[1].length() == 0)
				{
					std::cout << "Error, '" << filename << "', line " << lineCount << ": You must specify the world name.\n";
					std::cout << worldNameFormat;
					loadedSuccessfully = false;
				}
				else
				{
					name = splitLine[1];
				}
			}
			else if (splitLine[0] == "S")
			{
				//Check Formatting
				if (splitLine.size() != 3)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": Wrong number of values for loading starting location. Values required (including prefix \"S\"): 2. Values given: " << splitLine.size() << ".\n";
					std::cout << startConfigurationFormat;
					loadedSuccessfully = false;
				}
				else if (splitLine[1].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the id of the starting location.\n";
					std::cout << startConfigurationFormat;
					loadedSuccessfully = false;
				}
				else if (splitLine[2].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the ids of the commands to be made available at the start of the game.\n";
					std::cout << startConfigurationFormat;
					loadedSuccessfully = false;
				}
				else if (!locations.count(splitLine[1]))
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": The starting_location_id must be the id of a location that has already been created. World.locations doesn't contain a location with id \"" + splitLine[1] + "\".\n";
					std::cout << startConfigurationFormat;
					loadedSuccessfully = false;
				}
				else
				{
					currentLocation = locations[splitLine[1]];
					std::vector<std::string> commands = StringManager::Instance()->StringToVector(splitLine[2], ',');
					CommandManager::Instance()->UnlockCommands(commands);

					//Verifies each command was unlocked
					for (std::string command : commands)
					{
						if (command != "all" && !CommandManager::Instance()->HasCommand(command))
						{
							std::cout << "Error, \"" << filename << "\", line " << lineCount << ": No command with id \"" + command + "\" exists to be unlocked.\n";
							loadedSuccessfully = false;
						}
					}
				}
			}
			else if (splitLine[0] == "L")
			{
				//Check Formatting
				if (splitLine.size() != 4)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": Wrong number of values for loading location. Values required (including prefix \"L\"): 4. Values given: " << splitLine.size() << ".\n";
					std::cout << locationFormat;
					loadedSuccessfully = false;
				}
				else if (splitLine[1].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the location's id.\n";
					std::cout << locationFormat;
					loadedSuccessfully = false;
				}
				else if (splitLine[2].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the location's name.\n";
					std::cout << locationFormat;
					loadedSuccessfully = false;
				}
				else if (splitLine[3].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the location's description.\n";
					std::cout << locationFormat;
					loadedSuccessfully = false;
				}
				else
				{
					locations[splitLine[1]] = new Location(splitLine[1], splitLine[2], splitLine[3]);
					containers[splitLine[1]] = (Container*)locations[splitLine[1]]->GetComponent("container");
					gameObjects[splitLine[1]] = (GameObject*)locations[splitLine[1]];
					MessageManager::Instance()->Subscribe(locations[splitLine[1]]);
				}
			}
			else if (splitLine[0] == "P")
			{
				//Check Formatting
				if (splitLine.size() != 7)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": Wrong number of values for loading path between locations. Values required (including prefix \"P\"): 7. Values given: " << splitLine.size() << ".\n";
					std::cout << pathFormat;
					loadedSuccessfully = false;
				}
				else if (splitLine[3].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the id of the location the path leads away from.\n";
					std::cout << pathFormat;
					loadedSuccessfully = false;
				}
				else if (splitLine[4].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the direction the path leads in.\n";
					std::cout << pathFormat;
					loadedSuccessfully = false;
				}
				else if (splitLine[5].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the id of the location the path leads towards.\n";
					std::cout << pathFormat;
					loadedSuccessfully = false;
				}
				else if (splitLine[6].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the description of the path.\n";
					std::cout << pathFormat;
					loadedSuccessfully = false;
				}
				//Check endpoints of path exist
				else if (!locations.count(splitLine[3]))
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": The path's location_from_id must be the id of a location that has already been created. World.locations doesn't contain a location with id \"" + splitLine[1] + "\".\n";
					std::cout << pathFormat;
					loadedSuccessfully = false;
				}
				else if (!locations.count(splitLine[5]))
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": The path's location_to_id must be the id of a location that has already been created. World.locations doesn't contain a location with id \"" + splitLine[1] + "\".\n";
					std::cout << pathFormat;
					loadedSuccessfully = false;
				}
				//Create the path
				else
				{
					if (splitLine[1].length() == 0)
					{
						splitLine[1] = splitLine[3] + "_to_" + splitLine[5];
					}

					if (splitLine[2].length() == 0)
					{
						splitLine[2] = splitLine[3] + " to " + splitLine[5];
					}

					Path* path = new Path(splitLine[1], splitLine[2], splitLine[5], splitLine[6]);
					locations[splitLine[3]]->AddPath(splitLine[4], path);    //Automatically subscribes the path to MessageManager appropriately
					gameObjects[path->GetID()] = (GameObject*)path;
					//MessageManager::Instance()->Subscribe(splitLine[3], path);
				}
			}
			else if (splitLine[0] == "A")
			{
				//Check Formatting
				if (splitLine.size() != 3)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": Wrong number of values for loading direction alias. Values required (including prefix \"A\"): 5. Values given: " << splitLine.size() << ".\n";
					std::cout << aliasFormat;
					loadedSuccessfully = false;
				}
				else if (splitLine[1].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the name of the direction to be given an alias.\n";
					std::cout << aliasFormat;
					loadedSuccessfully = false;
				}
				else if (splitLine[2].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the alias of the direction.\n";
					std::cout << aliasFormat;
					loadedSuccessfully = false;
				}
				//Check the given alias isn't already assigned to a direction
				else if (directionAliases.count(splitLine[2]))
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": A given alias can only be given to a single direction. A direction already has the alias \"" + splitLine[2] + "\".\n";
					std::cout << aliasFormat;
					loadedSuccessfully = false;
				}
				//Create the alias
				else
				{
					directionAliases[splitLine[2]] = splitLine[1];
				}
			}			
			else if (splitLine[0] == "I")
			{	
				//Check Formatting
				if (splitLine.size() != 6)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": Wrong number of values for loading item. Values required (including prefix \"I\"): 5. Values given: " << splitLine.size() << ".\n";
					std::cout << itemFormat;
					loadedSuccessfully = false;
				}
				else if (splitLine[1].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the id of the container (location or container item) that holds the item.\n";
					std::cout << itemFormat;
					loadedSuccessfully = false;
				}
				else if (splitLine[2].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the item's id.\n";
					std::cout << itemFormat;
					loadedSuccessfully = false;
				}
				else if (splitLine[3].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the item's name.\n";
					std::cout << itemFormat;
					loadedSuccessfully = false;
				}
				else if (splitLine[4].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the item's description.\n";
					std::cout << itemFormat;
					loadedSuccessfully = false;
				}

				else if (splitLine[5].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the item's components, or \"none\" if it has none.\n";
					std::cout << itemFormat;
					loadedSuccessfully = false;
				}
				//Check the item's container exists
				else if (!containers.count(splitLine[1]))
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": The item's container_id must be the id of a container (i.e. location or container item) that has already been created. Map \"containers\" in World.World() does not include container \"" + splitLine[1] + "\".\n";
					std::cout << itemFormat;
					loadedSuccessfully = false;
				}
				//Create the item
				else
				{	
					Item* item = new Item(splitLine[2], splitLine[3], splitLine[4]);
					containers[splitLine[1]]->AddItem(item);		//AddItem() and RemoveItem() now automatically subscribe and unsubscribe items from MessageManager so they're listed under the correct container
					gameObjects[item->GetID()] = (GameObject*)item;
					//MessageManager::Instance()->Subscribe(splitLine[1], item);

					if (splitLine[5] != "none")
					{
						std::vector<std::string> componentIds = StringManager::Instance()->StringToVector(splitLine[5], ',');

						for (std::string componentId : componentIds)
						{
							Component* component = ComponentFactory::Instance()->CreateComponent(componentId, (GameObject*)item);

							if (component == nullptr)
							{
								std::cout << "Error, \"" << filename << "\", line " << lineCount << ": Invalid component ID \"" + componentId + "\". ComponentFactory cannot produce Components with that component ID.\n";
								std::cout << itemFormat;
								loadedSuccessfully = false;
							}
							else
							{
								item->AddComponent(component);

								if (componentId == "container")
								{
									containers[item->GetID()] = (Container*)component;
								}
							}
						}
					}				
				}
			}
			else if (splitLine[0] == "C")
			{				
				if (splitLine.size() < 3)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": Wrong number of values for loading components. Values required (including prefix \"C\"): 3 or more. Values given: " << splitLine.size() << ".\n";
					std::cout << generalComponentFormat;
					loadedSuccessfully = false;
				}
				else if (splitLine[1].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the type of component to be created.\n";
					std::cout << generalComponentFormat;
					loadedSuccessfully = false;
				}
				else if (splitLine[2].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the id of the game object the component will be assigned to.\n";
					std::cout << generalComponentFormat;
					loadedSuccessfully = false;
				}
				else if (!gameObjects.count(splitLine[2]))
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": The component's game_object_id must be the id of a game object that has already been created. Map \"gameObjects\" in World.World() does not include game object \"" + splitLine[2] + "\".\n";
					std::cout << generalComponentFormat;
					loadedSuccessfully = false;
				}
				else if (splitLine[1] == "container")
				{		
					if (splitLine.size() != 5)
					{
						std::cout << "Error, \"" << filename << "\", line " << lineCount << ": Wrong number of values for loading container component. Values required (including prefix \"C\"): 5. Values given: " << splitLine.size() << ".\n";
						std::cout << generalComponentFormat;
						std::cout << containerComponentFormat;
						loadedSuccessfully = false;
					}
					else if (splitLine[3] != "Yes" && splitLine[3] != "No")
					{
						std::cout << "Error, \"" << filename << "\", line " << lineCount << ": is_open? must be \"Yes\" or \"No\".\n";
						std::cout << generalComponentFormat;
						std::cout << containerComponentFormat;
						loadedSuccessfully = false;
					}
					else if (splitLine[4] != "Yes" && splitLine[4] != "No")
					{
						std::cout << "Error, \"" << filename << "\", line " << lineCount << ": always_open? must be \"Yes\" or \"No\".\n";
						std::cout << generalComponentFormat;
						std::cout << containerComponentFormat;
						loadedSuccessfully = false;
					}
					else
					{
						gameObjects[splitLine[2]]->AddComponent((Component*) new Container(gameObjects[splitLine[2]], splitLine[3] == "Yes", splitLine[4] == "Yes"));
						containers[splitLine[2]] = (Container*)gameObjects[splitLine[2]]->GetComponent("container");
					}					
				}
				else if (splitLine[1] == "description")
				{
					if (splitLine.size() != 4)
					{
						std::cout << "Error, \"" << filename << "\", line " << lineCount << ": Wrong number of values for loading container component. Values required (including prefix \"C\"): 5. Values given: " << splitLine.size() << ".\n";
						std::cout << generalComponentFormat;
						std::cout << descriptionComponentFormat;
						loadedSuccessfully = false;
					}
					else if (splitLine[3].length() == 0)
					{
						std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the description to be assigned to the description component.\n";
						std::cout << generalComponentFormat;
						std::cout << descriptionComponentFormat;
						loadedSuccessfully = false;
					}
					else
					{
						gameObjects[splitLine[2]]->AddComponent((Component*) new Description(gameObjects[splitLine[2]], splitLine[3]));
					}
				}
				else if (splitLine[1] == "lock")
				{
					if (splitLine[3] != "Yes" && splitLine[3] != "No")
					{
						std::cout << "Error, \"" << filename << "\", line " << lineCount << ": is_locked? must be \"Yes\" or \"No\".\n";
						std::cout << generalComponentFormat;
						std::cout << lockComponentFormat;
						loadedSuccessfully = false;
					}
					else if (splitLine[4].size() == 0)
					{
						std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must list the items that the lock can be unlocked with, or \"none\" if not unlockable.\n";
						std::cout << generalComponentFormat;
						std::cout << lockComponentFormat;
						loadedSuccessfully = false;
					}
					else
					{
						std::vector<std::string> keys = StringManager::Instance()->StringToVector(splitLine[4], ',');
						bool validLock = true;

						for (std::string key : keys)
						{
							if (!gameObjects.count(key))
							{
								std::cout << "Error, \"" << filename << "\", line " << lineCount << ": No game object with ID \"" + key + "\" exists. You must create the item(s) that unlock a lock before creating said lock.\n";
								std::cout << generalComponentFormat;
								std::cout << lockComponentFormat;
								loadedSuccessfully = false;
								validLock = false;
							}
						}

						if (validLock)
						{
							gameObjects[splitLine[2]]->AddComponent((Component*) new Lock(gameObjects[splitLine[2]], splitLine[3] == "Yes", keys));
						}
					}
				}
				else if (splitLine[1] == "movable")
				{
					if (splitLine.size() != 3)
					{
						std::cout << "Error, \"" << filename << "\", line " << lineCount << ": Wrong number of values for loading movable component. Values required (including prefix \"C\"): 3. Values given: " << splitLine.size() << ".\n";
						std::cout << generalComponentFormat;
						std::cout << movableComponentFormat;
						loadedSuccessfully = false;
					}
					else
					{
						gameObjects[splitLine[2]]->AddComponent((Component*) new Movable(gameObjects[splitLine[2]]));
					}					
				}
				else if (splitLine[1] == "unlock_commands")
				{
					if (splitLine.size() != 4)
					{
						std::cout << "Error, \"" << filename << "\", line " << lineCount << ": Wrong number of values for loading unlock commands component. Values required (including prefix \"C\"): 4. Values given: " << splitLine.size() << ".\n";
						std::cout << generalComponentFormat;
						std::cout << unlockCommandsComponentFormat;
						loadedSuccessfully = false;
					}
					else if (splitLine[3].length() == 0)
					{
						std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the commands to be unlocked, or \"all\" if the remaining commands are to all be unlocked.\n";
						std::cout << generalComponentFormat;
						std::cout << unlockCommandsComponentFormat;
						loadedSuccessfully = false;
					}
					else
					{
						gameObjects[splitLine[2]]->AddComponent((Component*) new UnlockCommands(gameObjects[splitLine[2]], StringManager::Instance()->StringToVector(splitLine[3], ',')));
					}
				}
				else
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": Invalid component type \"" + splitLine[1] + "\". No component exists of that type.\n";
					std::cout << generalComponentFormat;
					loadedSuccessfully = false;
				}				
			}
			else
			{
				//Formatting error
				std::cout << "Error, \"" << filename << "\", line " << lineCount << ": Invalid prefix. Values prefixes: W, S, L, P, A, I or C. Prefix given: \"" << splitLine[0] << "\".\n";
				loadedSuccessfully = false;
			}
		}

		CommandMove* moveCommand = (CommandMove*)CommandManager::Instance()->GetCommand("move");
		moveCommand->SetDirectionAliases(directionAliases);

		if (name == "")
		{
			std::cout << "Error: No world name was provided.\n";
			std::cout << worldNameFormat;
		}
		
		if (locations.size() == 0)
		{
			std::cout << "Error: No locations were provided.\n";
			std::cout << locationFormat;			
		}

		if (currentLocation == nullptr)
		{
			std::cout << "Error: No starting location was provided.\n";
			std::cout << startConfigurationFormat;
		}
	}
	else
	{
		std::cout << "Error: Unable to open file \"" + filename + "\".\n";
		loadedSuccessfully = false;
	}

	if (!loadedSuccessfully)
	{
		std::cout << "Error: Could not load world from \"" + filename + "\" successfully.\n\n";
	}

	ifs.close();
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

std::string World::DescribeCurrentLocation()
{
	return ((Description*)currentLocation->GetComponent("description"))->GetDescription(); 
}

std::string World::ViewItemsInCurrentLocation()
{
	return ((Container*)currentLocation->GetComponent("container"))->ViewItems();
}

std::string World::ViewPathsAtCurrentLocation()
{
	return currentLocation->ViewPaths();
}

bool World::HasLocation(std::string location)
{
	for(std::pair<std::string, Location*> p: locations)
	{
		if (p.first == location)
		{
			return true;
		}
	}

	return false;
}

Location* World::GetLocation(std::string location)
{
	for (std::pair<std::string, Location*> p : locations)
	{
		if (p.first == location)
		{
			return p.second;
		}
	}

	return nullptr;
}


