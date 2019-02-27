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

	//init objects
	TAXI.Init("Taxi","OBJ//TAXI.obj", "Image//Green.tga", Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0.1, 0.1, 0.1));
	TRUCK.Init("Truck","OBJ//TRUCK.obj", "Image//Green.tga", Vector3(0, 0, 0));
	F1.Init("F1","OBJ//F1.obj", "Image//Green.tga", Vector3(0, 0, 0));
	BACKGROUND.Init("Background","OBJ//BACKGROUND.obj", "Image//Background.tga", Vector3(0, 0, 0));
	ARROW.Init("Arrow","OBJ//ARROW.obj", "Image//Red.tga", Vector3(10, 10, 0));
	TEXT.Init("Text",MeshBuilder::GenerateText(16, 16), "Image//Fonts//calibri.tga");
	camera[FIXED_FOLLOWER]->Init(Vector3(0, 2, 5), Vector3(0, 0.0f, 0), Vector3(0, 1, 0)); //Camera Initialisation

	TAXI.AddTexture("Image//Red.tga");
	TAXI.AddTexture("Image//Blue.tga");
	TAXI.AddTexture("Image//Yellow.tga");
	TAXI.AddTexture("Image//Purple.tga");
	TAXI.AddTexture("Image//Aqua.tga");

	TRUCK.AddTexture("Image//Red.tga");
	TRUCK.AddTexture("Image//Blue.tga");
	TRUCK.AddTexture("Image//Yellow.tga");
	TRUCK.AddTexture("Image//Purple.tga");
	TRUCK.AddTexture("Image//Aqua.tga");

	F1.AddTexture("Image//Red.tga");
	F1.AddTexture("Image//Blue.tga");
	F1.AddTexture("Image//Yellow.tga");
	F1.AddTexture("Image//Purple.tga");
	F1.AddTexture("Image//Aqua.tga");

	currentVehicle = V_TAXI;
	currentColor = C_GREEN;

	selected = false;
	freeRoam.ToggleCamMovement();

	existingCar = nullptr;
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
	if (currentVehicle == V_TAXI)
	{
		RenderObject(&TAXI);
	}
	else if (currentVehicle == V_TRUCK)
	{
		RenderObject(&TRUCK);
	}
	else if (currentVehicle == V_F1)
	{
		RenderObject(&F1);
	}
	//=============================================================================
	//================================ Text =======================================
	if (selected == 0) //If Vehicle mode
	{
		RenderTextOnScreen(&TEXT, "VEHICLE", Color(0, 1, 0), 2.1f, 11.3f, 12.5f);
		RenderTextOnScreen(&TEXT, "COLOUR", Color(1, 0, 0), 1.5f, 17.4f, 1.6f);

	}
	else if (selected == 1) //If Colour mode
	{
		RenderTextOnScreen(&TEXT, "COLOUR", Color(0, 1, 0), 2.1f, 11.8f, 1.f);
		RenderTextOnScreen(&TEXT, "VEHICLE", Color(1, 0, 0), 1.5f, 17.2f, 17.7f);
	}
}

