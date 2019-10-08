#include "pch.h"

#ifndef STRINGMANAGER_H
#define STRINGMANAGER_H

#include <string>
#include <vector>
#include <array>
#include <sstream>

class StringManager
{
protected:
	//Private Fields
	static StringManager* instance;

	//Constructor
	StringManager();
public:
	//Public Properties
	static StringManager* Instance();

	//Public Methods
	std::string ToUppercase(std::string string);
	std::vector<std::string> ToUppercase(std::vector<std::string> strings);
	std::string ToLowercase(std::string string);
	std::vector<std::string> ToLowercase(std::vector<std::string> strings);
	std::vector<std::string> StringToVector(std::string string, char delimiter);
	std::string VectorToString(std::vector<std::string> vector, char delimiter);
	bool VectorContainsString(std::vector<std::string> vector, std::string string);
};

#endif
