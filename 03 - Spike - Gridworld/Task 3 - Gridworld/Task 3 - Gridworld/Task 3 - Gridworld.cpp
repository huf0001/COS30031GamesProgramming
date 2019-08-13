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

class Vector2Int
{
public:
	int x;
	int y;

	Vector2Int(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
};

void Render(char world[8][8], int size, Vector2Int pos, string output)
{
	for (int j = 0; j < size; j++)
	{
		for (int i = 0; i < size; i++)
		{
			if (i == pos.x && j == pos.y)
			{
				cout << "P";
			}
			else
			{				
				cout << world[i][j];
			}
		}

		cout << endl;
	}

	cout << "\n" << output << endl;
}

void ConvertToUppercase(string * s)
{
	string result = * s;
	transform(result.begin(), result.end(), result.begin(), ::toupper);
	* s = result;
}

void ConvertToLowercase(string * s)
{
	string result = * s;
	transform(result.begin(), result.end(), result.begin(), ::tolower);
	* s = result;
}

void Input(string * input)
{
	cin >> * input;
	ConvertToUppercase(input);
}

string MoveTo(bool * finished, char world[8][8], int size, Vector2Int& currentPos, string direction, Vector2Int& newPos)
{
	if (newPos.x < 0 || newPos.x > size || newPos.y < 0 || newPos.y > size)
	{
		return "You cannot move " + direction + ", there's nothing there.";
	}

	if (world[newPos.x][newPos.y] == '#')
	{
		return "You cannot move " + direction + ", that's a wall.";
	}
	
	currentPos = newPos;
	string result = "You moved " + direction + ".\n";

	switch (world[newPos.x][newPos.y])
	{
		case 'G':
			*finished = true;
			result += "You found gold. You WIN!\nGAME OVER!";
			break;
		case 'D':
			*finished = true;
			result += "That's a pit with spikes. Aaaaaaannnd you DIED.\nGAME OVER!";
			break;
		default:
			break;
	}

	return result;
}

string GetAvailableDirections(char world[8][8], int size, Vector2Int& pos)
{
	string result;
	
	if (pos.y + 1 < size && world[pos.x][pos.y + 1] != '#')
	{
		result += "North (N)";
	}

	if (pos.y - 1 > 0 && world[pos.x][pos.y - 1] != '#')
	{
		if (result.length() > 0)
		{
			result += ", ";
		}

		result += "South (S)";
	}

	if (pos.x + 1 < size && world[pos.x + 1][pos.y] != '#')
	{
		if (result.length() > 0)
		{
			result += ", ";
		}

		result += "East (E)";
	}

	if (pos.x - 1 > 0 && world[pos.x - 1][pos.y] != '#')
	{
		if (result.length() > 0)
		{
			result += ", ";
		}

		result += "West (W)";
	}

	if(result.length() == 0)
	{
		result = "nowhere . . . hmm, that's not right . . . ";
	}

	return result;
}

void Update(bool * finished, string input, char world[8][8], int size, Vector2Int& pos, string * output)
{
	if (input.length() == 1)
	{
		Vector2Int newPos = Vector2Int(pos.x, pos.y);
		switch (input[0])
		{

			//	/*
//	Char world corresponds to (when seen from player's perspective):
//	########	N
//	#G D#D #   W E
//	#   #  #	S
//	### # D#
//	#   #  #
//	# #### #
//	#      #
//	########
//*/
//
//	char world[8][8] =
//	{
//		{'#', '#', '#', '#', '#', '#', '#', '#'},	W
//		{'#', 'G', ' ', '#', ' ', ' ', ' ', '#'},  N S
//		{'#', ' ', ' ', '#', ' ', '#', ' ', '#'},	E
//		{'#', 'D', ' ', ' ', ' ', '#', ' ', '#'},
//		{'#', '#', '#', '#', '#', '#', ' ', '#'},
//		{'#', 'D', ' ', ' ', ' ', '#', ' ', '#'},
//		{'#', ' ', ' ', 'D', ' ', ' ', ' ', '#'},
//		{'#', '#', '#', '#', '#', '#', '#', '#'}
//	};

			case 'Q':
				*finished = true;
				*output = "Goodbye";
				return;
			case 'N':
				newPos = Vector2Int(pos.x, pos.y - 1);
				*output = MoveTo(finished, world, size, pos, "north", newPos);
				break;
			case 'S':
				newPos = Vector2Int(pos.x, pos.y + 1);
				*output = MoveTo(finished, world, size, pos, "south", newPos);
				break;
			case 'E':
				newPos = Vector2Int(pos.x, pos.x + 1);
				*output = MoveTo(finished, world, size, pos, "east", newPos);
				break;
			case 'W':
				newPos = Vector2Int(pos.x, pos.x - 1);
				*output = MoveTo(finished, world, size, pos, "west", newPos);
				break;
			default:
				*output = "That is not a valid input key.";
				break;
		}

		if (*finished)
		{
			return;
		}
	}
	else
	{
		*output = "That is not valid input. Only enter one key at a time.";
	}

	*output += "\nYou can move " + GetAvailableDirections(world, size, pos) + ": ";
}

int main()
{
	bool finished = false;
	string input;
	string output;
	int size = 8;
	Vector2Int pos = Vector2Int(2, 7);

	/*
		Char world corresponds to (when seen from player's perspective):
		########	N
		#G D#D #   W E
		#   #  #	S
		### # D#
		#   #  #
		# #### #
		#      #
		########
	*/

	//	   W
	//	  N S
	//	   E
	char world[8][8] = 
	{
		{'#', '#', '#', '#', '#', '#', '#', '#'},
		{'#', 'G', ' ', '#', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', '#', ' ', '#', ' ', '#'},
		{'#', 'D', ' ', ' ', ' ', '#', ' ', '#'},
		{'#', '#', '#', '#', '#', '#', ' ', '#'},
		{'#', 'D', ' ', ' ', ' ', '#', ' ', '#'},
		{'#', ' ', ' ', 'D', ' ', ' ', ' ', '#'},
		{'#', '#', '#', '#', '#', '#', '#', '#'}
	};

	cout << "Welcome to GridWorld!\n" << endl;
	Render(world, size, pos, output);
	cout << "Inputs:" << endl;
	cout << "\tN: move North" << endl;
	cout << "\tS: move South" << endl;
	cout << "\tE: move East" << endl;
	cout << "\tW: move West" << endl;
	cout << "\tQ: Quit" << endl;
	cout << "Begin" << endl;
	cout << "You can move North (N): ";
	
	while (!finished)
	{
		Input(&input);
		Update(&finished, input, world, size, pos, &output);
		Render(world, size, pos, output);
	};

	cout << "Finished" << endl;
}
