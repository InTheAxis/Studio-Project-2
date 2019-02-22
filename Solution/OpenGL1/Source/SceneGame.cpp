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
	car.SetMaterial(shiny);

	speedboost.Init("speedboost", MeshBuilder::GenerateCube(Color(0, 0, 0)), "", Vector3(0, 0.5, 5), Vector3(0, 0, 0), Vector3(1, 1, 1));
	particleEffect.Init("particleEffect", MeshBuilder::GenerateCube(Color(1, 0, 0)), "", Vector3(0, 0.5, car.GetTranslate().z-1.5), Vector3(0, 0, 0), Vector3(0.1, 0.1, 0.1));

	floor.Init("floor", "OBJ//Map.obj", "Image//color2.tga",Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(100, 100, 100));
	paintLayer.Init("paintLayer", "OBJ//PaintLayer.obj", "", Vector3(0, 0.25, 0), Vector3(0, 0, 0), Vector3(100, 100, 100));
	

	car.AddChild(&particleEffect);
	

	mouse.SetOrthSize(orthSize);
	mouse.SetAllButton(allButtons);
	buttonIndex = 0;

	RequestDontDestroy(&car);
}

void SceneGame::RenderDerived()
{
	RenderObject(&car, true);
	RenderObject(&floor, false);
	
	if(!speedboost.GetPickedUp())
		RenderObject(&speedboost, false);

	if (this->pause)
	{
		RenderObjectOnScreen(&resumeButton, false);
		RenderObjectOnScreen(&exitButton, false);
	}
	RenderObject(&paintLayer, false);
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
		/*if (car.GetEngineForce() > 0)*/
			particleEffect.ApplyEffect(&car,dt);

		speedboost.CheckAbsorption(car.GetTranslate());

		speedboost.ApplyEffect(&car,dt);

		

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

		if (Application::IsKeyPressed(VK_DOWN))
		{
			car.Brake(true);
		}
		else
		{
			car.Brake(false);
		}

		//todo make actual turn
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
		car.UpdateSuvat(dt);
		car.UpdateRotation(dt);

	}

	else
	{
		for (Button* b : allButtons)	//for each button in the vector carryout the function
		{
			b->AnimateButton();
		}

		//changing of scenes

		if (exitButton.GetOnClickEvent())
		{
			allButtons[1]->SetHover(false);
			exitButton.SetOnClickEvent(false);
			pause = !pause;
			mouse.ResetMousePos();
			RequestChangeScene(1);//test
		}

		if (resumeButton.GetOnClickEvent())
		{
			allButtons[0]->SetHover(false);
			resumeButton.SetOnClickEvent(false);
			pause = false;
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

	if (!currentCam)
		camera[0]->Update(dt, car.GetTranslate(), car.GetAngle()); //update camera

	if (timer >= 120)
	{
		//mouse.ResetMousePos();
		//RequestChangeScene(0);//change to end scene once it is created
	}
}

void SceneGame::UpdateDerivedBounced(double dt)
{
	if (pause)
	{
		//selector controls
		if (Application::IsKeyPressed(VK_RETURN))
		{
			allButtons[buttonIndex]->DoAction();
		}

		if (Application::IsKeyPressed(VK_DOWN))
		{
			allButtons[buttonIndex]->SetHover(false);

			if (buttonIndex >= NUM_OF_BUTTONS - 1)
			{
				buttonIndex = 0;
			}

			else
				buttonIndex++;

			allButtons[buttonIndex]->SetHover(true);
		}
		else if (Application::IsKeyPressed(VK_UP))
		{
			allButtons[buttonIndex]->SetHover(false);


			if (buttonIndex <= 0)
				buttonIndex = NUM_OF_BUTTONS - 1;
			else
				buttonIndex--;

			allButtons[buttonIndex]->SetHover(true);
		}
	}

	if (Application::IsKeyPressed(VK_ESCAPE))
	{
		pause = !pause;
	}
}

void SceneGame::RenderFrameBuffer()
{
}
