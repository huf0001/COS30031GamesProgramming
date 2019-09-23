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
					containers[splitLine[1]] = (Container*)locations[splitLine[1]];
				}
			}
			else if (splitLine[0] == "P")
			{
				//Check Formatting
				if (splitLine.size() != 7)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": Wrong number of values for loading path between locations. Values required (including prefix \"P\"): 5. Values given: " << splitLine.size() << ".\n";
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

					locations[splitLine[3]]->AddPath(splitLine[4], new Path(splitLine[1], splitLine[2], splitLine[5], splitLine[6]));
					//locations[splitLine[3]]->AddPath(splitLine[4], new Path(locations[splitLine[3]], splitLine[5], splitLine[6]));
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
					Item* i = new Item(splitLine[2], splitLine[3], splitLine[4]);
					containers[splitLine[1]]->AddItem(i);

					if (splitLine[5] != "none")
					{
						std::vector<std::string> componentIds = StringManager::Instance()->StringToVector(splitLine[5], ',');

						for (std::string componentId : componentIds)
						{
							Component* component = ComponentFactory::Instance()->CreateComponent(componentId, (GameObject*)i);

							if (component == nullptr)
							{
								std::cout << "Error, \"" << filename << "\", line " << lineCount << ": Invalid component ID \"" + componentId + "\". ComponentFactory cannot produce Components with that component ID.\n";
								std::cout << "\tFormat: \"I:container_id:item_id:Item Name:item description:component_id_1,component_id_2, . . .\". (container_id: the location or container item the item is being stored inside.)\n\n";
								loadedSuccessfully = false;
							}
							else
							{
								i->AddComponent(component);
							}
						}
					}				
				}
			}
			else if (splitLine[0] == "C")
			{
				//Handles components
				//"C:component_id:game_object_id"
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


