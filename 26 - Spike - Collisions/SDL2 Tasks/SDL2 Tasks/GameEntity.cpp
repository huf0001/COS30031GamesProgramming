#include "GameEntity.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

bool GameEntity::GetActive()
{
	return active;
}

void GameEntity::SetActive(bool value)
{
	active = value;
}

bool GameEntity::GetColliding()
{
	return colliding;
}

void GameEntity::SetColliding(bool value)
{
	collidingLastFrame = colliding;
	colliding = value;
}

bool GameEntity::GetCollidingLastFrame()
{
	return collidingLastFrame;
}

GameEntity* GameEntity::GetParent()
{
	return parent;
}

void GameEntity::SetParent(GameEntity* value)
{
	pos = GetPos(world) - parent->GetPos(world);
	parent = value;
}

Vector2 GameEntity::GetPos(SPACE space)
{
	if (space == local || parent == NULL)
	{
		return pos;
	}

	return parent->GetPos(world) + RotateVector(pos, parent->GetRotation(local));
}

void GameEntity::SetPos(Vector2 value)
{
	pos = value;
}

float GameEntity::GetRotation(SPACE space)
{
	if (space == local || parent == NULL)
	{
		return rotation;
	}

	return parent->GetRotation(world) + rotation;
}

void GameEntity::SetRotation(float value)
{
	rotation = value;

	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}
	else if (rotation < 0.0f)
	{
		rotation += 360.0f;
	}
}

//Constructors---------------------------------------------------------------------------------------------------------------------------------------

GameEntity::GameEntity(Vector2 pos)
{
	GameEntity(pos.x, pos.y);
}

GameEntity::GameEntity(float x, float y)
{
	pos.x = x;
	pos.y = y;
	rotation = 0.0f;
	active = true;
	parent = NULL;
	colliding = false;
	collidingLastFrame = false;
}

//Destructor-----------------------------------------------------------------------------------------------------------------------------------------

GameEntity::~GameEntity()
{

}

//Public Methods-------------------------------------------------------------------------------------------------------------------------------------

void GameEntity::Update()
{

}

void GameEntity::Render()
{

}

