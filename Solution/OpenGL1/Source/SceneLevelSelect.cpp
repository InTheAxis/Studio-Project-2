#include "SceneLevelSelect.h"



SceneLevelSelect::SceneLevelSelect()
{
}

SceneLevelSelect::~SceneLevelSelect()
{
}


void SceneLevelSelect::InitDerived()
{
	level1.Init("level1", MeshBuilder::GenerateCube(Color(0, 1, 0)), "", Vector3(30, 20, 0), Vector3(0, 0, 0), Vector3(5, 1, 0));
	level2.Init("level2", MeshBuilder::GenerateCube(Color(0, 1, 0)), "", Vector3(30, 17.5, 0), Vector3(0, 0, 0), Vector3(5, 1, 0));
	level3.Init("level3", MeshBuilder::GenerateCube(Color(0, 1, 0)), "", Vector3(30, 15, 0), Vector3(0, 0, 0), Vector3(5, 1, 0));
	mouse.Init("mouse",MeshBuilder::GenerateCube(Color(1, 0, 0)), "", Vector3(orthSize.x * 0.5f, orthSize.y * 0.5f, 10), Vector3(0, 0, 0), Vector3(1, 1, 0));

	allButtons.push_back(&level1);
	allButtons.push_back(&level2);
	allButtons.push_back(&level3);

	totalbuttons = 3;
	buttonindex = 0;
	allButtons[0]->SetHover(true);

	mouse.SetOrthSize(orthSize);
	mouse.SetAllButton(allButtons);
}

void SceneLevelSelect::RenderDerived()
{
	RenderObjectOnScreen(&level1, false);
	RenderObjectOnScreen(&level2, false);
	RenderObjectOnScreen(&level3, false);
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
		RequestChangeScene(3);
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

