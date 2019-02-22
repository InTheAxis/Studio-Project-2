#include "SceneStart.h"



SceneStart::SceneStart()
{
}

SceneStart::~SceneStart()
{
}


void SceneStart::InitDerived()
{
	background.Init("background", "OBJ//LevelsButton.obj", "Image//Background.tga", Vector3(orthSize.x * 0.5f, orthSize.y * 0.5f, -10), Vector3(0, 0, 0), Vector3(60, 30, 10));
	mouse.Init("mouse", MeshBuilder::GenerateCube(Color(1, 0, 0)), "", Vector3(orthSize.x * 0.5f, orthSize.y * 0.5f, 10), Vector3(0, 0, 0), Vector3(1, 1, 0));
	play.Init("play", "OBJ//LevelsButton.obj", "Image//play.tga", Vector3(15, 15, 0));

	
	playText.Init("playText", "OBJ//LevelsButton.obj", "Image//playText.tga", Vector3(15, 15, 1), Vector3(0, 0, 0), Vector3(15, 15, 0));
	garage.Init("garage", "OBJ//LevelsButton.obj", "Image//levels.tga", Vector3(30, 15, 0), Vector3(0, 0, 0), Vector3(1, 1, 0));
	exit.Init("exit", "OBJ//LevelsButton.obj", "Image//levels.tga", Vector3(45, 15, 0), Vector3(0, 0, 0), Vector3(1, 1, 0));
	

	decreaseSize = false;

	allButtons.push_back(&play);
	allButtons.push_back(&garage);
	allButtons.push_back(&exit);

	totalbuttons = 3;

	buttonindex = 0;

	mouse.SetOrthSize(orthSize);
	mouse.SetAllButton(allButtons);
	freeRoam.ToggleCamMovement();
}

void SceneStart::RenderDerived()
{
	RenderObjectOnScreen(&background, false);
	RenderObjectOnScreen(&play, false);
	RenderObjectOnScreen(&playText, false);
	RenderObjectOnScreen(&garage, false);
	RenderObjectOnScreen(&exit, false);
	RenderObjectOnScreen(&mouse, false);
}

void SceneStart::UpdateDerived(double dt)
{
	mouse.Move(dt);
	mouse.CheckHover();

	for (Button* b : allButtons)	//for each button in the vector carryout the function
	{
		b->AnimateButton();
	}

	if (play.GetOnClickEvent())
	{
		allButtons[buttonindex]->SetHover(false);
		play.SetOnClickEvent(false);
		mouse.ResetMousePos();
		RequestChangeScene(2);
	}

	if (garage.GetOnClickEvent())
	{
		allButtons[buttonindex]->SetHover(false);
		garage.SetOnClickEvent(false);
		mouse.ResetMousePos();
		RequestChangeScene(6);
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


		}
	}
}

void SceneStart::UpdateDerivedBounced(double dt)
{
	//selector controls
	

	if (Application::IsKeyPressed(VK_RETURN))
	{
		allButtons[buttonindex]->DoAction();
	}

	if (Application::IsKeyPressed(VK_DOWN))
	{
		allButtons[buttonindex]->SetHover(false);
		if (buttonindex >= totalbuttons - 1)
		{
			buttonindex = 0;
		}

		else
			buttonindex++;

		allButtons[buttonindex]->SetHover(true);
	}

	if (Application::IsKeyPressed(VK_UP))
	{
		allButtons[buttonindex]->SetHover(false);
		if (buttonindex <= 0)
			buttonindex = totalbuttons - 1;
		else
			buttonindex--;

		allButtons[buttonindex]->SetHover(true);
	}
}
