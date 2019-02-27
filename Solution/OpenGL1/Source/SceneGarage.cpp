#include "SceneGarage.h"


SceneGarage::SceneGarage()
{

}

void SceneGarage::InitDerived()
{
	//mouse and buttons
	exitButton.Init("exit", "OBJ//LevelsButton.obj", "Image//levels1.tga", Vector3(50, 5, -10), Vector3(0, 0, 0), Vector3(1, 1, 0));
	exitText.Init("level3text", "OBJ//LevelsButton.obj", "Image//exitText.tga", Vector3(50, 5, -9), Vector3(0, 0, 0), Vector3(20, 20, 0));

	hoodinkButton.Init("exit", "OBJ//LevelsButton.obj", "Image//levels1.tga", Vector3(10, 5, -10), Vector3(0, 0, 0), Vector3(1, 1, 0));
	hoodinkText.Init("level3text", "OBJ//LevelsButton.obj", "Image//exitText.tga", Vector3(10, 5, -9), Vector3(0, 0, 0), Vector3(20, 20, 0));

	mouse.Init("mouse", MeshBuilder::GenerateCube(Color(1, 0, 0)), "", Vector3(orthSize.x * 0.5f, orthSize.y * 0.5f, 10), Vector3(0, 0, 0), Vector3(1, 1, 0));

	allButtons.push_back(&hoodinkButton);
	allButtons.push_back(&exitButton);
	//passing window range and buttons for cursor
	mouse.SetOrthSize(orthSize);
	mouse.SetAllButton(allButtons);

	TAXI.Init("Taxi","OBJ//TAXI.obj", "Image//Red.tga", Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0.1, 0.1, 0.1));
	TRUCK.Init("Truck","OBJ//TRUCK.obj", "Image//Red.tga", Vector3(0, 0, 0));
	F1.Init("F1","OBJ//F1.obj", "Image//Red.tga", Vector3(0, 0, 0));

	BACKGROUND.Init("Background","OBJ//BACKGROUND.obj", "Image//Background.tga", Vector3(0, 0, 0));
	ARROW.Init("Arrow","OBJ//ARROW.obj", "Image//Red.tga", Vector3(10, 10, 0));

	TEXT.Init("Text",MeshBuilder::GenerateText(16, 16), "Image//Fonts//calibri.tga");
	camera[0]->Init(Vector3(0, 2, 5), Vector3(0, 0.0f, 0), Vector3(0, 1, 0)); //Camera Initialisation

	TAXI.AddTexture("Image//Green.tga");
	TAXI.AddTexture("Image//Blue.tga");
	TAXI.AddTexture("Image//Yellow.tga");
	TAXI.AddTexture("Image//Purple.tga");
	TAXI.AddTexture("Image//Aqua.tga");

	TRUCK.AddTexture("Image//Green.tga");
	TRUCK.AddTexture("Image//Blue.tga");
	TRUCK.AddTexture("Image//Yellow.tga");
	TRUCK.AddTexture("Image//Purple.tga");
	TRUCK.AddTexture("Image//Aqua.tga");

	F1.AddTexture("Image//Green.tga");
	F1.AddTexture("Image//Blue.tga");
	F1.AddTexture("Image//Yellow.tga");
	F1.AddTexture("Image//Purple.tga");
	F1.AddTexture("Image//Aqua.tga");

	CurrentVehicle = V_TAXI;
	CurrentColor = C_RED;

	SColor = "COLOUR";
	SVehicle = "VEHICLE";

	Selected = 0;
	freeRoam.ToggleCamMovement();
}

void SceneGarage::RenderDerived()
{
	RenderObject(&BACKGROUND);
	RenderObjectOnScreen(&ARROW);
	ARROW.SetScale(Vector3(16,12.5,3));
	ARROW.SetTranslate(Vector3(30,-4.5f,0));
	
	//mouse and cursor
	RenderObjectOnScreen(&mouse, false);
	RenderObjectOnScreen(&exitButton, false);
	RenderObjectOnScreen(&exitText, false);
	RenderObjectOnScreen(&hoodinkButton, false);
	RenderObjectOnScreen(&hoodinkText, false);

	//============================ Vehicle Switching ==============================
	if (CurrentVehicle == V_TAXI)
	{
		RenderObject(&TAXI);
	}
	else if (CurrentVehicle == V_TRUCK)
	{
		RenderObject(&TRUCK);
	}
	else if (CurrentVehicle == V_F1)
	{
		RenderObject(&F1);
	}
	//=============================================================================
	//================================ Text =======================================
	if (Selected == 0) //If Vehicle mode
	{
		RenderTextOnScreen(&TEXT, SVehicle, Color(0, 1, 0), 2.1f, 11.3f, 12.5f);
		RenderTextOnScreen(&TEXT, SColor, Color(1, 0, 0), 1.5f, 17.4f, 1.6f);

	}
	else if (Selected == 1) //If Colour mode
	{
		RenderTextOnScreen(&TEXT, SColor, Color(0, 1, 0), 2.1f, 11.8f, 1.f);
		RenderTextOnScreen(&TEXT, SVehicle, Color(1, 0, 0), 1.5f, 17.2f, 17.7f);
	}
}

