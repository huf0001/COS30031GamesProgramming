#include "pch.h"

#include "Player.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

//std::string Player::GetName()
//{
//	return name;
//}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

Player::Player(std::string id, std::string name) : GameObject(id, name)
{
	/*this->name = name;*/
	AddComponent((Component*) new Container((GameObject*)this, true, true));
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------
