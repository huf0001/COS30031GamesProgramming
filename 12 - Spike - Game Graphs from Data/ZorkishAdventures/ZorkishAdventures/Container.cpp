#include "pch.h"

#include "Container.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

Container::Container()
{
	items = std::vector<Item*>();
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

void Container::AddItem(Item* item)
{
	items.push_back(item);
}

bool Container::HasItem(std::vector<std::string> input)
{
	if (!items.empty())
	{
		std::string string = StringManager::Instance()->VectorToString(input, ' ');

		for (int i = 0; i < items.size(); i++)
		{
			if (StringManager::Instance()->ToLowercase(items[i]->GetName()) == string)
			{
				return true;
			}
		}
	}

	return false;
}

Item* Container::GetItem(std::vector<std::string> input)
{
	if (!items.empty())
	{
		std::string string = StringManager::Instance()->VectorToString(input, ' ');

		for (int i = 0; i < items.size(); i++)
		{
			if (StringManager::Instance()->ToLowercase(items[i]->GetName()) == string)
			{
				return items[i];
			}
		}
	}

	return nullptr;
}

std::string Container::ViewItem(std::vector<std::string> input)
{
	/*std::vector<std::string> inputCopy = std::vector<std::string>(input);
	std::vector<std::string> name;

	for(int i = input.size() - 1; i >= 0; i--)
	{
		inputCopy.pop_back();

		if (input[i] != "in")
		{
			name.insert(name.begin(), input[i]);
		}
		else
		{
			Container* container = (Container*)GetItem(name);

			if (container != nullptr)
			{
				return container->ViewItem(inputCopy);
			}
			
			return "You can't look in " + StringManager::Instance()->VectorToString(name, ' ') + "; it isn't there.";
		}
	}*/

	Item* item = GetItem(input);

	if (item != nullptr)
	{
		return item->GetDescription();
	}

	return "You cannot find '" + StringManager::Instance()->VectorToString(input, ' ') + "'; it isn't where you were looking.";
}

void Container::RemoveItem(std::vector<std::string> input)
{
	if (!items.empty())
	{
		std::string string = StringManager::Instance()->VectorToString(input, ' ');

		for (int i = 0; i < items.size(); i++)
		{
			if (StringManager::Instance()->ToLowercase(items[i]->GetName()) == string)
			{
				items.erase(items.begin() + i);
				break;
			}
		}
	}
}

std::string Container::ViewItems()
{
	if (items.empty())
	{
		return "";
	}

	std::string result = "";

	for (int i = 0; i < items.size(); i++)
	{
		result += "\n\t- " + items[i]->GetName();
	}

	return result;
}

