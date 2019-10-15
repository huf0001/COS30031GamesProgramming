#include "pch.h"

int main(int args, char* argv[])
{	
	GameManager::Instance()->Run();
	GameManager::Release();
	return 0;
}