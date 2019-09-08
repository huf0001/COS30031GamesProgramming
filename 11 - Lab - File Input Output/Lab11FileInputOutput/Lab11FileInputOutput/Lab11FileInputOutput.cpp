// Lab11FileInputOutput.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "nlohmann/json.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

//Class Definition-----------------------------------------------------------------------------------------------------------------------------------

struct CompoundType
{
public:
	char character;
	int integer;
	float floatingPointNumber;
	std::vector<int> intVector;
	std::string string;

	CompoundType();
	void Print();
};

//Class Implementation-------------------------------------------------------------------------------------------------------------------------------

//Constructor--------------------------------------------------------------------------------------

CompoundType::CompoundType()
{
	intVector = std::vector<int>();
}

void CompoundType::Print()
{
	std::cout << "Printing CompoundType";
	std::cout << "\n";
	std::cout << "\n\tCharacter: " << character;
	std::cout << "\n\tInteger: " << integer;
	std::cout << "\n\tFloating Point Number: " << floatingPointNumber;
	std::cout << "\n\tInt Vector:";

	for (int i = 0; i < intVector.size(); i++)
	{
		std::cout << "\n\t\tInt Vector [" << i << "]: " << intVector[i];
	}

	std::cout << "\n\tString: " << string;
	std::cout << "\n";
}

//Lab Section Methods--------------------------------------------------------------------------------------------------------------------------------

void ResetStringStream(std::stringstream* stream)
{
	const static std::stringstream initial;

	stream->str(std::string());
	stream->clear();
	stream->copyfmt(initial);
}

std::vector<std::string> JsonObjectStringToVector(std::string string)
{
	std::vector<std::string> result;
	std::stringstream ss(string);
	std::string temp;

	while (getline(ss, temp, ','))
	{
		if (temp.length() != 0)
		{
			if (temp[0] == '{')
			{
				temp.erase(temp.begin());
			}

			if (temp[temp.size() - 1] == '}')
			{
				temp.pop_back();
			}
		}

		result.push_back(temp);
	}

	return result;
}

std::vector<std::string> StringToVector(std::string string, char delimiter)
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

void PartABinaryFileOutputInput()
{
	std::cout << "<<< Part A - Binary File Output / Input >>>" << std::endl;
	std::cout << std::endl;
	
	CompoundType test = CompoundType();

	test.character = 'c';
	test.integer = 8345;
	test.floatingPointNumber = 865.00585;
	test.intVector.push_back(2);
	test.intVector.push_back(6);
	test.intVector.push_back(974865);
	test.string = "test string";

	test.Print();

	//Write to file
	std::cout << "\n";
	std::cout << "Writing to File\n";
	std::cout << "\n";
	std::ofstream outputToMyFile;
	outputToMyFile.open("test1.bin", std::ios::out | std::ios::binary | std::ios::trunc);

	if (outputToMyFile.is_open())
	{
		outputToMyFile << test.character << std::endl;
		outputToMyFile << test.integer << std::endl;
		outputToMyFile << test.floatingPointNumber << std::endl;
		outputToMyFile << test.intVector.size() << std::endl;

		for (int i = 0; i < test.intVector.size(); i++)
		{
			outputToMyFile << test.intVector[i] << std::endl;
		}

		outputToMyFile << test.string << std::endl;
	}
	else
	{
		std::cout << "Unable to open file";
	}
	
	outputToMyFile.close();

	//Read from file
	std::cout << "\n";
	std::cout << "Reading from File\n";
	std::cout << "\n";
	
	std::ifstream inputFromMyFile("test1.bin");
	std::string line;
	test = CompoundType();

	if (inputFromMyFile.is_open())
	{		
		std::getline(inputFromMyFile, line);
		std::stringstream readToTestClass(line);
		readToTestClass >> test.character;

		ResetStringStream(&readToTestClass);
		std::getline(inputFromMyFile, line);
		readToTestClass.str(line);
		readToTestClass >> test.integer;
		
		ResetStringStream(&readToTestClass);
		std::getline(inputFromMyFile, line);
		readToTestClass.str(line);
		readToTestClass >> test.floatingPointNumber;

		int n;
		int x;
		ResetStringStream(&readToTestClass);
		std::getline(inputFromMyFile, line);
		readToTestClass.str(line);
		readToTestClass >> n;

		for (int i = 0; i < n; i++)
		{
			ResetStringStream(&readToTestClass);
			std::getline(inputFromMyFile, line);
			readToTestClass.str(line);
			readToTestClass >> x;
			test.intVector.push_back(x);
		}

		ResetStringStream(&readToTestClass);
		std::getline(inputFromMyFile, test.string);
		
		/*readToTestClass.str(test.string);
		readToTestClass >> n;
		std::cout << "Reading data to inappropriate data type\n\n";
		std::cout << "\tString: " << test.string << "\n";
		std::cout << "\tInt: " << n << "\n\n";*/
	}
	else
	{
		std::cout << "\tUnable to open file\n";
	}

	inputFromMyFile.close();

	test.Print();

	std::cout << std::endl;
}

