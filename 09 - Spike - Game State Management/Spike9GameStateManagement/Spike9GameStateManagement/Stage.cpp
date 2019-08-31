#include "pch.h"

#include "Stage.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

std::string Stage::GetName()
{
	return name;
}

void Stage::SetName(std::string value)
{
	name = value;
}

bool Stage::GetSetup()
{
	return setup;
}

void Stage::SetSetup(bool value)
{
	setup = value;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

Stage::Stage()
{
	setup = false;
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------
