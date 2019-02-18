#include "SceneStart.h"



SceneStart::SceneStart()
{
}

SceneStart::~SceneStart()
{
}


void SceneStart::InitDerived()
{
	prevCursorXY = currentCursorXY = (Vector3(Application::cursorX, Application::cursorY, 0));

	mouse.Init("mouse", MeshBuilder::GenerateCube(Color(1, 0, 0)), "", Vector3(orthSize.x * 0.5f, orthSize.y * 0.5f, 10), Vector3(0, 0, 0), Vector3(1, 1, 0));
	play.Init("play", MeshBuilder::GenerateCube(Color(1, 0, 1)), "", Vector3(30, 20, 0), Vector3(0, 0, 0), Vector3(5, 1, 0));
	garage.Init("garage", MeshBuilder::GenerateCube(Color(1, 0, 1)), "", Vector3(30, 17.5, 0), Vector3(0, 0, 0), Vector3(5, 1, 0));
	exit.Init("exit", MeshBuilder::GenerateCube(Color(1, 0, 1)), "", Vector3(30, 15, 0), Vector3(0, 0, 0), Vector3(5, 1, 0));

	decreaseSize = false;

	allButtons.push_back(&play);
	allButtons.push_back(&garage);
	allButtons.push_back(&exit);

	totalbuttons = 3;

	buttonindex = 0;

	mouse.SetOrthSize(orthSize);
	mouse.SetAllButton(allButtons);
}

void SceneStart::RenderDerived()
{
	RenderObjectOnScreen(&play, false);
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
		RequestChangeScene(2);
	}

	if (garage.GetOnClickEvent())
	{
		allButtons[buttonindex]->SetHover(false);
		play.SetOnClickEvent(false);
		RequestChangeScene(6);
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
