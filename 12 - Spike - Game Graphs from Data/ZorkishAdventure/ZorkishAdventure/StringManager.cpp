#include "StringManager.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

StringManager* StringManager::instance = nullptr;

StringManager* StringManager::Instance()
{
	if (instance == nullptr)
	{
		instance = new StringManager();
	}

	return instance;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

StringManager::StringManager()
{
	
}

//Public Methods-------------------------------------------------------------------------------------------------------------------------------------

std::string StringManager::ToUppercase(std::string string)
{
	transform(string.begin(), string.end(), string.begin(), ::toupper);
	return string;
}

std::vector<std::string> StringManager::ToUppercase(std::vector<std::string> strings)
{
	for (int i = 0; i < strings.size(); i++)
	{
		strings[i] = ToUppercase(strings[i]);
	}

	return strings;
}

std::string StringManager::ToLowercase(std::string string)
{
	transform(string.begin(), string.end(), string.begin(), ::tolower);
	return string;
}

std::vector<std::string> StringManager::ToLowercase(std::vector<std::string> strings)
{
	for (int i = 0; i < strings.size(); i++)
	{
		strings[i] = ToLowercase(strings[i]);
	}

	return strings;
}

std::vector<std::string> StringManager::StringToVector(std::string string, char delimiter)
{
	std::vector<std::string> result;
	std::stringstream ss(string);
	std::string temp;

	while (getline(ss, temp, delimiter))
	{
		result.push_back(temp);
	}

	return result;
}

std::string StringManager::VectorToString(std::vector<std::string> vector, char delimiter)
{
	std::string result;

	for (int i = 0; i < vector.size(); i++)
	{
		if (i > 0)
		{
			result += delimiter;
		}

		result += vector[i];
	}

	return result;
}

bool StringManager::VectorContainsString(std::vector<std::string> vector, std::string string)
{
	for (int i = 0; i < vector.size(); i++)
	{
		if (vector[i] == string)
		{
			return true;
		}
	}

	return false;
}

