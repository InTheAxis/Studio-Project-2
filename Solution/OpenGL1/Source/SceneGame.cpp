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
	//timer,button and cursor

	resumeButton.Init("resume", "OBJ//LevelsButton.obj", "Image//levels.tga", Vector3(30, 20, 0), Vector3(0, 0, 0), Vector3(1, 1, 0));

	resumeText.Init("level1text", "OBJ//LevelsButton.obj", "Image//levels1Text.tga", Vector3(8, 15, -9), Vector3(0, 0, 0), Vector3(20, 20, 0));

	exitText.Init("level3text", "OBJ//LevelsButton.obj", "Image//levels3Text.tga", Vector3(52, 15, -9), Vector3(0, 0, 0), Vector3(20, 20, 0));

	exitButton.Init("exit", "OBJ//LevelsButton.obj", "Image//levels.tga", Vector3(30, 15, 0), Vector3(0, 0, 0), Vector3(1, 1, 0));
	mouse.Init("mouse", MeshBuilder::GenerateCube(Color(1, 0, 0)), "", Vector3(orthSize.x * 0.5f, orthSize.y * 0.5f, 10), Vector3(0, 0, 0), Vector3(1, 1, 0));

	//AI
	ai.Init("ai", "OBJ//taxi.obj", "Image//Red.tga");
	ai.CreateRigidBody(Vector3(0, 0, 10), 1200, 0.1f, 0.09f);
	ai.SetMaterial(shiny);
	ai.DefineRect2DCollider(Vector3(2, 2, 2));
	ai.SetTranslate(Vector3(0, 0.3, 0));

	//car
	car.Init("car", "OBJ//taxi.obj", "Image//taxi.tga");
	car.CreateRigidBody(Vector3(0, 0, 10), 1200, 0.1f, 0.09f);
	car.SetMaterial(shiny);
	car.DefineRect2DCollider(Vector3(2, 2, 2));
	car.GetPaint()->SetPaintColor(Color(1, 1, 0));
	car.SetTranslate(Vector3(0, 0.3, 0));


	//PowerUps,Particle Effects
	speedboost.Init("speedboost", MeshBuilder::GenerateCube(Color(0, 0, 0)), "", Vector3(0, 0.5, 5), Vector3(0, 0, 0), Vector3(1, 1, 1));
	particleEffect.Init("particleEffect", MeshBuilder::GenerateCube(Color(1, 0, 0)), "", Vector3(0, 0.5, car.GetTranslate().z-1.5), Vector3(0, 0, 0), Vector3(0.1, 0.1, 0.1));

	//map
	floor.Init("floor", "OBJ//LowPolyFloor.obj", "Image//color2.tga", Vector3(0,0,0), Vector3(0, 0, 0), Vector3(1.1, 1.1, 1.1));
	paintLayer.Init("paintLayer", "OBJ//HighPolyFloor.obj", "", Vector3(0, 0.25f, 0));
	
	frontWall.Init("Border", "OBJ//Wall.obj","Image//Red.tga");
	frontWall.DefineRect2DCollider(Vector3(1, 1, 105));
	frontWall.SetTranslate(Vector3(0, 0, 55));
	frontWall.SetRotate(Vector3(0, 90, 0));
	frontWall.SetScale(Vector3(1.1, 0.5, 1.1));

	leftWall.Init("Border", "OBJ//Wall.obj", "Image//Red.tga");
	leftWall.DefineRect2DCollider(Vector3(1, 1, 105));
	leftWall.SetTranslate(Vector3(55, 0, 0));
	leftWall.SetScale(Vector3(1.1, 0.5, 1.1));

	rightWall.Init("Border", "OBJ//Wall.obj", "Image//Red.tga");
	rightWall.DefineRect2DCollider(Vector3(1, 1, 105));
	rightWall.SetTranslate(Vector3(55, 0, 0));
	rightWall.SetScale(Vector3(1.1, 0.5, 1.1));

	backWall.Init("Border", "OBJ//Wall.obj", "Image//Red.tga");
	backWall.DefineRect2DCollider(Vector3(1, 1, 105));
	backWall.SetTranslate(Vector3(0, 0, -55));
	frontWall.SetRotate(Vector3(0, 90, 0));
	backWall.SetScale(Vector3(1.1, 0.5, 1.1));


	
	std::cout << "Generating grid for level\n";
	level.GenerateGrid(paintLayer.GetVBO());
	std::cout << "Done!\n";
	

	//buttons
	allButtons.push_back(&resumeButton);
	allButtons.push_back(&exitButton);
	
	//storing positions that are not empty
	map.SetOccupied(&level, ai.GetTranslate());
	map.SetOccupied(&level, car.GetTranslate());
	map.SetOccupied(&level, speedboost.GetTranslate());

	while (map.GetObjectCount() < sqrt((level_chunk.GetChunkCount())))
	{
		if (map.GenerateObj(&level))
		{
			int x = Math::RandIntMinMax(1, 2);
			int y = Math::RandIntMinMax(1, 4); //random to choose the generated object
			Objects.push_back(Collidable());
			Objects[map.GetObjectCount() - 1].Init("genObj", map.GenerateRandObj(x), map.GetObjTex(x));
			Objects[map.GetObjectCount() - 1].SetMaterial(dull);
			Objects[map.GetObjectCount() - 1].DefineRect2DCollider(Vector3(5,5,5));
			Objects[map.GetObjectCount() - 1].SetTranslate(map.GetLocation());
			Objects[map.GetObjectCount() - 1].SetRotate(map.GetRandRotate(y));
			Objects[map.GetObjectCount() - 1].SetScale(map.GetRandScale(y));
		}
	}
	
	//adding particle effects to car
	car.AddChild(&particleEffect);


	
	RequestDontDestroy(&car);
	RequestDontDestroy(&ai);
	timer = 0;

	//background music
	PlaySound(TEXT("Music//background.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	//passing window range and buttons for cursor
	mouse.SetOrthSize(orthSize);
	mouse.SetAllButton(allButtons);

}

void SceneGame::RenderDerived()
{
	if (DEBUG)
	{
		for (int i = 0; i < map.GetObjectCount(); i++)
		{
			RenderObject(Objects[i].GetCollider());
		}
		RenderObject(car.GetCollider());
		RenderObject(ai.GetCollider());
		RenderObject(frontWall.GetCollider());
		
	}
	
	//map and transparent paint layer
	/*RenderObject(&floor);*/
	RenderObject(&paintLayer);
	RenderObject(&frontWall);
	//RenderObject(&rightWall);
	//RenderObject(&leftWall);
	//RenderObject(&backWall);

	//vehicles
	RenderObject(&car);
	RenderObject(&ai);

	//powerups
	if(!speedboost.GetPickedUp())
		RenderObject(&speedboost, false);

	for (int x = 0; x < map.GetObjectCount(); x++)
	{
		RenderObject(&Objects[x]);
	}

	//resume and exit buttons during pause
	if (this->pause)
	{
		RenderObjectOnScreen(&resumeButton, false);
		RenderObjectOnScreen(&exitButton, false);
		RenderObjectOnScreen(&mouse, false);
	}

	//mouse
	

	//timer
	std::string timerString = "Timer: " + std::to_string(timer);
	RenderTextOnScreen(&TEXT, timerString, Color(1, 0, 1), 1, 0, 0);
}

void SceneGame::UpdateDerived(double dt)
{
	mouse.Move(dt);
	mouse.CheckHover();

	if (!pause)
	{
		/*std::cout << "Timer: " << timer << std::endl;*/

		//Timer
		if(!DEBUG)
		timer += dt;

		//Particle Effects
		if (car.GetEngineForce() > 0)
			particleEffect.ApplyEffect(&car,dt);

		//PowerUps
		speedboost.CheckAbsorption(car.GetTranslate());
		speedboost.ApplyEffect(static_cast<GameObject*>(&car), dt);


		//Car forward & backward inputs
		if (Application::IsKeyPressed(VK_UP) && car.GetGear() > 0)
		{
			car.MoveForward(1, dt);
		}
		else if (Application::IsKeyPressed(VK_UP) && car.GetGear() == 0)
		{
			car.MoveForward(-1, dt);
		}
		else
		{
			car.MoveForward(0, dt);
		}

		//Car brake input
		if (Application::IsKeyPressed(VK_DOWN))
		{
			car.Brake(true);
		}
		else
		{
			car.Brake(false);
		}

		//Car left & right inputs
		if (Application::IsKeyPressed(VK_LEFT))
		{
			car.MoveRight(-1, dt);
		}
		else if (Application::IsKeyPressed(VK_RIGHT))
		{
			car.MoveRight(1, dt);
		}
		else
		{
			car.MoveRight(0, dt);
		}

	

		//ai
		if (ai.CheckToMove())
		{
			temp = map.GetDestination(&level, car.GetPaint()->GetPaintColor(), ai.GetTranslate());
		}
		ai.SetNextForward(temp);
		if (!ai.CheckToMove())
		{
			ai.CalcAngle();
			if (ai.IfTurn())
			{
				if (ai.GetSpeed() > 5)
				{
					ai.Brake(true);
				
				}
				else
				{
					ai.Brake(false);
				}
				ai.MoveRight(ai.SetDir(), dt);
			}
			ai.MoveForward(1, dt);
		}


		//update car
		car.UpdateSuvat(dt);
		car.UpdateRotation(dt);
		ai.UpdateSuvat(dt);
		ai.UpdateRotation(dt);




		//update collision
		car.UpdateCollider();
		ai.UpdateCollider();
		frontWall.UpdateCollider();

		for (int i = 0; i < map.GetObjectCount(); i++)
		{
			Objects[i].UpdateCollider();
		}

		//collision checking
		if (_coll->CheckCollision2D(&car, &ai))
			_coll->ResolveCollision2D(&car, &ai);


		for (int i = 0; i < map.GetObjectCount(); i++)
		{
			if (_coll->CheckCollision2D(&car, &Objects[i]))
				_coll->ResolveCollision2D(&car, &Objects[i]);

			if (_coll->CheckCollision2D(&ai, &Objects[i]))
				_coll->ResolveCollision2D(&ai, &Objects[i]);
		}

		if (_coll->CheckCollision2D(&car, &frontWall))
			_coll->ResolveCollision2D(&car, &frontWall);

		if (_coll->CheckCollision2D(&ai, &frontWall))
			_coll->ResolveCollision2D(&ai, &frontWall);

		if (!currentCam)
			camera[0]->Update(dt, car.GetTranslate(), car.GetAngle()); //update camera

		paintLayer.ChangeColor(&level, car.GetTranslate(), car.GetPaint()->GetPaintColor());
		paintLayer.ChangeColor(&level, ai.GetTranslate(), Color(1,0,0));

	}
	else
	{
		for (Button* b : allButtons)	//for each button in the vector carryout the function
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
			pause = !pause;
			timer = 0;
			mouse.ResetMousePos();
			RequestChangeScene(1);//test
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

				else
				{
				}
			}
		}
	}

	//endgame time

	if (timer >= 100)
	{
		mouse.ResetMousePos();
		RequestDontDestroy(&paintLayer);
		RequestDontDestroy(&floor);
		std::cout << "given " << static_cast<GameObject*>(&car) << std::endl;
		RequestDontDestroy(static_cast<GameObject*>(&car));
		RequestDontDestroy(&ai);
		RequestChangeScene(4);//change to end scene once it is created
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
		car.SetGear(car.GetGear() + 1);
	}
	if (Application::IsKeyPressed('Z')) //Decrease gear
	{
		car.SetGear(car.GetGear() - 1);
	}
}

void SceneGame::RenderFrameBuffer()
{
	RenderObject(&paintLayer, false);
}
