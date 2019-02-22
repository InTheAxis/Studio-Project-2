#include "SceneLevelSelect.h"



SceneLevelSelect::SceneLevelSelect()
{
}

SceneLevelSelect::~SceneLevelSelect()
{
}


void SceneLevelSelect::InitDerived()
{
	level1.Init("level1button", "OBJ//LevelsButton.obj", "Image//levels1.tga", Vector3(8, 15, -10), Vector3(0, 0, 0), Vector3(1, 1, 0));
	level2.Init("level2button", "OBJ//LevelsButton.obj", "Image//levels1.tga", Vector3(30, 15, -10), Vector3(0, 0, 0), Vector3(1, 1, 0));
	level3.Init("level3button", "OBJ//LevelsButton.obj", "Image//levels1.tga", Vector3(52, 15, -10), Vector3(0, 0, 0), Vector3(1, 1, 0));
	mouse.Init("mouse",MeshBuilder::GenerateCube(Color(1, 0, 0)), "", Vector3(orthSize.x * 0.5f, orthSize.y * 0.5f, 10), Vector3(0, 0, 0), Vector3(1, 1, 0));

	
	level1Text.Init("level1text", "OBJ//LevelsButton.obj", "Image//levels1Text.tga", Vector3(8, 15, -9), Vector3(0, 0, 0), Vector3(20, 20, 0));
	level2Text.Init("level2text", "OBJ//LevelsButton.obj", "Image//levels2Text.tga", Vector3(30, 15, -9), Vector3(0, 0, 0), Vector3(20, 20, 0));
	level3Text.Init("level3text", "OBJ//LevelsButton.obj", "Image//levels3Text.tga", Vector3(52, 15, -9), Vector3(0, 0, 0), Vector3(20, 20, 0));
	allButtons.push_back(&level1);
	allButtons.push_back(&level2);
	allButtons.push_back(&level3);

	totalbuttons = 3;
	buttonindex = 0;
	allButtons[0]->SetHover(true);

	mouse.SetOrthSize(orthSize);
	mouse.SetAllButton(allButtons);
	freeRoam.ToggleCamMovement();
	mouse.ResetMousePos();
}

void SceneLevelSelect::RenderDerived()
{
	RenderObjectOnScreen(&level1, false);
	RenderObjectOnScreen(&level1Text, false);
	RenderObjectOnScreen(&level2, false);
	RenderObjectOnScreen(&level2Text, false);
	RenderObjectOnScreen(&level3, false);
	RenderObjectOnScreen(&level3Text, false);
	RenderObjectOnScreen(&mouse, false);
}

void SceneLevelSelect::UpdateDerived(double dt)
{
	mouse.Move(dt);
	mouse.CheckHover();
	for (Button* b : allButtons)	//for each button in the vector carryout the function
	{
		b->AnimateButton();
	}


	//changing of scenes
	if (level1.GetOnClickEvent())
	{
		allButtons[buttonindex]->SetHover(false);
		level1.SetOnClickEvent(false);	//reset bool before changing scene
		mouse.ResetMousePos();
		RequestChangeScene(3);
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

void SceneLevelSelect::UpdateDerivedBounced(double dt)
{
	

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

