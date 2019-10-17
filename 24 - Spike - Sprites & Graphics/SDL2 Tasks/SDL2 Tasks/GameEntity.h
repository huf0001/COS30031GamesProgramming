#include "pch.h"

#ifndef GAMEENTITY_H
#define GAMEENTITY_H

class GameEntity
{
private:
	//Private Fields
	Vector2 pos;
	float rotation;
	bool active;
	GameEntity* parent;

	//Private Methods

public:
	//Enums
	enum SPACE
	{
		local = 0,
		world = 1
	};

	//Public Properties
	bool GetActive();
	void SetActive(bool value);
	GameEntity* GetParent();
	void SetParent(GameEntity* value);
	Vector2 GetPos(SPACE space = world);
	void SetPos(Vector2 value);
	float GetRotation(SPACE space = world);
	void SetRotation(float value);

	//Constructors
	GameEntity(float x = 0.0f, float y = 0.0f);
	GameEntity(Vector2 pos);

	//Destructor
	~GameEntity();

	//Public Methods
	void Update();
	void Render();
};

#endif
