#include "pch.h"

#include "CommandMove.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

void CommandMove::SetDirectionAliases(std::map<std::string, std::string> directionAliases)
{
	this->directionAliases = directionAliases;
}

std::string CommandMove::GetSyntax()
{
	std::string result;

	result += "MOVE\n";
	result += "----------------------------\n";
	result += "Function:\n";
	result += "\t- Move to a new location.\n";
	result += "Syntax:\n";
	result += "\t- \"move [direction]\"\n";
	result += "\t- \"[direction]\"\n";

	if (aliases.size() > 0)
	{
		result += "Aliases for \"move\":\n";

		for (std::string alias : aliases)
		{
			result += "\t- \"" + alias + "\"\n";
		}
	}

	if (directionAliases.size() > 0)
	{
		result += "Aliases for common directions:\n";

		for (std::pair<std::string, std::string> pair : directionAliases)
		{
			result += "\t- \"" + pair.first + "\" = \"" + pair.second + "\"\n";
		}
	}

	return result;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

CommandMove::CommandMove()
{
	AddKeyword("move");
	AddAlias("go");
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

void CommandMove::AddDirectionAlias(std::string direction, std::string alias)
{
	directionAliases[alias] = direction;
}

bool CommandMove::HasDirectionWithAlias(std::string alias)
{
	for (std::pair<std::string, std::string> p : directionAliases)
	{
		if (p.first == alias)
		{
			return true;
		}
	}

	return false;
}

std::string CommandMove::GetDirectionWithAlias(std::string alias)
{
	for (std::pair<std::string, std::string> p : directionAliases)
	{
		if (p.first == alias)
		{
			return p.second;
		}
	}

	return "";
}

std::string CommandMove::DeAliasDirection(std::string direction)
{
	if (HasDirectionWithAlias(direction))
	{
		return GetDirectionWithAlias(direction);
	}

	return direction;
}

bool CommandMove::CanProcess(std::vector<std::string> input, World* world, Player* player)
{
	std::string inputString = StringManager::Instance()->VectorToString(input, ' ');

	return HasKeyword(input[0]) 
		|| HasAlias(input[0])
		|| world->GetCurrentLocation()->HasPath(inputString)
		|| (HasDirectionWithAlias(inputString) && world->GetCurrentLocation()->HasPath(GetDirectionWithAlias(inputString)));
}

std::string CommandMove::Process(std::vector<std::string> input, World* world, Player* player)
{
	if (HasKeyword(input[0]))
	{
		input.erase(input.begin());
	}

	std::string direction = DeAliasDirection(StringManager::Instance()->VectorToString(input, ' '));

	if (world->GetCurrentLocation()->HasPath(direction))
	{
		Path* path = world->GetCurrentLocation()->GetPath(direction);

		if (path != nullptr)
		{
			std::string destination = path->GetDestination();

			if (world->HasLocation(destination))
			{
				Location* location = world->GetLocation(destination);

				if (location != nullptr)
				{
					world->SetCurrentLocation(location);
					return "Moving " + direction + " . . .\n" + CommandManager::Instance()->GetCommand("look")->Process(StringManager::Instance()->StringToVector("look", ' '), world, player);
				}
			}
		}
	}

	return "There is nothing in that direction.";
}

void CommandMove::ResetAliases()
{
	aliases = std::vector<std::string>();
	directionAliases = std::map<std::string, std::string>();
}