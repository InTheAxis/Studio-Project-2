#include "SceneStart.h"



SceneStart::SceneStart()
{

}

SceneStart::~SceneStart()
{
}


void SceneStart::InitDerived()
{

	play.Init(MeshBuilder::GenerateCube(Color(1, 0, 1)), "", Vector3(30, 20, 0), Vector3(0, 0, 0), Vector3(5, 1, 0));
	levelSelect.Init(MeshBuilder::GenerateCube(Color(1, 0, 1)), "", Vector3(30, 17.5, 0), Vector3(0, 0, 0), Vector3(5, 1, 0));
	exit.Init(MeshBuilder::GenerateCube(Color(1, 0, 1)), "", Vector3(30, 15, 0), Vector3(0, 0, 0), Vector3(5, 1, 0));

	decreaseSize = false;

	allButtons.push_back(&play);
	allButtons.push_back(&levelSelect);
	allButtons.push_back(&exit);

	totalbuttons = 3;

	buttonindex = 0;

	allButtons[0]->SetHover(true);

}

void SceneStart::RenderDerived()
{
	RenderObjectOnScreen(&play, false);
	RenderObjectOnScreen(&levelSelect, false);
	RenderObjectOnScreen(&exit, false);
}

void SceneStart::UpdateDerived(double dt)
{
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
		if (buttonindex >= totalbuttons-1)
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
