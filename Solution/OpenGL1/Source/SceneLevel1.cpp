#include "SceneLevel1.h"



SceneLevel1::SceneLevel1()
{

}

SceneLevel1::~SceneLevel1()
{
}


void SceneLevel1::InitDerived()
{

	resume.Init(MeshBuilder::GenerateCube(Color(1, 0, 0)), "", Vector3(30, 20, 0), Vector3(0, 0, 0), Vector3(5, 1, 0));
	exit.Init(MeshBuilder::GenerateCube(Color(1, 0, 0)), "", Vector3(30, 17.5, 0), Vector3(0, 0, 0), Vector3(1, 1, 0));

	allButtons.push_back(&resume);
	allButtons.push_back(&exit);

	car.Init("OBJ//toilet.obj", "Image//toilet.tga", Vector3(2, 0, 0));
	car.SetMaterial(shiny);

	skybox.Init("OBJ//skybox.obj", "Image//skybox.tga", Vector3(0, -50, 0),Vector3(0, 0, 0), Vector3(100, 100, 100));

	totalbuttons = 2;
	buttonindex = 0;
	allButtons[0]->SetHover(true);
}

void SceneLevel1::RenderDerived()
{
	if (pause)
	{
		RenderObjectOnScreen(&resume, false);
		RenderObjectOnScreen(&exit, false);
	}
	
	RenderObject(&car, true);

	RenderObject(&skybox, false);

}

void SceneLevel1::UpdateDerived(double dt)
{
	if (pause)
	{
		for (Button* b : allButtons)	//for each button in the vector carryout the function
		{
			b->AnimateButton();
		}

		//changing of scenes

		if (exit.GetOnClickEvent())
		{
			allButtons[buttonindex]->SetHover(false);
			exit.SetOnClickEvent(false);
			pause = false;
			RequestChangeScene(1);//test
		}

		if (resume.GetOnClickEvent())
		{
			resume.SetOnClickEvent(false);
			pause = false;
		}
	}

	else
	{
		//run game
	}

}

void SceneLevel1::UpdateDerivedBounced(double dt)
{
	//selector controls
	if (pause)
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

	else
	{
		if (Application::IsKeyPressed(VK_UP))
		{
			car.IncrementTranslate(Vector3(0, 0, 1));
		}

		if (Application::IsKeyPressed(VK_DOWN))
		{
			car.IncrementTranslate(Vector3(0, 0, -1));
		}
	}

	if (Application::IsKeyPressed('P'))
	{
		if (pause)
			pause = false;
		else
			pause = true;
	}

	if (Application::IsKeyPressed('E'))
	{
		RequestChangeScene(0);
	}
}
