#include "GameManager.h"

//Public Properties----------------------------------------------------------------------------------------------------------------------------------

GameManager* GameManager::instance = NULL;

GameManager* GameManager::Instance()
{
	if (!instance)
	{
		instance = new GameManager();
	}

	return instance;
}

//Constructor----------------------------------------------------------------------------------------------------------------------------------------

GameManager::GameManager()
{
	running = true;
	assetManager = AssetManager::Instance();
	audioManager = AudioManager::Instance();
	graphics = Graphics::Instance();
	timer = Timer::Instance();
	std::srand(std::time(0));

	if (!Graphics::GetInitialised())
	{
		running = false;
	}

	//Background
	gameEntities["background"] = new Texture("LyokoBinaryWall.png");
	gameEntities["background"]->SetPos(Vector2(Graphics::GetScreenWidth() * 0.5f, Graphics::GetScreenHeight() * 0.5f));
	((Texture*)gameEntities["background"])->SetWidth(Graphics::GetScreenWidth());
	((Texture*)gameEntities["background"])->SetHeight(Graphics::GetScreenHeight());
	renderOrder.push_back("background");

	//Sprites
	gameEntities["sprite3"] = new Texture("SpriteSheet.png", 272, 0, 136, 190);
	gameEntities["sprite3"]->SetPos(Vector2(100, 0));
	gameEntities["sprite3"]->SetActive(false);
	renderOrder.push_back("sprite3");
	gameEntities["sprite2"] = new Texture("SpriteSheet.png", 136, 0, 136, 190);
	gameEntities["sprite2"]->SetPos(Vector2(100, 0));
	gameEntities["sprite2"]->SetActive(false);
	renderOrder.push_back("sprite2");
	gameEntities["sprite1"] = new Texture("SpriteSheet.png", 0, 0, 136, 190);
	gameEntities["sprite1"]->SetPos(Vector2(100, 0));
	gameEntities["sprite1"]->SetActive(false);
	renderOrder.push_back("sprite1");

	//Rectangles
	gameEntities["fixedRect"] = new Rectangle(300, 300, Graphics::Instance()->GetColour("green"), true, Graphics::GetScreenWidth() * 0.5f, Graphics::GetScreenHeight() * 0.5f);
	renderOrder.push_back("fixedRect");
	shapes.push_back((Shape*)gameEntities["fixedRect"]);
	gameEntities["movingRect"] = new Rectangle(100, 100, Graphics::Instance()->GetColour("green"), true, Graphics::GetScreenWidth() * 0.5f + 100, Graphics::GetScreenHeight() * 0.5f + 100);
	renderOrder.push_back("movingRect");
	shapes.push_back((Shape*)gameEntities["movingRect"]);

	////Used childRect to test that axis aligned rotation of rectangles was working with regards to GetBottomLeft() and GetTopRight()
	//gameEntities["childRect"] = new Rectangle(100, 100, Graphics::Instance()->GetColour("blue"), true, Graphics::GetScreenWidth() * 0.5f, Graphics::GetScreenHeight() * 0.5f);
	//renderOrder.push_back("childRect");
	//shapes.push_back((Shape*)gameEntities["childRect"]);
	//gameEntities["childRect"]->SetParent(gameEntities["movingRect"]);

	//Circles
	gameEntities["fixedCircle"] = new Circle(150, Graphics::Instance()->GetColour("green"), true, Graphics::GetScreenWidth() * 0.5f, Graphics::GetScreenHeight() * 0.5f);
	renderOrder.push_back("fixedCircle");
	shapes.push_back((Shape*)gameEntities["fixedCircle"]);
	gameEntities["fixedCircle"]->SetActive(false);
	gameEntities["movingCircle"] = new Circle(50, Graphics::Instance()->GetColour("green"), true, Graphics::GetScreenWidth() * 0.5f + 100, Graphics::GetScreenHeight() * 0.5f + 100);
	renderOrder.push_back("movingCircle");
	shapes.push_back((Shape*)gameEntities["movingCircle"]);
	gameEntities["movingCircle"]->SetActive(false);

	timeSinceMove = 0;
	currentShapes = Shape::ShapeRectangle;
	fixedShape = (Shape*)gameEntities["fixedRect"];
	movingShape = (Shape*)gameEntities["movingRect"];
	moveShapes = true;
}