void PartBSimpleTextFileInputWithSplit()
{
	std::cout << "<<< Part B - Simple Text File Input with Split >>>" << std::endl;
	std::cout << std::endl;
	
	std::ifstream inputFromTextFile("test2.txt");
	std::string line;

	if (inputFromTextFile.is_open())
	{
		while (std::getline(inputFromTextFile, line))
		{
			if (line.length() == 0 || line[0] == '#')
			{
				continue;
			}

			std::cout << "Printing new line\n\n";
			
			//Note: not sure what is meant by "appropriate number of bits"
			std::vector<std::string> splitLine = StringToVector(line, ':');

			for (int i = 0; i < splitLine.size(); i++)
			{
				std::cout << "\t" << splitLine[i] << "\n";
			}
		}
	}
	else
	{
		std::cout << "\tUnable to open file\n";
	}

	inputFromTextFile.close();

	std::cout << std::endl;
}

void PartCReadingJSONFiles()
{
	//Create a simple JSON test program that opens your JSON file (task3.json), and then prints
	//the contents to screen
	std::cout << "<<< Part C - Reading JSON Files >>>" << std::endl;
	std::cout << std::endl;

	//from https://github.com/nlohmann/json
	//std::ifstream ifs("test3.json");
	//nlohmann::json j;
	//ifs >> j;		//no operator >> matches the operand types std::ifstream, nlohmann::json

	
	//from http://www.parresianz.com/c++/json/json-input/
	//nlohmann::json j;
	//std::ifstream ifs("test3.json");
	//std::stringstream iss;
	//iss << ifs.rdbuf();
	//j << iss;		//deprecated, suggests "iss >> j;"; no operator << matches the operand types used
	//iss >> j;		//no operator >> matches the operand types used
					

	//from https://stackoverflow.com/questions/33628250/c-reading-a-json-object-from-file-with-nlohmann-json
	//std::ifstream ifs("test3.json");
	//nlohmann::json j(ifs);	//json doesn't take argument type ifstream
	//nlohmann::json j = nlohmann::json::parse(ifs);	//Claims json has no member "parse", yet parse was suggested
							

	//adapted from http://www.parresianz.com/c++/json/json-input/
	/*nlohmann::json j;
	std::ifstream ifs("test3.json");
	std::stringstream iss;
	iss << ifs.rdbuf();
	std::string jsonAsString;	
	std::cout << jsonAsString << std::endl;*/	//Comes out a small chunk at a time; maybe there's a better way to do it for this task . . .


	//Doesn't read the file contents in to a json object, but at least reads in the contents. Would not be appropriate for multi-line formatting.
	//Perhaps reading in the whole file's contents into one string, and then manually processing it and breaking it apart into objects, and then
	//into attribute-value pairs for that object, and slowly building the json file's contents up as json objects might be somehow workable with
	//this input method
	std::ifstream ifs("test3.json");
	std::string line;

	if (ifs.is_open())
	{
		while (std::getline(ifs, line))
		{
			std::cout << "Printing new line\n\n";

			//Note: not sure what is meant by "appropriate number of bits"
			std::vector<std::string> splitLine = JsonObjectStringToVector(line);

			for (int i = 0; i < splitLine.size(); i++)
			{
				std::cout << "\t" << splitLine[i] << "\n";
			}
		}
	}
	else
	{
		std::cout << "\tUnable to open file\n";
	}
}

//Main-----------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	PartABinaryFileOutputInput();
	PartBSimpleTextFileInputWithSplit();
	PartCReadingJSONFiles();
}
