#include "pch.h"

#include "World.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

Location* World::GetCurrentLocation()
{
	return currentLocation;
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
	loadedSuccessfully = true;

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
				//Check formatting
				if (splitLine.size() != 2)
				{
					std::cout << "Error, '" << filename << "', line " << lineCount << ": Wrong number of values for loading world name. Values required (including prefix 'W'): 2. Values given: " << splitLine.size() << ".\n";
					std::cout << "Format: \"W:World Name\".\n\n";
					loadedSuccessfully = false;
					break;
				}
				else if (splitLine[1].length() == 0)
				{
					std::cout << "Error, '" << filename << "', line " << lineCount << ": You must specify the world name.\n";
					std::cout << "Format: \"W:World Name\".\n\n";
					loadedSuccessfully = false;
					break;
				}
			}
			else if (splitLine[0] == "S")
			{
				//Check formatting
				if (splitLine.size() != 2)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": Wrong number of values for loading starting location. Values required (including prefix \"S\"): 2. Values given: " << splitLine.size() << ".\n";
					std::cout << "Format: \"S:starting_location_id\".\n\n";
					loadedSuccessfully = false;
					break;
				}
				else if (splitLine[1].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the id of the starting location.\n";
					std::cout << "Format: \"S:starting_location_id\".\n\n";
					loadedSuccessfully = false;
					break;
				}
				else
				{
					name = splitLine[1];
				}
			}
			else if (splitLine[0] == "L")
			{
				//Check formatting
				if (splitLine.size() != 4)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": Wrong number of values for loading location. Values required (including prefix \"L\"): 4. Values given: " << splitLine.size() << ".\n";
					std::cout << "Format: \"L:location_id_:Location Name:location description\".\n";
					loadedSuccessfully = false;
					break;
				}
				else if (splitLine[1].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the location's id.\n";
					std::cout << "Format: \"L:location_id_:Location Name:location description\".\n";
					loadedSuccessfully = false;
					break;
				}
				else if (splitLine[2].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the location's name.\n";
					std::cout << "Format: \"L:location_id_:Location Name:location description\".\n";
					loadedSuccessfully = false;
					break;
				}
				else if (splitLine[3].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the location's description.\n";
					std::cout << "Format: \"L:location_id_:Location Name:location description\".\n";
					loadedSuccessfully = false;
					break;
				}
				else
				{
					locations[splitLine[1]] = new Location(splitLine[1], splitLine[2], splitLine[3]);
					containers[splitLine[1]] = (Container*)locations[splitLine[1]];
				}
			}
			else if (splitLine[0] == "P")
			{
				//Check formatting
				if (splitLine.size() != 5)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": Wrong number of values for loading path between locations. Values required (including prefix \"P\"): 5. Values given: " << splitLine.size() << ".\n";
					std::cout << "Format: \"P:location_from_id:direction:location_to_id:path description\".\n\n";
					loadedSuccessfully = false;
					break;
				}
				else if (splitLine[1].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the id of the location the path leads away from.\n";
					std::cout << "Format: \"P:location_from_id:direction:location_to_id:path description\".\n\n";
					loadedSuccessfully = false;
					break;
				}
				else if (splitLine[2].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the direction the path leads in.\n";
					std::cout << "Format: \"P:location_from_id:direction:location_to_id:path description\".\n\n";
					loadedSuccessfully = false;
					break;
				}
				else if (splitLine[3].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the id of the location the path leads towards.\n";
					std::cout << "Format: \"P:location_from_id:direction:location_to_id:path description\".\n\n";
					loadedSuccessfully = false;
					break;
				}
				else if (splitLine[4].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the description of the path.\n";
					std::cout << "Format: \"P:location_from_id:direction:location_to_id:path description\".\n\n";
					loadedSuccessfully = false;
					break;
				}
				//Check endpoints of path exist
				else if (!locations.count(splitLine[1]))
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": The path's location_from_id must be the id of a location that has already been created. World.locations doesn't contain a location with id \"" + splitLine[1] + "\".\n";
					std::cout << "Format: \"P:location_from_id:direction:location_to_id:path description\".\n\n";
					loadedSuccessfully = false;
					break;
				}
				else if (!locations.count(splitLine[3]))
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": The path's location_to_id must be the id of a location that has already been created. World.locations doesn't contain a location with id \"" + splitLine[1] + "\".\n";
					std::cout << "Format: \"P:location_from_id:direction:location_to_id:path description\".\n\n";
					loadedSuccessfully = false;
					break;
				}
				//Create the path
				else
				{
					locations[splitLine[1]]->AddPath(splitLine[2], new Path(splitLine[3], splitLine[4]));
				}
			}
			else if (splitLine[0] == "C")
			{
				//Check formatting
				if (splitLine.size() != 5)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": Wrong number of values for loading container item. Values required (including prefix \"C\"): 5. Values given: " << splitLine.size() << ".\n";
					std::cout << "Format: \"C:container_item_id:Container Item Name:container item description:container_id\". (container_id: the location or container item the container item is being stored inside.)\n\n";
					loadedSuccessfully = false;
					break;
				}
				else if (splitLine[1].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the container item's id.\n";
					std::cout << "Format: \"C:container_item_id:Container Item Name:container item description:container_id\". (container_id: the location or container item the container item is being stored inside.)\n\n";
					loadedSuccessfully = false;
					break;
				}
				else if (splitLine[2].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the container item's name.\n";
					std::cout << "Format: \"C:container_item_id:Container Item Name:container item description:container_id\". (container_id: the location or container item the container item is being stored inside.)\n\n";
					loadedSuccessfully = false;
					break;
				}
				else if (splitLine[3].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the container item's description.\n";
					std::cout << "Format: \"C:container_item_id:Container Item Name:container item description:container_id\". (container_id: the location or container item the container item is being stored inside.)\n\n";
					loadedSuccessfully = false;
					break;
				}
				else if (splitLine[4].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the id of the container (location or container item) that holds the container item.\n";
					std::cout << "Format: \"C:container_item_id:Container Item Name:container item description:container_id\". (container_id: the location or container item the container item is being stored inside.)\n\n";
					loadedSuccessfully = false;
					break;
				}
			}
			else if (splitLine[0] == "I")
			{
				//Check formatting
				if (splitLine.size() != 5)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": Wrong number of values for loading item. Values required (including prefix \"I\"): 5. Values given: " << splitLine.size() << ".\n";
					std::cout << "Format: \"I:item_id:Item Name:item description:container_id\". (container_id: the location or container item the item is being stored inside.)\n\n";
					loadedSuccessfully = false;
					break;
				}
				else if (splitLine[1].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the item's id.\n";
					std::cout << "Format: \"I:item_id:Item Name:item description:container_id\". (container_id: the location or container item the item is being stored inside.)\n\n";
					loadedSuccessfully = false;
					break;
				}
				else if (splitLine[2].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the item's name.\n";
					std::cout << "Format: \"I:item_id:Item Name:item description:container_id\". (container_id: the location or container item the item is being stored inside.)\n\n";
					loadedSuccessfully = false;
					break;
				}
				else if (splitLine[3].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the item's description.\n";
					std::cout << "Format: \"I:item_id:Item Name:item description:container_id\". (container_id: the location or container item the item is being stored inside.)\n\n";
					loadedSuccessfully = false;
					break;
				}
				else if (splitLine[4].length() == 0)
				{
					std::cout << "Error, \"" << filename << "\", line " << lineCount << ": You must specify the id of the container (location or container item) that holds the item.\n";
					std::cout << "Format: \"I:item_id:Item Name:item description:container_id\". (container_id: the location or container item the item is being stored inside.)\n\n";
					loadedSuccessfully = false;
					break;
				}
			}
			else
			{
				//Formatting error
				std::cout << "Error, \"" << filename << "\", line " << lineCount << ": Invalid prefix. Values prefixes: W, S, L, P, C or I. Prefix given: \"" << splitLine[0] << "\".\n";
				loadedSuccessfully = false;
				break;
			}
		}

		//TODO: check that a location was loaded
		//TODO: check that a starting location was specified
	}
	else
	{
		std::cout << "\tUnable to open file\n";
		loadedSuccessfully = false;
	}

	ifs.close();




	
	////Assign to fields
	//this->name = filename;
	//locations = std::map<std::string, Location*>();

	////Setup locations in world
	//locations["Void"] = new Location("Void", "The Void", "This world is simple and pointless. Used to test Zorkish phase 1 spec.");

	////Set starting location
	//currentLocation = locations["Void"];

	////Flesh out testing location "Void"
	//currentLocation->AddItem(new Item("book", "Book", "A dusty old book."));
	//currentLocation->AddItem(new Item("pencil", "Pencil", "A short, used pencil."));
	//currentLocation->AddItem(new Item("glasses", "Glasses", "A pair of glasses."));
	//currentLocation->AddItem(new Item("quill", "Quill", "A black and grey quill."));

	//currentLocation->AddItem((Item*) new ContainerItem("bag", "Bag", "A red bag."));
	//ContainerItem* bag = (ContainerItem*)currentLocation->GetItem(StringManager::Instance()->StringToVector("bag", ' '));
	//bag->AddItem(new Item("gold coin", "Gold Coin", "A gold coin. This is valuable."));
	//bag->AddItem(new Item("silver coin", "Silver Coin", "A silver coin. This is worth a bit."));
	//bag->AddItem(new Item("copper coin", "Copper Coin", "A copper coin. This is not worth much."));
	//bag->AddItem(new ContainerItem("box", "Box", "A small wooden box."));
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

std::string World::DescribeCurrentLocation()
{
	return currentLocation->GetDescription();
}

std::string World::ViewItemsInCurrentLocation()
{
	return currentLocation->ViewItems();
}