bool car = false;
void SceneGarage::UpdateDerived(double dt)  //Keeps the vehicles in rotation
{
	//mouse
	mouse.Move(dt);
	mouse.CheckHover();

	if (CurrentVehicle == 0)
	{
		if (TAXI.GetScale() != Vector3(1, 1, 1))
		{
			TAXI.IncrementScale(Vector3(0.03, 0.03, 0.03));
		}
	}
	else if (CurrentVehicle != 0)
	{
		TAXI.SetScale(Vector3(0.1, 0.1, 0.1));
	}

	if (CurrentVehicle == 1)
	{
		if (TRUCK.GetScale() != Vector3(1, 1, 1))
		{
			TRUCK.IncrementScale(Vector3(0.03, 0.03, 0.03));
		}
	}
	else if (CurrentVehicle != 1)
	{
		TRUCK.SetScale(Vector3(0.1, 0.1, 0.1));
	}

	if (CurrentVehicle == 2)
	{
		if (F1.GetScale() != Vector3(1, 1, 1))
		{
			F1.IncrementScale(Vector3(0.03, 0.03, 0.03));
		}
	}
	else if (CurrentVehicle != 2)
	{
		F1.SetScale(Vector3(0.1, 0.1, 0.1));
	}


	TAXI.IncrementRotate(Vector3(0, 1, 0));
	TRUCK.IncrementRotate(Vector3(0, 1, 0));
	F1.IncrementRotate(Vector3(0, 1, 0));

	//buttons
	for (Button* b : allButtons)	//for each button in the vector carryout the function
	{
		b->AnimateButton();
	}

	if (exitButton.GetOnClickEvent())
	{
		allButtons[1]->SetHover(false);
		exitButton.SetOnClickEvent(false);
		RequestChangeScene(1);//test
		mouse.ResetMousePos();
	}

	if (hoodinkButton.GetOnClickEvent())
	{
		allButtons[0]->SetHover(false);
		hoodinkButton.SetOnClickEvent(false);
		RequestChangeScene(2);//test
		mouse.ResetMousePos();
	}

	if (Application::leftMouseClick)
	{
		for (unsigned int i = 0; i < allButtons.size(); ++i)
		{
			if (allButtons[i]->GetHover())
			{
				allButtons[i]->DoAction();
				break;
			}
		}
	}

}

void SceneGarage::UpdateDerivedBounced(double dt)
{
	//======================= Vehicle Switching ===========================
	if (Application::IsKeyPressed(VK_UP))
	{
		if (Selected == 1) //If Colour mode
		{
			Selected = 0; //Switch to Vehicle mode
		}
	}
	else if (Application::IsKeyPressed(VK_DOWN))
	{
		if (Selected == 0) //If Vehicle mode
		{
			Selected = 1; //Switch to Colour mode
		}
	}
	//=====================================================================
	//======================== Colour Switching ===========================
	else if (Application::IsKeyPressed(VK_RIGHT))
	{
		if (Selected == 1) // COLOUR MODE
		{
			if (CurrentColor == C_TOTAL - 1)
			{
				CurrentColor = C_RED;
			}
			else
			{
				CurrentColor++;
			}
			TAXI.ChangeTexture(CurrentColor);
			TRUCK.ChangeTexture(CurrentColor);
			F1.ChangeTexture(CurrentColor);
		}
		else if (Selected == 0) // VEHICLE MODE
		{
			if (CurrentVehicle == 0)
			{
				CurrentVehicle = V_TOTAL - 1;
			}
			else
			{
				CurrentVehicle--;
			}
		}
	}
	else if (Application::IsKeyPressed(VK_LEFT))
	{
		if (Selected == 1)  // COLOUR MODE
		{
			if (CurrentColor == C_RED)
			{
				CurrentColor = C_TOTAL - 1;
			}
			else
			{
				CurrentColor--;
			}
			TAXI.ChangeTexture(CurrentColor);
			TRUCK.ChangeTexture(CurrentColor);
			F1.ChangeTexture(CurrentColor); // Placeholder, change to F1 later
		}
		else if (Selected == 0)  // VEHICLE MODE
		{
			if (CurrentVehicle == V_TOTAL - 1)
			{
				CurrentVehicle = 0;
			}
			else
			{
				CurrentVehicle++;
			}
		}
	}
	//================================================================================

	
}

SceneGarage::~SceneGarage()
{

}