// Lab11FileInputOutput.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

//Class Definition-----------------------------------------------------------------------------------------------------------------------------------

struct CompoundType
{
public:
	char character;
	int integer;
	float floatingPointNumber;

	CompoundType();
	void Print();
};

//Class Implementation-------------------------------------------------------------------------------------------------------------------------------

//Constructor--------------------------------------------------------------------------------------

CompoundType::CompoundType()
{
	
}

void CompoundType::Print()
{
	std::cout << "Printing CompoundType";
	std::cout << "\n";
	std::cout << "\n\tCharacter: " << character;
	std::cout << "\n\tInteger: " << integer;
	std::cout << "\n\tFloating Point Number: " << floatingPointNumber;
	std::cout << "\n";
}

//Lab Section Methods--------------------------------------------------------------------------------------------------------------------------------

void PartABinaryFileOutputInput()
{
	CompoundType test = CompoundType();

	test.character = 'c';
	test.integer = 8345;
	test.floatingPointNumber = 865.00585;

	test.Print();

	//TODO: open binary file in write mode


	//TODO: write values of CompoundType to file


	//TODO: close binary file


}

void PartBSimpleTextFileInputWithSplit()
{
	
}

void PartCReadingJSONFiles()
{
	
}

//Main-----------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
    std::cout << "<<< Part A - Binary File Output / Input >>>" << std::endl;
	std::cout << std::endl;
	PartABinaryFileOutputInput();

	std::cout << std::endl;
    std::cout << "<<< Part B - Simple Text File Input with Split >>>" << std::endl;
	std::cout << std::endl;
	PartBSimpleTextFileInputWithSplit();

	std::cout << std::endl;
    std::cout << "<<< Part C - Reading JSON Files >>>" << std::endl;
	std::cout << std::endl;
	PartCReadingJSONFiles();
}
