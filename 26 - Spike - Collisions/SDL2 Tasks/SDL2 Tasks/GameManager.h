#include "pch.h"

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

class GameManager
{
private:
	//Private Constants
	const int FRAME_RATE = 60;

	//Private Fields
	static GameManager* instance;
	AssetManager* assetManager;
	AudioManager* audioManager;
	Graphics* graphics;
	std::map<std::string, GameEntity*> gameEntities;
	std::vector<std::string> renderOrder;
	Timer* timer;
	SDL_Event events;
	bool running;

	std::vector<Shape*> shapes;
	Shape::ShapeType currentShapes;
	Shape* fixedShape;
	Shape* movingShape;
	float timeSinceMove;
	
	//Constructor
	GameManager();

	//Destructor
	~GameManager();

	//Private Methods

protected:
	//Protected Fields

	//Protected Methods

public:
	//Public Properties
	static GameManager* Instance();

	//Public Methods
	void Run();
	void Input();
	void Update();
	void MoveShape(Shape* shape);
	void CheckCircleCollision(Shape* a, Shape* b);
	void CheckRectangleCollision(Shape* a, Shape* b);
	void UpdateColour(Shape* shape);
	void Render();
	void ToggleSprite(Texture* sprite);
	static void Release();
};

#endif
