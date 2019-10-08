// Task 2 Demo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//Includes/Using---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "pch.h"
#include <iostream>
#include <string>
#include <array>
#include <stdio.h> //NULL
#include <stdlib.h> //srand, rand
#include <time.h> //time
#include <vector>
#include <sstream>
#include <iterator>

using namespace std;

//Classes - TestClass----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
###7. Declare a simple class that has at least one private variable,
one public variable, and one public method. Create an instance of
the class, and demonstrate it’s use.
 */
class TestClass
{
	//TestClass Private fields-----------------------------------------------------------------------------------------------------------------------
private: 
	int privateA;

	//TestClass Public fields------------------------------------------------------------------------------------------------------------------------
public:
	int publicB;

	//TestClass Public "properties"------------------------------------------------------------------------------------------------------------------

	int getPrivateA()
	{
		return privateA;
	}
	void setPrivateA(int value)
	{
		privateA = value;
	}

	//TestClass Setup methods------------------------------------------------------------------------------------------------------------------------

	//Constructor
	TestClass(int a, int b)
	{
		privateA = a;
		publicB = b;
	}

	//TestClass General methods----------------------------------------------------------------------------------------------------------------------

	//Multiplies privateA by publicB
	int ATimesB()
	{
		return privateA * publicB;
	}

};

//Loose Methods - General------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
	1. Create a function that accepts at least two values, prints the values to screen, and
	returns nothing. Call this from your main.
 */
void PrintValues(int a, int b)
{
	cout << "1: Print Values. A: " << a << ". B: " << b << ".\n" << endl;
}

/*
	2. Create a function that accepts one value, alters it, and 
	returns it (simple value). Call this function from main, and 
	print the returned value.
 */
int AlterValue(int a)
{
	return a * 2;
}

/*
	4. Create a function that uses a for loop to print all odd numbers
	between 0 and 20 on a single text line of text output, formatted
	with spaces. Call this from main.
 */
void PrintOddNumbersFromOneToTwenty()
{
	string oneToTwentyOdds = "4: Odd numbers from 1 to 20: ";

	for (int i = 1; i <= 20; i += 2)
	{
		if (i < 19)
		{
			oneToTwentyOdds += std::to_string(i) + ", ";
		}
		else
		{
			oneToTwentyOdds += std::to_string(i) + ".\n";
		}
	}

	cout << oneToTwentyOdds << endl;
}

/*
	5. Create a function that creates a 1 dimensional array of 5 
	integers, then fill the array with random int values, print the
	contents of the array to the screen. Call from main.
 */
void RandomIntArray()
{
	array<int, 5> randomIntValues;
	srand(time(NULL));

	cout << "5: Print 5 Random Integers from Array." << endl;


	for (int i = 0; i < randomIntValues.size(); i++)
	{
		randomIntValues[i] = rand() % 100 + 1;
		cout << "randomIntValues[" << i << "]: " << randomIntValues[i] << "." << endl;
	}

	cout << endl;
}

//Loose Methods - Main---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{

	//Part 1
	PrintValues(3, 5);


	//Part 2
	int n = 4;
	cout << "2: Print Altered Value. Raw value: " << n << ". Altered value: " << AlterValue(n) << ".\n" << endl;


	//Part 3
	/*
		3. Declare a pointer to a variable, and demonstrate the 
		setting and reading of the value in the variable using the
		pointer.
	 */
	int * nPtr = &n;
	cout << "3: Demonstrate reading & setting of a variable via a pointer." << endl;
	cout << "Starting value of n (read from n): " << n << "." << endl;
	cout << "Memory address of n (read from nPtr): " << nPtr << "." << endl;
	cout << "Starting value of n (read from nPtr): " << * nPtr << "." << endl;
	* nPtr *= 2;
	cout << "Ending value of n (set from nPtr, read from n): " << n << ".\n" << endl;


	//Part 4
	PrintOddNumbersFromOneToTwenty();


	//Part 5
	RandomIntArray();


	//Part 6
/*
	6. Split the line of text, such as “this has spaces in it”,
	by spaces, and show each part to screen.
 */
	cout << "6: Split 'this has spaces in it' by spaces." << endl;

	string text = "this has spaces in it";
	istringstream iss(text);
	istream_iterator<string> beg(iss), end;
	vector<string> words(beg, end);

	for (int i = 0; i < words.size(); i++)
	{
		cout << "words[" << i << "]: " << words[i] << endl;
	}

	cout << endl;


	//Part 7
	TestClass test = TestClass(4, 3);
	
	cout << "7: Create and use a simple class. Created TestClass(a=4,b=3)." << endl;
	cout << "privateA (accessed through getPrivateA()): " << test.getPrivateA() << ". publicB: " 
		<< test.publicB << ". Output of ATimesB(): " << test.ATimesB() << "." << endl;

	test.setPrivateA(test.getPrivateA() + 1);
	test.publicB++;

	cout << "privateA (changed through setPrivateA()): " << test.getPrivateA() << ". publicB (changed): "
		<< test.publicB << ". New output of ATimesB(): " << test.ATimesB() << "." << endl;
}

