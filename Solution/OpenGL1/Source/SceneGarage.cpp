#include "SceneGarage.h"


SceneGarage::SceneGarage()
{

}

void SceneGarage::InitDerived()
{
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
}

void SceneGarage::RenderDerived()
{
	RenderObject(&BACKGROUND);

	RenderObjectOnScreen(&ARROW);
	ARROW.SetScale(Vector3(16,12.5,3));
	ARROW.SetTranslate(Vector3(30,-4.5f,0));
	

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