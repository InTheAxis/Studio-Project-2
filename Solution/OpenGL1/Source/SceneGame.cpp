#include "SceneGame.h"



SceneGame::SceneGame()
{

}

SceneGame::~SceneGame()
{
}


void SceneGame::InitDerived()
{
	//timer,button and cursor
	timer = 0;
	resumeButton.Init("play", "OBJ//LevelsButton.obj", "Image//levels.tga", Vector3(30, 20, 0), Vector3(0, 0, 0), Vector3(1, 1, 0));
	exitButton.Init("garage", "OBJ//LevelsButton.obj", "Image//levels.tga", Vector3(30, 15, 0), Vector3(0, 0, 0), Vector3(1, 1, 0));
	mouse.Init("mouse", MeshBuilder::GenerateCube(Color(1, 0, 0)), "", Vector3(orthSize.x * 0.5f, orthSize.y * 0.5f, 10), Vector3(0, 0, 0), Vector3(1, 1, 0));

	//car
	car.Init("car", "OBJ//taxi.obj", "Image//taxi.tga",Vector3(0, 0.3f, 0));
	car.CreateRigidBody(Vector3(0, 0, 10), 1200, 0.1f, 0.09f);
	car.SetTorque(-1, 0, 0.5, 0.5);
	car.SetMaterial(shiny);
	car.DefineRect2DCollider(Vector3(2, 2, 2));
	car.GetPaint()->SetPaintColor(Color(1, 1, 0));

	//AI
	ai.Init("ai", "OBJ//taxi.obj", "Image//Red.tga", Vector3(0, 0.3f, 10));
	ai.CreateRigidBody(Vector3(0, 0, 10), 1200, 0.1f, 0.09f);
	ai.SetTorque(-1, 0, 0.5, 0.5);
	ai.SetMaterial(shiny);
	ai.DefineRect2DCollider(Vector3(2,2,2));

	//PowerUps,Particle Effects
	speedboost.Init("speedboost", MeshBuilder::GenerateCube(Color(0, 0, 0)), "", Vector3(0, 0.5, 5), Vector3(0, 0, 0), Vector3(1, 1, 1));
	particleEffect.Init("particleEffect", MeshBuilder::GenerateCube(Color(1, 0, 0)), "", Vector3(0, 0.5, car.GetTranslate().z-1.5), Vector3(0, 0, 0), Vector3(0.1, 0.1, 0.1));


	//map
	floor.Init("floor", "OBJ//LowPolyFloor.obj", "Image//color2.tga");
	paintLayer.Init("paintLayer", "OBJ//HighPolyFloor.obj", "", Vector3(0, 0.25f, 0));
	

	std::cout << "Generating grid for level\n";
	level.GenerateGrid(paintLayer.GetVBO());
	std::cout << "Done!\n";


	//buttons
	allButtons.push_back(&resumeButton);
	allButtons.push_back(&exitButton);

	//while (map.GetObjectCount() < ((level_chunk.GetChunkCount() / 9) - 2))
	//{
	//	if (map.GenerateObj(&level))
	//	{
	//		int x = Math::RandIntMinMax(1, 2);
	//		int y = Math::RandIntMinMax(1, 4); //random to choose the generated object
	//		Objects.push_back(Collidable());
	//		Objects[map.GetObjectCount() - 1].Init("genObj", map.GenerateRandObj(x), map.GetObjTex(x), map.GetLocation(), map.GetRandRotate(y), map.GetRandScale(y));
	//		Objects[map.GetObjectCount() - 1].SetMaterial(dull);
	//		Objects[map.GetObjectCount() - 1].DefineRect2DCollider(Objects[map.GetObjectCount() - 1].GetScale());
	//	}
	//}
	
	//adding particle effects to car
	car.AddChild(&particleEffect);



	
	//passing window range and buttons for cursor
	mouse.SetOrthSize(orthSize);
	mouse.SetAllButton(allButtons);
}

void SceneGame::RenderDerived()
{
	if (DEBUG)
	{
		RenderObject(car.GetCollider());
		RenderObject(ai.GetCollider());
		/*for (int i = 0; i < ((level_chunk.GetChunkCount() / 9) - 2); i++)
		{
			RenderObject(Objects[i].GetCollider());
		}*/
	}
	
	//map and transparent paint layer
	RenderObject(&floor);
	RenderObject(&paintLayer);

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
	}

	//mouse
	RenderObjectOnScreen(&mouse, false);

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
		speedboost.ApplyEffect(reinterpret_cast<GameObject*>(&car), dt);


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

		//Torque rotation inputs
		if (Application::IsKeyPressed('1'))
		{
			car.TorqueRotation(1, dt);
		}
		else if (Application::IsKeyPressed('2'))
		{
			car.TorqueRotation(2, dt);
		}
		else if (Application::IsKeyPressed('3'))
		{
			car.TorqueRotation(3, dt);
		}
		else if (Application::IsKeyPressed('4'))
		{
			car.TorqueRotation(4, dt);
		}
		else if (Application::IsKeyPressed('5'))
		{
			car.TorqueRotation(5, dt);
		}
		else if (Application::IsKeyPressed('6'))
		{
			car.TorqueRotation(6, dt);
		}
		else if (Application::IsKeyPressed('7'))
		{
			car.TorqueRotation(7, dt);
		}
		else if (Application::IsKeyPressed('8'))
		{
			car.TorqueRotation(8, dt);
		}
		else
		{
			car.TorqueRotation(0, dt);
		}

		//update car
		car.UpdateSuvat(dt);
		car.UpdateRotation(dt);
		car.UpdateTorque(dt);

		ai.UpdateSuvat(dt);
		ai.UpdateRotation(dt);
		ai.UpdateTorque(dt);

		//update collision
		car.UpdateCollider();
		ai.UpdateCollider();

	
		if (_coll->CheckCollision2D(&car, &ai))
			_coll->ResolveCollision2D(&car, &ai);

		if (!currentCam)
			camera[0]->Update(dt, car.GetTranslate(), car.GetAngle()); //update camera

		paintLayer.ChangeColor(&level, car.GetTranslate(), car.GetPaint()->GetPaintColor());

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
			for (int i = 0; i < allButtons.size(); ++i)
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
	if (timer >= 20)
	{
		mouse.ResetMousePos();
		RequestDontDestroy(&paintLayer);
		RequestDontDestroy(&floor);
		RequestDontDestroy(&car);
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
	if (Application::IsKeyPressed('Z')) //Decrease gear
	{
		car.SetGear(car.GetGear() - 1);
	}
	if (Application::IsKeyPressed('X')) //Increase gear
	{
		car.SetGear(car.GetGear() + 1);
	}
}

void SceneGame::RenderFrameBuffer()
{
	RenderObject(&paintLayer, false);
}
