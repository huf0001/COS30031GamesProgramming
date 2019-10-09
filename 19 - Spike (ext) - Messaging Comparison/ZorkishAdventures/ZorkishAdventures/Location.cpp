#include "pch.h"

#include "Location.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------


//std::string Location::GetID()
//{
//	return id;
//}

//std::string Location::GetName()
//{
//	return name;
//}
//
//std::string Location::GetDescription()
//{
//	return description;
//}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

Location::Location(std::string id, std::string name, std::string description) : GameObject(id, name, "location")
{
	this->paths = std::map<std::string, Path*>();
	AddComponent((Component*) new Description((GameObject*)this, description));
	AddComponent((Component*) new Container((GameObject*)this, true, true));
}

//Public Methods-------------------------------------------------------------------------------------------------------------------------------------

bool Location::HasPath(std::string direction)
{
	for (std::pair<std::string, Path*> p : paths)
	{
		if (p.first == direction)
		{
			return true;
		}
	}

	return false;
}

void Location::AddPath(std::string direction, Path* path)
{
	if (paths.count(direction))
	{
		std::cout << "Warning: overwriting paths[" << direction << "] with a new path.\n\n";
	}

	paths[direction] = path;
	path->SetContainerID(this->id);
	MessageManager::Instance()->Subscribe(this->id, path);
}

Path* Location::GetPath(std::string direction)
{
	for (std::pair<std::string, Path*> p : paths)
	{
		if (p.first == direction)
		{
			return p.second;
		}
	}

	return nullptr;
}

std::map<std::string, Path*> Location::GetPaths()
{
	return paths;
}

std::string Location::ViewPaths()
{
	if (paths.empty())
	{
		return "";
	}

	std::string result = "";

	for (std::pair<std::string, Path*> p: paths)
	{
		result += "\n\t- " + ((Description*)p.second->GetComponent("description"))->GetDescription();
	}

	return result;
}
