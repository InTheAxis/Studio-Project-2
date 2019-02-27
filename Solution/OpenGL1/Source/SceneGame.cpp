#include "SceneGame.h"
#include <cmath>


SceneGame::SceneGame()
{

}

SceneGame::~SceneGame()
{
}


void SceneGame::InitDerived()
{
	std::cout << "Generating OBJs\n";
	
	//timer,button and cursor
	resumeButton.Init("resume", "OBJ//LevelsButton.obj", "Image//levels1.tga", Vector3(20, 15, -10), Vector3(0, 0, 0), Vector3(1, 1, 0));
	resumeText.Init("level1text", "OBJ//LevelsButton.obj", "Image//resumeText.tga", Vector3(20, 15, -9), Vector3(0, 0, 0), Vector3(20, 20, 0));
	exitButton.Init("exit", "OBJ//LevelsButton.obj", "Image//levels1.tga", Vector3(40, 15, -10), Vector3(0, 0, 0), Vector3(1, 1, 0));
	exitText.Init("level3text", "OBJ//LevelsButton.obj", "Image//exitText.tga", Vector3(40, 15, -9), Vector3(0, 0, 0), Vector3(20, 20, 0));
	mouse.Init("mouse", MeshBuilder::GenerateCube(Color(1, 0, 0)), "", Vector3(orthSize.x * 0.5f, orthSize.y * 0.5f, 10), Vector3(0, 0, 0), Vector3(1, 1, 0));

	//speedometer
	needle.Init("Needle", "OBJ//Needle.obj", "Image//Red.tga", Vector3(50, 1, 0), Vector3(-3, 0, 0), Vector3(1.5, 1.6, 1));
	needle.SetMaterial(shiny);

	//AI
	ai.Init("ai", "OBJ//taxiNoWheels.obj", "Image//Purple.tga");
	ai.CreateRigidBody(Vector3(0, 0, 10), 1200, 0.1f, 0.09f);
	ai.SetMaterial(shiny);
	ai.DefineRect2DCollider(Vector3(2, 2, 2));
	ai.GetPaint()->SetPaintColor(Color(1, 0, 1));
	ai.SetTranslate(Vector3(0, 0.3f, 40));
	ai.SetStats(20000, 1111, 7000, 0.05);

	//car
	car = static_cast<Car*>(GetDontDestroyGameObject("car"));
	//reset transforms
	car->SetTranslate(Vector3(0, 0.3f, 0));
	car->SetRotate(Vector3(0, 0, 0));
	car->SetScale(Vector3(1, 1, 1));
	car->CreateRigidBody(Vector3(0, 0, 10), 1200, 0.1f, 0.09f);
	car->DefineRect2DCollider(Vector3(2, 2, 2));
	car->SetStats(20000, 1111, 7000, 0.05);
	car->AddChild(&particleEffect); //adding particle effects to car

	//PowerUps,Particle Effects
	speedboost.Init("speedboost", MeshBuilder::GenerateCube(Color(0, 0, 0)), "", Vector3(0, 0.5, 5), Vector3(0, 0, 0), Vector3(1, 1, 1));
	particleEffect.Init("smoke", "OBJ//cloud.obj", "Image//cloud.tga", Vector3(0, 0.5f, car->GetTranslate().z-1.5f), Vector3(0, 0, 0), Vector3(0.1f, 0.1f, 0.1f));
	sprayBoost.Init("SprayBoost", MeshBuilder::GenerateCube(Color(1, 0, 0)), "", Vector3(0, 0.5, 15), Vector3(0, 0, 0), Vector3(1, 1, 1));

	//map
	floor.Init("floor", "OBJ//LowPolyFloor.obj", "Image//ground.tga", Vector3(0, 0, 0));
	floor.AddTexture("Image//ground-plain.tga");
	paintLayer.Init("paintLayer", "OBJ//HighPolyFloor.obj", "", Vector3(0, 0.25f, 0));
	
	//walls
	//shld just use the same mesh... -terence
	frontWall.Init("Border", "OBJ//Wall.obj","Image//WallTex.tga");
	frontWall.DefineRect2DCollider(Vector3(1, 1, 115));
	frontWall.SetTranslate(Vector3(0, 0, 53.75));
	frontWall.SetRotate(Vector3(0, 90, 0));
	frontWall.SetScale(Vector3(1.1f, 0.5f, 1.1f));
	frontWall.SetMaterial(bright);

	leftWall.Init("Border", "OBJ//Wall.obj", "Image//WallTex.tga");
	leftWall.DefineRect2DCollider(Vector3(1, 1, 115));
	leftWall.SetTranslate(Vector3(-53.75f, 0.f, 0.f));
	leftWall.SetScale(Vector3(1.1f, 0.5f, 1.1f));
	leftWall.SetMaterial(bright);

	rightWall.Init("Border", "OBJ//Wall.obj", "Image//WallTex.tga");
	rightWall.DefineRect2DCollider(Vector3(1, 1, 115));
	rightWall.SetTranslate(Vector3(53.75, 0, 0));
	rightWall.SetRotate(Vector3(0, 180, 0));
	rightWall.SetScale(Vector3(1.1, 0.5, 1.1));
	rightWall.SetMaterial(bright);

	backWall.Init("Border", "OBJ//Wall.obj", "Image//WallTex.tga");
	backWall.DefineRect2DCollider(Vector3(1, 1, 115));
	backWall.SetTranslate(Vector3(0, 0, -53.75));
	backWall.SetRotate(Vector3(0, 270, 0));
	backWall.SetScale(Vector3(1.1, 0.5, 1.1));
	backWall.SetMaterial(bright);

	std::cout << "Done Generating OBJs\n";

	std::cout << "Generating grid for level\n";
	level.GenerateGrid(paintLayer.GetVBO());
	std::cout << "Done Generating grid\n";

	//buttons
	allButtons.push_back(&resumeButton);
	allButtons.push_back(&exitButton);
	

	std::cout << "Generating map based on grid\n";
	//storing positions that are not empty
	map.SetOccupied(&level, ai.GetTranslate());
	map.SetOccupied(&level, car->GetTranslate());
	map.SetOccupied(&level, speedboost.GetTranslate());
	map.SetOccupied(&level, sprayBoost.GetTranslate());
	//generating map
	while (map.GetObjectCount() < sqrt((level_chunk.GetChunkCount()))) //gets a value depending on chunk size
	{
		if (map.GenerateObj(&level)) //if random area is not occupied
		{
			int x = Math::RandIntMinMax(1, 4);
			int y = Math::RandIntMinMax(1, 4); //random to choose the generated object
			Objects.push_back(Collidable());
			Objects[map.GetObjectCount() - 1].Init("genObj", "OBJ//Building.obj", map.GetObjTex(x)); 
			Objects[map.GetObjectCount() - 1].SetMaterial(dull);
			Objects[map.GetObjectCount() - 1].DefineRect2DCollider(Vector3(5,5,5));
			Objects[map.GetObjectCount() - 1].SetTranslate(map.GetLocation());
			Objects[map.GetObjectCount() - 1].SetRotate(map.GetRandRotate(y));
			Objects[map.GetObjectCount() - 1].SetScale(map.GetRandScale(y));
		}
	}
	std::cout << "Done Generating map\n";

	//passing window range and buttons for cursor
	mouse.SetOrthSize(orthSize);
	mouse.SetAllButton(allButtons);

	//update non-moving colliders
	frontWall.UpdateCollider();
	leftWall.UpdateCollider();
	rightWall.UpdateCollider();
	backWall.UpdateCollider();

	for (int i = 0; i < map.GetObjectCount(); i++)
	{
		Objects[i].UpdateCollider();
	}
	
	//misc
	timer = 0;
	speedometerAngle = 0;
	currentCam = FIXED_FOLLOWER;
}