void SceneGarage::UpdateDerived(double dt)  //Keeps the vehicles in rotation
{
	//mouse
	mouse.Move(dt);
	mouse.CheckHover();

	if (currentVehicle == 0)
	{
		if (TAXI.GetScale() != Vector3(1, 1, 1))
		{
			TAXI.IncrementScale(Vector3(0.03, 0.03, 0.03));
		}
	}
	else if (currentVehicle != 0)
	{
		TAXI.SetScale(Vector3(0.1, 0.1, 0.1));
	}

	if (currentVehicle == 1)
	{
		if (TRUCK.GetScale() != Vector3(1, 1, 1))
		{
			TRUCK.IncrementScale(Vector3(0.03, 0.03, 0.03));
		}
	}
	else if (currentVehicle != 1)
	{
		TRUCK.SetScale(Vector3(0.1, 0.1, 0.1));
	}

	if (currentVehicle == 2)
	{
		if (F1.GetScale() != Vector3(1, 1, 1))
		{
			F1.IncrementScale(Vector3(0.03, 0.03, 0.03));
		}
	}
	else if (currentVehicle != 2)
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

	if (hoodinkButton.GetOnClickEvent())
	{
		allButtons[0]->SetHover(false);
		hoodinkButton.SetOnClickEvent(false);
		RequestChangeScene(2); //HOOD
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
	if (exitButton.GetOnClickEvent())
	{
		existingCar = static_cast<Car*>(GetDontDestroyGameObject("car"));
		if (!existingCar) std::cout << " ERROR : car pointer lost in garage\n";
		switch (currentVehicle)
		{
		default:
		case V_TAXI:
			if (existingCar)
				existingCar->Init("car", "OBJ//taxiNoWheels.obj");
			break;
		case V_TRUCK:
			if (existingCar)
				existingCar->Init("car", "OBJ//TRUCK.obj");
			break;
		case V_F1:
			if (existingCar)
				existingCar->Init("car", "OBJ//F1.obj");
			break;
		}
		switch (currentColor)
		{
		case C_GREEN:
			existingCar->GetPaint()->SetPaintColor(Color(0, 1, 0));
			break;
		case C_RED:
			existingCar->GetPaint()->SetPaintColor(Color(1, 0, 0));
			break;
		case C_BLUE:
			existingCar->GetPaint()->SetPaintColor(Color(0, 1, 0));
			break;
		case C_YELLOW:
			existingCar->GetPaint()->SetPaintColor(Color(1, 1, 0));
			break;
		case C_PURPLE:
			existingCar->GetPaint()->SetPaintColor(Color(1, 0, 1));
			break;
		case C_AQUA:
			existingCar->GetPaint()->SetPaintColor(Color(0, 1, 1));
			break;
		}

		allButtons[1]->SetHover(false);
		exitButton.SetOnClickEvent(false);
		RequestDontDestroy(static_cast<GameObject*>(existingCar));
		RequestChangeScene(1); //START
		mouse.ResetMousePos();
	}
	
	//======================= Vehicle Switching ===========================
	if (Application::IsKeyPressed(VK_UP))
	{
		if (selected == 1) //If Colour mode
		{
			selected = 0; //Switch to Vehicle mode
		}
	}
	else if (Application::IsKeyPressed(VK_DOWN))
	{
		if (selected == 0) //If Vehicle mode
		{
			selected = 1; //Switch to Colour mode
		}
	}
	//=====================================================================
	//======================== Colour Switching ===========================
	else if (Application::IsKeyPressed(VK_RIGHT))
	{
		if (selected == 1) // COLOUR MODE
		{
			if (currentColor == C_TOTAL - 1)
			{
				currentColor = C_RED;
			}
			else
			{
				currentColor++;
			}
			TAXI.ChangeTexture(currentColor);
			TRUCK.ChangeTexture(currentColor);
			F1.ChangeTexture(currentColor);
		}
		else if (selected == 0) // VEHICLE MODE
		{
			if (currentVehicle == 0)
			{
				currentVehicle = V_TOTAL - 1;
			}
			else
			{
				currentVehicle--;
			}
		}
	}
	else if (Application::IsKeyPressed(VK_LEFT))
	{
		if (selected == 1)  // COLOUR MODE
		{
			if (currentColor == 0)
			{
				currentColor = C_TOTAL - 1;
			}
			else
			{
				currentColor--;
			}
			TAXI.ChangeTexture(currentColor);
			TRUCK.ChangeTexture(currentColor);
			F1.ChangeTexture(currentColor); // Placeholder, change to F1 later
		}
		else if (selected == 0)  // VEHICLE MODE
		{
			if (currentVehicle == V_TOTAL - 1)
			{
				currentVehicle = 0;
			}
			else
			{
				currentVehicle++;
			}
		}
	}
	//================================================================================

	
}

SceneGarage::~SceneGarage()
{

}