#include "SceneStart.h"



SceneStart::SceneStart()
{
	
}

SceneStart::~SceneStart()
{
}


void SceneStart::InitDerived()
{

	play.Init(MeshBuilder::GenerateCube(Color(1, 0, 1)), "", Vector3(20, 10, 0),  Vector3(0, 0, 0), Vector3(5, 1, 0));
	levelSelect.Init(MeshBuilder::GenerateCube(Color(1, 0, 1)), "", Vector3(20, 7.5, 0), Vector3(0, 0, 0), Vector3(5, 1, 0));
	exit.Init(MeshBuilder::GenerateCube(Color(1, 0, 1)), "", Vector3(20, 5, 0), Vector3(0, 0, 0), Vector3(5, 1, 0));

	decreaseSize = false;

	allButtons.push_back(&play);
	allButtons.push_back(&levelSelect);
	allButtons.push_back(&exit);

	totalbuttons = 3;

	buttonindex = 0;

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
		RequestChangeScene(2);
	}

	/*if (selectortranslateY == 10)
	{
		if (Play.GetScale().x >= 8)
		{
			decreaseSize = true;
		}

		else if (Play.GetScale().x <= 5)
		{
			decreaseSize = false;
		}

		if (decreaseSize)
			Play.IncrementScale(Vector3(3 * -dt, -dt, 0)*1.5);

		else if (!decreaseSize)
			Play.IncrementScale(Vector3(3 * dt, dt, 0)*1.5);
	}

	else
		Play.SetScale(Vector3(5, 1, 1));*/

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
		
		/*selectortranslateY = Arrow.MoveSelector(15, selectortranslateY, -2.5, selector);
		selector.SetTranslate(Vector3(15, selectortranslateY, 0));*/
		if (buttonindex >= totalbuttons)
		{
			buttonindex = 0;
		}

		else
		buttonindex++;
	}

	if (Application::IsKeyPressed(VK_UP))
	{
		if (buttonindex <= 0)
			buttonindex = totalbuttons - 1;
		else
		buttonindex--;
		/*selectortranslateY = Arrow.MoveSelector(15, selectortranslateY, 2.5, selector);
		selector.SetTranslate(Vector3(15, selectortranslateY, 0));*/
	}
}

//float Button::MoveSelector(float x, float y, float distance, GameObject selector)
//{
//	if (distance >= 0)
//	{
//		if (y >= optionposY[0])
//		{
//			y = optionposY.back();
//		}
//
//		else
//			y += distance;
//	}
//
//	if (distance <= 0)
//	{
//		if (y <= optionposY.back())
//		{
//			y = optionposY[0];
//		}
//
//		else
//			y += distance;
//	}
//	return y;
//
//}
//
//void Button::SetOptionPosY(float y)
//{
//	optionposY.push_back(y);
//}