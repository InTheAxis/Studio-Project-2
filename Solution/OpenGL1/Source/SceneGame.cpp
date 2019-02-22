#include "SceneGame.h"



SceneGame::SceneGame()
{

}

SceneGame::~SceneGame()
{
}


void SceneGame::InitDerived()
{
	timer = 0;
	resumeButton.Init("play", "OBJ//LevelsButton.obj", "Image//levels.tga", Vector3(30, 20, 0), Vector3(0, 0, 0), Vector3(1, 1, 0));
	exitButton.Init("garage", "OBJ//LevelsButton.obj", "Image//levels.tga", Vector3(30, 15, 0), Vector3(0, 0, 0), Vector3(1, 1, 0));
	mouse.Init("mouse", MeshBuilder::GenerateCube(Color(1, 0, 0)), "", Vector3(orthSize.x * 0.5f, orthSize.y * 0.5f, 10), Vector3(0, 0, 0), Vector3(1, 1, 0));

	allButtons.push_back(&resumeButton);
	allButtons.push_back(&exitButton);

	car.Init("car", "OBJ//taxi.obj", "Image//taxi.tga", Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(1.f, 1.f, 1.f));
	car.CreateRigidBody(Vector3(0, 0, 10), 1200, 0.1f, 0.09f);
	car.SetTorque(-1, 0, 0.5, 0.5);
	car.SetMaterial(shiny);

	speedboost.Init("speedboost", MeshBuilder::GenerateCube(Color(0, 0, 0)), "", Vector3(0, 0.5, 5), Vector3(0, 0, 0), Vector3(1, 1, 1));
	particleEffect.Init("particleEffect", MeshBuilder::GenerateCube(Color(1, 0, 0)), "", Vector3(0, 0.5, car.GetTranslate().z-1.5), Vector3(0, 0, 0), Vector3(0.1, 0.1, 0.1));

	floor.Init("floor", "OBJ//Map.obj", "Image//color2.tga");
	paintLayer.Init("paintLayer", "OBJ//PaintLayer.obj", "", Vector3(0, 0.25f, 0));
	
	std::cout << "Generating grid for level\n";
	level.GenerateGrid(paintLayer.GetVBO());
	std::cout << "Done!\n";

	car.AddChild(&particleEffect);
	car.GetPaint()->SetPaintColor(Color(1, 0, 1));
	
	mouse.SetOrthSize(orthSize);
	mouse.SetAllButton(allButtons);
	buttonIndex = 0;
}

void SceneGame::RenderDerived()
{
	RenderObject(&car);
	RenderObject(&floor);
	RenderObject(&paintLayer);
	
	if(!speedboost.GetPickedUp())
		RenderObject(&speedboost, false);


	if (this->pause)
	{
		RenderObjectOnScreen(&resumeButton, false);
		RenderObjectOnScreen(&exitButton, false);
	}
	RenderObjectOnScreen(&mouse, false);
}

void SceneGame::UpdateDerived(double dt)
{
	mouse.Move(dt);
	mouse.CheckHover();

	if (!pause)
	{
		std::cout << "Timer: " << timer << std::endl;
		timer += dt;
		if (car.GetEngineForce() > 0)
			particleEffect.ApplyEffect(&car,dt);

		speedboost.CheckAbsorption(car.GetTranslate());

		speedboost.ApplyEffect(&car,dt);

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

		car.UpdateSuvat(dt);
		car.UpdateRotation(dt);
		car.UpdateTorque(dt);


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
	if (timer >= 120)
	{
		//mouse.ResetMousePos();
		//RequestChangeScene(0);//change to end scene once it is created
	}
}

void SceneGame::UpdateDerivedBounced(double dt)
{
	if (Application::IsKeyPressed(VK_ESCAPE))
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