void SceneGame::RenderDerived()
{
	//render colliders for debugging
	if (DEBUG)
	{
		for (int i = 0; i < map.GetObjectCount(); i++)
		{
			RenderObject(Objects[i].GetCollider());
		}
		RenderObject(car->GetCollider());
		RenderObject(ai.GetCollider());
		RenderObject(frontWall.GetCollider());
		RenderObject(backWall.GetCollider());
		RenderObject(leftWall.GetCollider());
		RenderObject(rightWall.GetCollider());
		
	}
	
	//map and transparent paint layer
	RenderObject(&floor);
	RenderObject(&paintLayer);
	RenderObject(&frontWall);
	RenderObject(&rightWall);
	RenderObject(&leftWall);
	RenderObject(&backWall);
	//buildings
	for (int x = 0; x < map.GetObjectCount(); x++)
	{
		RenderObject(&Objects[x]);
	}

	//vehicles
	RenderObject(car);
	RenderObject(&ai);

	//powerups, would loop if there wass more than 2
	if(!speedboost.GetPickedUp())
		RenderObject(&speedboost, false);
	if (!sprayBoost.GetPickedUp())
		RenderObject(&sprayBoost, false);

	//speedometer needle
	RenderObjectOnScreen(&needle, true);
	needle.SetRotate(Vector3(0, 0, -speedometerAngle));
	//speedometer markings
	RenderTextOnScreen(&TEXT, "0", Color(0.8f, 0.8f, 0.8f), 1.2f, 35.f, 0.3f);
	RenderTextOnScreen(&TEXT, "20", Color(0.8f, 0.8f, 0.8f), 1.2f, 35.3f, 2.4f);
	RenderTextOnScreen(&TEXT, "40", Color(0.8f, 0.8f, 0.8f), 1.2f, 36.6f, 3.8f);
	RenderTextOnScreen(&TEXT, "60", Color(0.8f, 0.8f, 0.8f), 1.2f, 38.4f, 5.f);
	RenderTextOnScreen(&TEXT, "80", Color(0.8f, 0.8f, 0.8f), 1.2f, 41.3f, 5.7f);
	RenderTextOnScreen(&TEXT, "100", Color(0.8f, 0.8f, 0.8f), 1.2f, 44.5f, 5.f);
	RenderTextOnScreen(&TEXT, "120", Color(0.8f, 0.8f, 0.8f), 1.2f, 45.5f, 3.8f);
	RenderTextOnScreen(&TEXT, "140", Color(0.8f, 0.8f, 0.8f), 1.2f, 46.7f, 2.4f);
	RenderTextOnScreen(&TEXT, "160", Color(0.8f, 0.8f, 0.8f), 1.2f, 47.3f, 0.3f);

	//resume and exit buttons during pause
	if (this->pause)
	{
		RenderObjectOnScreen(&resumeButton, false);
		RenderObjectOnScreen(&resumeText, false);
		RenderObjectOnScreen(&exitButton, false);
		RenderObjectOnScreen(&exitText, false);
		RenderObjectOnScreen(&mouse, false);
	}

	//timer
	std::string timerString = "Timer: " + std::to_string(TIMER_MAX - (int)std::ceil(timer));
	RenderTextOnScreen(&TEXT, timerString, Color(1, 1, 1), 1, 1, 0.5f);
}