//Destructor-----------------------------------------------------------------------------------------------------------------------------------------

GameManager::~GameManager()
{
	AssetManager::Release();
	assetManager = NULL;
	AudioManager::Release();
	audioManager = NULL;
	Graphics::Release();
	graphics = NULL;
	
	for (auto pair : gameEntities)
	{
		if (pair.second != NULL)
		{
			delete pair.second;
			pair.second = NULL;
		}
	}

	gameEntities.clear();

	Timer::Release();
	timer = NULL;
}

//Methods--------------------------------------------------------------------------------------------------------------------------------------------

void GameManager::Run()
{
	while (running)
	{
		Input();
		Update();
		Render();		
	}

	Release();
}

void GameManager::Input()
{
	while (SDL_PollEvent(&events) != 0)
	{
		switch (events.type)
		{
		case SDL_QUIT:
			running = false;
			break;
		case SDL_KEYDOWN:
			switch (events.key.keysym.scancode)
			{
				//Quit
			case SDL_SCANCODE_ESCAPE:
				running = false;
				break;

				//Background
			case SDL_SCANCODE_0:
				gameEntities["background"]->SetActive(!gameEntities["background"]->GetActive());
				break;

				//Images
			case SDL_SCANCODE_1:
				ToggleSprite((Texture*)gameEntities["sprite1"]);
				break;
			case SDL_SCANCODE_2:
				ToggleSprite((Texture*)gameEntities["sprite2"]);
				break;
			case SDL_SCANCODE_3:
				ToggleSprite((Texture*)gameEntities["sprite3"]);
				break;

				//Music
			case SDL_SCANCODE_8:
				audioManager->HandleMusic("FogOfWar1.mp3");
				break;
			case SDL_SCANCODE_9:
				audioManager->HandleMusic("Var_3.mp3");
				break;

				//SFX
			case SDL_SCANCODE_5:
				audioManager->PlaySFX("BuildingDestroyed.wav", 0, 1);
				break;
			case SDL_SCANCODE_6:
				audioManager->PlaySFX("MortarHit.wav", 0, 2);
				break;
			case SDL_SCANCODE_7:
				audioManager->PlaySFX("MortarLaunch.wav", 0, 3);
				break;

			//Render circles or rectangles?
			case SDL_SCANCODE_C:
				if (currentShapes != Shape::ShapeCircle)
				{
					currentShapes = Shape::ShapeCircle;
					fixedShape = (Shape*)gameEntities["fixedCircle"];
					movingShape = (Shape*)gameEntities["movingCircle"];

					for (Shape* s : shapes)
					{
						if (s->GetType() == currentShapes && !s->GetActive())
						{
							s->SetActive(true);
							s->SetColour(graphics->GetColour("green"));
							s->SetColliding(false);
						}
						else if (s->GetType() != currentShapes && s->GetActive())
						{
							s->SetActive(false);
						}
					}
				}

				break;

			case SDL_SCANCODE_R:
				if (currentShapes != Shape::ShapeRectangle)
				{
					currentShapes = Shape::ShapeRectangle;
					fixedShape = (Shape*)gameEntities["fixedRect"];
					movingShape = (Shape*)gameEntities["movingRect"];

					for (Shape* s : shapes)
					{
						if (s->GetType() == currentShapes && !s->GetActive())
						{
							s->SetActive(true);
							s->SetColour(graphics->GetColour("green"));
							s->SetColliding(false);
						}
						else if (s->GetType() != currentShapes && s->GetActive())
						{
							s->SetActive(false);
						}
					}
				}

				break;

			//Move shapes?
			case SDL_SCANCODE_SPACE:
				moveShapes = !moveShapes;
				break;
			}

			break;
		}
	}
}

