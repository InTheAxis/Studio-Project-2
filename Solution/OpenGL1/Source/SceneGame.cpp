#include "SceneGame.h"



SceneGame::SceneGame()
{

}

SceneGame::~SceneGame()
{
}


void SceneGame::InitDerived()
{

	resumeButton.Init("resumeButton", MeshBuilder::GenerateCube(Color(1, 0, 0)), "", Vector3(30, 20, 0), Vector3(0, 0, 0), Vector3(5, 1, 0));
	exitButton.Init("exitButton", MeshBuilder::GenerateCube(Color(1, 0, 0)), "", Vector3(30, 17.5, 0), Vector3(0, 0, 0), Vector3(1, 1, 0));
	mouse.Init("mouse", MeshBuilder::GenerateCube(Color(1, 0, 0)), "", Vector3(orthSize.x * 0.5f, orthSize.y * 0.5f, 10), Vector3(0, 0, 0), Vector3(1, 1, 0));

	allButtons.push_back(&resumeButton);
	allButtons.push_back(&exitButton);

	car.Init("car", "OBJ//toilet.obj", "Image//toilet.tga", Vector3(2, 0, 0));
	skybox.Init("skybox", "OBJ//skybox.obj", "Image//skybox.tga", Vector3(0, -50, 0), Vector3(0, 0, 0), Vector3(100, 100, 100));
	
	car.SetMaterial(shiny);

	mouse.SetOrthSize(orthSize);
	mouse.SetAllButton(allButtons);

	buttonIndex = 0;

	RequestDontDestroy(&car);
}

void SceneGame::RenderDerived()
{
	RenderObject(&car, true);

	RenderObject(&skybox, false);

	if (this->pause)
	{
		RenderObjectOnScreen(&resumeButton, false);
		RenderObjectOnScreen(&exitButton, false);
		RenderObjectOnScreen(&mouse, false);
	}
}

void SceneGame::UpdateDerived(double dt)
{
	if (!pause) return;

	mouse.Move(dt);
	mouse.CheckHover();

	for (Button* b : allButtons)	//for each button in the vector carryout the function
	{
		b->AnimateButton();
	}

	//changing of scenes

	if (exitButton.GetOnClickEvent())
	{
		allButtons[buttonIndex]->SetHover(false);
		exitButton.SetOnClickEvent(false);
		pause = false;
		RequestChangeScene(1);//test
	}

	if (resumeButton.GetOnClickEvent())
	{
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
