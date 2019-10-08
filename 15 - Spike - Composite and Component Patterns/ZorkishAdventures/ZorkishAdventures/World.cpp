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
					std::cout << "\tFormat: \"W:World Name\".\n";
					loadedSuccessfully = false;
				}
				else if (splitLine[1].length() == 0)
				{
					std::cout << "Error, '" << filename << "', line " << lineCount << ": You must specify the world name.\n";
					std::cout << "\tFormat: \"W:World Name\".\n";
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
				if (splitLine.size() != 2)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": Wrong number of values for loading starting location. Values required (including prefix \"S\"): 2. Values given: " << splitLine.size() << ".\n";
					std::cout << "\tFormat: \"S:starting_location_id\".\n";
					loadedSuccessfully = false;
				}
				else if (splitLine[1].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the id of the starting location.\n";
					std::cout << "\tFormat: \"S:starting_location_id\".\n";
					loadedSuccessfully = false;
				}
				else
				{
					currentLocation = locations[splitLine[1]];
				}
			}
			else if (splitLine[0] == "L")
			{
				//Check Formatting
				if (splitLine.size() != 4)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": Wrong number of values for loading location. Values required (including prefix \"L\"): 4. Values given: " << splitLine.size() << ".\n";
					std::cout << "\tFormat: \"L:location_id_:Location Name:location description\".\n";
					loadedSuccessfully = false;
				}
				else if (splitLine[1].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the location's id.\n";
					std::cout << "\tFormat: \"L:location_id_:Location Name:location description\".\n";
					loadedSuccessfully = false;
				}
				else if (splitLine[2].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the location's name.\n";
					std::cout << "\tFormat: \"L:location_id_:Location Name:location description\".\n";
					loadedSuccessfully = false;
				}
				else if (splitLine[3].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the location's description.\n";
					std::cout << "\tFormat: \"L:location_id_:Location Name:location description\".\n";
					loadedSuccessfully = false;
				}
				else
				{
					locations[splitLine[1]] = new Location(splitLine[1], splitLine[2], splitLine[3]);
					containers[splitLine[1]] = (Container*)locations[splitLine[1]]->GetComponent("container");
					gameObjects[splitLine[1]] = (GameObject*)locations[splitLine[1]];
				}
			}
			else if (splitLine[0] == "P")
			{
				//Check Formatting
				if (splitLine.size() != 7)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": Wrong number of values for loading path between locations. Values required (including prefix \"P\"): 7. Values given: " << splitLine.size() << ".\n";
					std::cout << "\tFormat: \"P:path_id:Path Name:location_from_id:direction:location_to_id:path description\". If Path ID and name are blank, they will be constructed from location_from_id and location_to_id.\n\n";
					loadedSuccessfully = false;
				}
				else if (splitLine[3].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the id of the location the path leads away from.\n";
					std::cout << "\tFormat: \"P:path_id:Path Name:location_from_id:direction:location_to_id:path description\". If Path ID and name are blank, they will be constructed from location_from_id and location_to_id.\n\n";
					loadedSuccessfully = false;
				}
				else if (splitLine[4].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the direction the path leads in.\n";
					std::cout << "\tFormat: \"P:path_id:Path Name:location_from_id:direction:location_to_id:path description\". If Path ID and name are blank, they will be constructed from location_from_id and location_to_id.\n\n";
					loadedSuccessfully = false;
				}
				else if (splitLine[5].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the id of the location the path leads towards.\n";
					std::cout << "\tFormat: \"P:path_id:Path Name:location_from_id:direction:location_to_id:path description\". If Path ID and name are blank, they will be constructed from location_from_id and location_to_id.\n\n";
					loadedSuccessfully = false;
				}
				else if (splitLine[6].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the description of the path.\n";
					std::cout << "\tFormat: \"P:path_id:Path Name:location_from_id:direction:location_to_id:path description\". If Path ID and name are blank, they will be constructed from location_from_id and location_to_id.\n\n";
					loadedSuccessfully = false;
				}
				//Check endpoints of path exist
				else if (!locations.count(splitLine[3]))
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": The path's location_from_id must be the id of a location that has already been created. World.locations doesn't contain a location with id \"" + splitLine[1] + "\".\n";
					std::cout << "\tFormat: \"P:path_id:Path Name:location_from_id:direction:location_to_id:path description\". If Path ID and name are blank, they will be constructed from location_from_id and location_to_id.\n\n";
					loadedSuccessfully = false;
				}
				else if (!locations.count(splitLine[5]))
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": The path's location_to_id must be the id of a location that has already been created. World.locations doesn't contain a location with id \"" + splitLine[1] + "\".\n";
					std::cout << "\tFormat: \"P:path_id:Path Name:location_from_id:direction:location_to_id:path description\". If Path ID and name are blank, they will be constructed from location_from_id and location_to_id.\n\n";
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
					locations[splitLine[3]]->AddPath(splitLine[4], path);
					gameObjects[path->GetID()] = (GameObject*)path;
				}
			}
			else if (splitLine[0] == "A")
			{
				//Check Formatting
				if (splitLine.size() != 3)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": Wrong number of values for loading direction alias. Values required (including prefix \"A\"): 5. Values given: " << splitLine.size() << ".\n";
					std::cout << "\tFormat: \"A:direction name:direction alias\".\n\n";
					loadedSuccessfully = false;
				}
				else if (splitLine[1].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the name of the direction to be given an alias.\n";
					std::cout << "\tFormat: \"A:direction name:direction alias\".\n\n";
					loadedSuccessfully = false;
				}
				else if (splitLine[2].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the alias of the direction.\n";
					std::cout << "\tFormat: \"A:direction name:direction alias\".\n\n";
					loadedSuccessfully = false;
				}
				//Check the given alias isn't already assigned to a direction
				else if (directionAliases.count(splitLine[2]))
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": A given alias can only be given to a single direction. A direction already has the alias \"" + splitLine[2] + "\".\n";
					std::cout << "\tFormat: \"A:direction name:direction alias\".\n\n";
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
				//TODO: "I:item_id:Item Name:item description:container_game_object_id:no. components:component_id,component_id, . . ."
				//Check Formatting
				if (splitLine.size() != 6)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": Wrong number of values for loading item. Values required (including prefix \"I\"): 5. Values given: " << splitLine.size() << ".\n";
					std::cout << "\tFormat: \"I:container_id:item_id:Item Name:item description:component_id_1,component_id_2, . . .\". (container_id: the location or container item the item is being stored inside.)\n\n";
					loadedSuccessfully = false;
				}
				else if (splitLine[1].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the id of the container (location or container item) that holds the item.\n";
					std::cout << "\tFormat: \"I:container_id:item_id:Item Name:item description:component_id_1,component_id_2, . . .\". (container_id: the location or container item the item is being stored inside.)\n\n";
					loadedSuccessfully = false;
				}
				else if (splitLine[2].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the item's id.\n";
					std::cout << "\tFormat: \"I:container_id:item_id:Item Name:item description:component_id_1,component_id_2, . . .\". (container_id: the location or container item the item is being stored inside.)\n\n";
					loadedSuccessfully = false;
				}
				else if (splitLine[3].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the item's name.\n";
					std::cout << "\tFormat: \"I:container_id:item_id:Item Name:item description:component_id_1,component_id_2, . . .\". (container_id: the location or container item the item is being stored inside.)\n\n";
					loadedSuccessfully = false;
				}
				else if (splitLine[4].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the item's description.\n";
					std::cout << "\tFormat: \"I:container_id:item_id:Item Name:item description:component_id_1,component_id_2, . . .\". (container_id: the location or container item the item is being stored inside.)\n\n";
					loadedSuccessfully = false;
				}

				else if (splitLine[5].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the item's components, or \"none\" if it has none.\n";
					std::cout << "\tFormat: \"I:container_id:item_id:Item Name:item description:component_id_1,component_id_2, . . .\". (container_id: the location or container item the item is being stored inside.)\n\n";
					loadedSuccessfully = false;
				}
				//Check the item's container exists
				else if (!containers.count(splitLine[1]))
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": The item's container_id must be the id of a container (i.e. location or container item) that has already been created. Map \"containers\" in World.World() does not include container \"" + splitLine[4] + "\".\n";
					std::cout << "\tFormat: \"I:container_id:item_id:Item Name:item description:component_id_1,component_id_2, . . .\". (container_id: the location or container item the item is being stored inside.)\n\n";
					loadedSuccessfully = false;
				}
				//Create the item
				else
				{	
					Item* item = new Item(splitLine[2], splitLine[3], splitLine[4]);
					containers[splitLine[1]]->AddItem(item);
					gameObjects[item->GetID()] = (GameObject*)item;

					if (splitLine[5] != "none")
					{
						std::vector<std::string> componentIds = StringManager::Instance()->StringToVector(splitLine[5], ',');

						for (std::string componentId : componentIds)
						{
							Component* component = ComponentFactory::Instance()->CreateComponent(componentId, (GameObject*)item);

							if (component == nullptr)
							{
								std::cout << "Error, \"" << filename << "\", line " << lineCount << ": Invalid component ID \"" + componentId + "\". ComponentFactory cannot produce Components with that component ID.\n";
								std::cout << "\tFormat: \"I:container_id:item_id:Item Name:item description:component_id_1,component_id_2, . . .\". (container_id: the location or container item the item is being stored inside.)\n\n";
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
				std::string generalFormat = "\tGeneral Format: \"C:component_type:game_object_id[:component specific parameters]\".\n\n";
				
				if (splitLine.size() < 3)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": Wrong number of values for loading components. Values required (including prefix \"C\"): 3 or more. Values given: " << splitLine.size() << ".\n";
					std::cout << generalFormat;
					loadedSuccessfully = false;
				}
				else if (splitLine[1].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the type of component to be created.\n";
					std::cout << generalFormat;
					loadedSuccessfully = false;
				}
				else if (splitLine[2].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the id of the game object the component will be assigned to.\n";
					std::cout << generalFormat;
					loadedSuccessfully = false;
				}
				else if (!gameObjects.count(splitLine[2]))
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": The component's game_object_id must be the id of a game object that has already been created. Map \"gameObjects\" in World.World() does not include game object \"" + splitLine[2] + "\".\n";
					std::cout << generalFormat;
					loadedSuccessfully = false;
				}
				else if (splitLine[1] == "container")
				{
					std::string containerFormat = "\tContainer Format: \"C:container:game_object_id:is_open?:always_open?\".\n\n";

					if (splitLine.size() != 5)
					{
						std::cout << "Error, \"" << filename << "\", line " << lineCount << ": Wrong number of values for loading container component. Values required (including prefix \"C\"): 5. Values given: " << splitLine.size() << ".\n";
						std::cout << generalFormat;
						std::cout << containerFormat;
						loadedSuccessfully = false;
					}
					else if (splitLine[3] != "Yes" && splitLine[3] != "No")
					{
						std::cout << "Error, \"" << filename << "\", line " << lineCount << ": is_open? must be \"Yes\" or \"No\".\n";
						std::cout << generalFormat;
						std::cout << containerFormat;
						loadedSuccessfully = false;
					}
					else if (splitLine[4] != "Yes" && splitLine[4] != "No")
					{
						std::cout << "Error, \"" << filename << "\", line " << lineCount << ": always_open? must be \"Yes\" or \"No\".\n";
						std::cout << generalFormat;
						std::cout << containerFormat;
						loadedSuccessfully = false;
					}
					else
					{
						gameObjects[splitLine[2]]->AddComponent((Component*) new Container(gameObjects[splitLine[2]], splitLine[3] == "Yes", splitLine[4] == "Yes"));
					}					
				}
				else if (splitLine[1] == "description")
				{
					std::string descriptionFormat = "\tDescription Format: \"C:description:game_object_id:description of game object\".\n\n";

					if (splitLine.size() != 4)
					{
						std::cout << "Error, \"" << filename << "\", line " << lineCount << ": Wrong number of values for loading container component. Values required (including prefix \"C\"): 5. Values given: " << splitLine.size() << ".\n";
						std::cout << generalFormat;
						std::cout << descriptionFormat;
						loadedSuccessfully = false;
					}
					else if (splitLine[3].length() == 0)
					{
						std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the description to be assigned to the description component.\n";
						std::cout << generalFormat;
						std::cout << descriptionFormat;
						loadedSuccessfully = false;
					}
					else
					{
						gameObjects[splitLine[2]]->AddComponent((Component*) new Description(gameObjects[splitLine[2]], splitLine[3]));
					}
				}
				else if (splitLine[1] == "lock")
				{
					std::string lockFormat = "\tLock Format: \"C:lock:game_object_id:is_locked?:unlockable_with_item_id_1,unlockable_with_item_id_2, . . .\". If not unlockable, specify \"none\".\n\n";

					if (splitLine[3] != "Yes" && splitLine[3] != "No")
					{
						std::cout << "Error, \"" << filename << "\", line " << lineCount << ": is_locked? must be \"Yes\" or \"No\".\n";
						std::cout << generalFormat;
						std::cout << lockFormat;
						loadedSuccessfully = false;
					}
					else if (splitLine[4].size() == 0)
					{
						std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must list the items that the lock can be unlocked with, or \"none\" if not unlockable.\n";
						std::cout << generalFormat;
						std::cout << lockFormat;
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
								std::cout << generalFormat;
								std::cout << lockFormat;
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
					std::string movableFormat = "\tMovable Format: \"C:movable:game_object_id\".\n\n";

					if (splitLine.size() != 3)
					{
						std::cout << "Error, \"" << filename << "\", line " << lineCount << ": Wrong number of values for loading movable component. Values required (including prefix \"C\"): 3. Values given: " << splitLine.size() << ".\n";
						std::cout << generalFormat;
						std::cout << movableFormat;
						loadedSuccessfully = false;
					}
					else
					{
						gameObjects[splitLine[2]]->AddComponent((Component*) new Movable(gameObjects[splitLine[2]]));
					}					
				}
				else
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": Invalid component type \"" + splitLine[1] + "\". No component exists of that type.\n";
					std::cout << generalFormat;
					loadedSuccessfully = false;
				}				
			}
			else
			{
				//Formatting error
				std::cout << "Error, \"" << filename << "\", line " << lineCount << ": Invalid prefix. Values prefixes: W, S, L, P, C or I. Prefix given: \"" << splitLine[0] << "\".\n";
				loadedSuccessfully = false;
			}
		}

		CommandMove* moveCommand = (CommandMove*)CommandManager::Instance()->GetCommand("move");
		moveCommand->SetDirectionAliases(directionAliases);

		if (name == "")
		{
			std::cout << "Error: No world name was provided.\n";
			std::cout << "\tFormat: \"W:World Name\".\n";
		}
		
		if (locations.size() == 0)
		{
			std::cout << "Error: No locations were provided.\n";
			std::cout << "\tFormat: \"L:location_id_:Location Name:location description\".\n";			
		}

		if (currentLocation == nullptr)
		{
			std::cout << "Error: No starting location was provided.\n";
			std::cout << "\tFormat: \"S:starting_location_id\".\n";
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