void GameManager::Update()
{
	//Update timer
	timer->Update();

	//Move moving shape
	if (moveShapes)
	{
		MoveShape(movingShape);
	}

	//Check collisions
	if (currentShapes == Shape::ShapeCircle)
	{
		CheckCircleCollision(fixedShape, movingShape);
	}
	else
	{
		CheckRectangleCollision(fixedShape, movingShape);
	}

	UpdateColour(fixedShape);
	UpdateColour(movingShape);
}

void GameManager::MoveShape(Shape* shape)
{
	timeSinceMove += timer->GetDeltaTime();

	if (timeSinceMove > 500)
	{
		timeSinceMove -= 500;
		shape->SetPos(Vector2(std::rand() % Graphics::GetScreenWidth(), std::rand() % Graphics::GetScreenHeight()));
		shape->SetRotation(std::rand() % 360);
	}
}

void GameManager::CheckCircleCollision(Shape* a, Shape* b)
{
	Circle* circleA = (Circle*)a;
	Circle* circleB = (Circle*)b;

	bool colliding = Distance(circleB->GetPos(GameEntity::world), circleA->GetPos(GameEntity::world)) <= circleB->GetRadius() + circleA->GetRadius();

	circleA->SetColliding(colliding);
	circleB->SetColliding(colliding);
}

void GameManager::CheckRectangleCollision(Shape* a, Shape* b)
{
	Rectangle* rectA = (Rectangle*)a;
	Rectangle* rectB = (Rectangle*)b;
	bool colliding = false;

	colliding = CheckAxisAlignedRectangleCollision(rectA, rectB);

	a->SetColliding(colliding);
	b->SetColliding(colliding);
}

bool GameManager::CheckAxisAlignedRectangleCollision(Rectangle* a, Rectangle* b)
{
	int aBottom = a->GetBottomLeft(GameEntity::world).y;
	int aTop = a->GetTopRight(GameEntity::world).y;
	int aLeft = a->GetBottomLeft(GameEntity::world).x;
	int aRight = a->GetTopRight(GameEntity::world).x;
	int bBottom = b->GetBottomLeft(GameEntity::world).y;
	int bTop = b->GetTopRight(GameEntity::world).y;
	int bLeft = b->GetBottomLeft(GameEntity::world).x;
	int bRight = b->GetTopRight(GameEntity::world).x;

	if (aTop < bBottom)
	{
		return false;
	}
	if (aBottom > bTop)
	{
		return false;
	}
	if (aLeft > bRight)
	{
		return false;
	}
	if (aRight < bLeft)
	{
		return false;
	}

	return true;
}

void GameManager::UpdateColour(Shape* shape)
{
	if (shape->GetColliding())
	{
		if (!shape->GetCollidingLastFrame())
		{
			shape->SetColour(Graphics::Instance()->GetColour("red"));
		}
	}
	else
	{
		if (shape->GetCollidingLastFrame())
		{
			shape->SetColour(Graphics::Instance()->GetColour("green"));
		}
	}
}

void GameManager::Render()
{
	if (timer->GetDeltaTime() >= 1.0f / FRAME_RATE)
	{
		graphics->ClearBackBuffer();

		for (int i = 0; i < renderOrder.size(); i++)
		{
			if (gameEntities[renderOrder[i]]->GetActive())
			{
				gameEntities[renderOrder[i]]->Render();
			}
		}

		graphics->Render();
		timer->Reset();
	}
}

void GameManager::ToggleSprite(Texture* sprite)
{
	sprite->SetActive(!sprite->GetActive());

	if (sprite->GetActive())
	{
		sprite->SetPos(Vector2(std::rand() % Graphics::GetScreenWidth(), std::rand() % Graphics::GetScreenHeight()));
	}
}

void GameManager::Release()
{
	delete instance;
	instance = NULL;
}
