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

	cursor.Init(MeshBuilder::GenerateCube(Color(1, 0, 0)), "", Vector3(orthSize.x * 0.5f, orthSize.y * 0.5f, 10), Vector3(0, 0, 0), Vector3(1, 1, 0));
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
	RenderObjectOnScreen(&cursor, false);
}

void SceneStart::UpdateDerived(double dt)
{
	MoveMouse(dt);

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

void SceneStart::MoveMouse(double dt)
{
	//get currentCursorXY
	currentCursorXY = Vector3(Application::cursorX, Application::cursorY, 0);

	//compare the change in position (delta position)
	//delta position is current cursor-prevcursor, basically the offset.
	deltaPosCursor = (currentCursorXY - prevCursorXY) * MOUSE_SENS;
	deltaPosCursor.y *= -1;

	//add deltaPos to mouse's translate
	cursor.IncrementTranslate(deltaPosCursor);

	//if mousepos is outside orth...
	if (cursor.GetTranslate().x >orthSize.x)
		cursor.SetTranslate(Vector3(orthSize.x, cursor.GetTranslate().y, cursor.GetTranslate().z));
	else if (cursor.GetTranslate().x < 0)
		cursor.SetTranslate(Vector3(0, cursor.GetTranslate().y, cursor.GetTranslate().z));
	if (cursor.GetTranslate().y > orthSize.y)
		cursor.SetTranslate(Vector3(cursor.GetTranslate().x, orthSize.y, cursor.GetTranslate().z));
	else if (cursor.GetTranslate().y < 0)
		cursor.SetTranslate(Vector3(cursor.GetTranslate().x, 0, cursor.GetTranslate().z));

	std::cout << currentCursorXY << std::endl;

	//update prevCursorXY
	prevCursorXY = currentCursorXY;
}