void SceneGame::UpdateDerived(double dt)
{
	if (dt > 1) //skip first frame or any frames < 1fps
		return;

	//move mouse
	mouse.Move(dt);
	mouse.CheckHover();

	if (!pause)
	{
		//Timer
		if(!DEBUG)
			timer += dt;

		//Particle Effects
		if (car->GetEngineForce() > 0)
			particleEffect.ApplyEffect(car,dt);

		//PowerUps
		speedboost.CheckAbsorption(car->GetTranslate());
		speedboost.ApplyEffect(static_cast<GameObject*>(car), dt);

		//car movement
		//Car forward & backward inputs
		if (Application::IsKeyPressed(VK_UP) && car->GetGear() > 0)
			car->MoveForward(1, dt);
		else if (Application::IsKeyPressed(VK_UP) && car->GetGear() == 0)
			car->MoveForward(-1, dt);
		else
			car->MoveForward(0, dt);
		//Car brake input
		if (Application::IsKeyPressed(VK_DOWN))
			car->Brake(true);
		else
			car->Brake(false);
		//Car left & right inputs
		if (Application::IsKeyPressed(VK_LEFT))
			car->MoveRight(-1, dt);
		else if (Application::IsKeyPressed(VK_RIGHT))
			car->MoveRight(1, dt);
		else
			car->MoveRight(0, dt);

		//speedometer
		speedometerAngle = Math::Clamp(car->GetSpeed() / MAX_SPEED * 360.f, 0.f, 180.f); //find ratio and set to 360 base, clamped at 0 and 180

		//ai
		if (ai.CheckToMove())
		{
			ai.SetNewLocation(map.GetDestination(&level, car->GetPaint()->GetPaintColor(), ai.GetTranslate())); //set a new location for ai to move to when its alr reached first destination or beginning of game
		}
		ai.SetNextForward(ai.GetNewLocation()); //updates view vector everytime it moves
		if (!ai.CheckToMove()) //if not at destination
		{
			ai.CalcAngle(); //checks angle to turn
			if (ai.IfTurn()) //if more than 5 degree then turn else dont
			{
				if (ai.GetSpeed() > 5) //brake if u > 5
					ai.Brake(true);
				else
					ai.Brake(false);
				ai.MoveRight(ai.SetDir(), dt); //turn
			}
			ai.MoveForward(1, dt); //move
			Vector3 currPos = ai.GetTranslate(); //save prev pos to check if its stuck at a place
			if (ai.ReDirect(currPos)) //if need to redirect
			{
				if (ai.GetReCount() <= 2) //check if its stuck there constantly
					ai.MoveRight(1, dt); //then change direction for it to turn
				else
					ai.MoveRight(-1, dt); //else turn away from stuck area
			}
		}


		//update car physics
		car->UpdateSuvat(dt);
		car->UpdateRotation(dt);
		//update ai physics
		ai.UpdateSuvat(dt);
		ai.UpdateRotation(dt);

		//update moving colliders
		car->UpdateCollider();
		ai.UpdateCollider();

		//collision checking
		if (_coll->CheckCollision2D(car, &ai))
			_coll->ResolveCollision2D(car, &ai);

		for (int i = 0; i < map.GetObjectCount(); i++)
		{
			if (_coll->CheckCollision2D(car, &Objects[i]))
				_coll->ResolveCollision2D(car, &Objects[i]);

			if (_coll->CheckCollision2D(&ai, &Objects[i]))
				_coll->ResolveCollision2D(&ai, &Objects[i]);
		}

		if (_coll->CheckCollision2D(car, &frontWall))
			_coll->ResolveCollision2D(car, &frontWall);

		if (_coll->CheckCollision2D(car, &backWall))
			_coll->ResolveCollision2D(car, &backWall);

		if (_coll->CheckCollision2D(car, &rightWall))
			_coll->ResolveCollision2D(car, &rightWall);

		if (_coll->CheckCollision2D(car, &leftWall))
			_coll->ResolveCollision2D(car, &leftWall);

		if (_coll->CheckCollision2D(&ai, &frontWall))
			_coll->ResolveCollision2D(&ai, &frontWall);

		if (_coll->CheckCollision2D(&ai, &backWall))
			_coll->ResolveCollision2D(&ai, &backWall);

		if (_coll->CheckCollision2D(&ai, &rightWall))
			_coll->ResolveCollision2D(&ai, &rightWall);

		if (_coll->CheckCollision2D(&ai, &leftWall))
			_coll->ResolveCollision2D(&ai, &leftWall);

		//update follower camera
		if (currentCam == FIXED_FOLLOWER)
			camera[FIXED_FOLLOWER]->Update(dt, car->GetTranslate(), car->GetAngle()); //update camera

		//paint layer for spray boost
		if (!sprayBoost.CheckAbsorption(car->GetTranslate()))
		{
			paintLayer.ChangeColor(&level, car->GetTranslate(), car->GetPaint()->GetPaintColor());
		}
		else
		{
			paintLayer.ChangeColor(&level, car->GetTranslate(), car->GetPaint()->GetPaintColor(), 1.5);
		}
		sprayBoost.ApplyEffect(reinterpret_cast<GameObject*>(&car), dt); //what does this do alex????? -terence, 27/02

		//paintlayer for ai
		paintLayer.ChangeColor(&level, ai.GetTranslate(), ai.GetPaint()->GetPaintColor());

	}
	else //pause
	{
		for (Button* b : allButtons)	//for each button in the vector carry out the function
		{
			b->AnimateButton();
		}

		//changing of scenes
		if (resumeButton.GetOnClickEvent())
		{
			allButtons[0]->SetHover(false);
			resumeButton.SetOnClickEvent(false);
			pause = false;
		}
		if (exitButton.GetOnClickEvent())
		{
			allButtons[1]->SetHover(false);
			exitButton.SetOnClickEvent(false);
			pause = false;
			timer = 0;
			mouse.ResetMousePos();
			RequestChangeScene(1); // START
		}

		if (Application::leftMouseClick)
		{
			for (unsigned int i = 0; i < allButtons.size(); ++i)
			{
				if (allButtons[i]->GetHover())
				{
					allButtons[i]->DoAction();
					break;
				}
			}
		}
	}

	//endgame time

	if (timer >= TIMER_MAX)
	{
		mouse.ResetMousePos();
		RequestDontDestroy(&paintLayer);
		RequestDontDestroy(&floor);
		RequestDontDestroy(static_cast<GameObject*>(&ai));
		RequestChangeScene(4);//change to results scene once it is created
	}
}

void SceneGame::UpdateDerivedBounced(double dt)
{
	if (Application::IsKeyPressed(VK_ESCAPE))//pause,unpause
	{
		pause = !pause;
	}
	if (Application::IsKeyPressed('X')) //Increase gear
	{
		car->SetGear(car->GetGear() + 1);
	}
	if (Application::IsKeyPressed('Z')) //Decrease gear
	{
		car->SetGear(car->GetGear() - 1);
	}
}
