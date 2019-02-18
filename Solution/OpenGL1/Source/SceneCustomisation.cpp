#include "SceneCustomisation.h"


SceneCustomisation::SceneCustomisation()
{

}

void SceneCustomisation::InitDerived()
{
	TAXI.Init("OBJ//TAXI.obj", "Image//Red.tga", Vector3(0, 0, 0), Vector3(0,0,0), Vector3(0.1,0.1,0.1));
	TRUCK.Init("OBJ//TRUCK.obj", "Image//Red.tga", Vector3(0, 0, 0));
	BACKGROUND.Init("OBJ//BACKGROUND.obj", "Image//Background.tga", Vector3(0, 0, 0));
	ARROW.Init("OBJ//ARROW.obj", "Image//Red.tga", Vector3(0, 0, 0));

	TEXT.Init(MeshBuilder::GenerateText(16, 16), "Image//Fonts//calibri.tga");
	camera[0]->Init(Vector3(0, 3, 5), Vector3(0, 0.5f, 0), Vector3(0, 1, 0)); //Camera Initialisation

	// F1.Init("OBJ//F1.obj", "Image//F1.tga", Vector3(0, -20, 0));

	ToiletTest.Init("OBJ//toilet.obj", "Image//Red.tga", Vector3(0, 0, 0));   //Placeholder

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

	ToiletTest.AddTexture("Image//Green.tga");
	ToiletTest.AddTexture("Image//Blue.tga");
	ToiletTest.AddTexture("Image//Yellow.tga");
	ToiletTest.AddTexture("Image//Purple.tga");
	ToiletTest.AddTexture("Image//Aqua.tga");

	ARROW.AddTexture("Image//Green.tga");
	ARROW.AddTexture("Image//Blue.tga");
	ARROW.AddTexture("Image//Yellow.tga");
	ARROW.AddTexture("Image//Purple.tga");
	ARROW.AddTexture("Image//Aqua.tga");

	CurrentVehicle = V_TAXI;
	CurrentColor = C_RED;
	CurrentColorText = S_RED;
	//CurrentColorArrow = A_RED;

	SColor = "COLOUR";
	SVehicle = "VEHICLE";

	Selected = 0;
}

void SceneCustomisation::RenderDerived() 
{
	RenderObject(&BACKGROUND);

	RenderObject(&ARROW);
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
		RenderObject(&ToiletTest); //Placeholder
	}
	//=============================================================================
	//========================= Text Colour Switching =============================
	if (CurrentColorText == S_RED)
	{
		RenderTextOnScreen(&TEXT, SColor, Color(1, 0, 0), 1.f, 17.5f, 1.5f);
		RenderTextOnScreen(&TEXT, SVehicle, Color(1, 0, 0), 1.f, 17.f, 17.5f);
	}
	else if (CurrentColorText == S_GREEN)
	{
		RenderTextOnScreen(&TEXT, SColor, Color(0, 1, 0), 1.f, 17.5f, 1.5f);
		RenderTextOnScreen(&TEXT, SVehicle, Color(0, 1, 0), 1.f, 17.f, 17.5f);
	}
	else if (CurrentColorText == S_BLUE)
	{
		RenderTextOnScreen(&TEXT, SColor, Color(0, 0, 1), 1.f, 17.5f, 1.5f);
		RenderTextOnScreen(&TEXT, SVehicle, Color(0, 0, 1), 1.f, 17.f, 17.5f);
	}
	else if (CurrentColorText == S_YELLOW)
	{
		RenderTextOnScreen(&TEXT, SColor, Color(1, 1, 0), 1.f, 17.5f, 1.5f);
		RenderTextOnScreen(&TEXT, SVehicle, Color(1, 1, 0), 1.f, 17.f, 17.5f);
	}
	else if (CurrentColorText == S_PURPLE)
	{
		RenderTextOnScreen(&TEXT, SColor, Color(0.982, 0.2, 1), 1.f, 17.5f, 1.5f);
		RenderTextOnScreen(&TEXT, SVehicle, Color(0.982, 0.2, 1), 1.f, 17.f, 17.5f);
	}
	else if (CurrentColorText == S_AQUA)
	{
		RenderTextOnScreen(&TEXT, SColor, Color(0.2, 1, 1), 1.f, 17.5f, 1.5f);
		RenderTextOnScreen(&TEXT, SVehicle, Color(0.2, 1, 1), 1.f, 17.f, 17.5f);
	}
	//=============================================================================
}

bool car = false;
void SceneCustomisation::UpdateDerived(double dt)  //Keeps the vehicles in rotation
{  
	if (CurrentVehicle == 0)
		if (TAXI.GetScale() != Vector3(1,1,1))
			TAXI.IncrementScale(Vector3(0.01, 0.01, 0.01));
	else if (CurrentVehicle != 0)
		TAXI.SetScale(Vector3(0.1, 0.1, 0.1));

	TAXI.IncrementRotate(Vector3(0, 1, 0));
	
	TRUCK.IncrementRotate(Vector3(0, 1, 0));
	//F1.IncrementRotate(Vector3(0, 1, 0));
	
	ToiletTest.IncrementRotate(Vector3(0, 1, 0));
}

void SceneCustomisation::UpdateDerivedBounced(double dt)
{
	//==================== Vehicle Switching ========================
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
	//===============================================================
	//===================== Colour Switching ========================
	else if (Application::IsKeyPressed(VK_RIGHT))
	{	
		if (Selected == 1) // COLOUR MODE
		{
			if (CurrentColor == C_TOTAL - 1)
			{
				CurrentColor = C_RED;
				CurrentColorText = S_RED;
				//CurrentColorArrow = A_RED;
			}
			else
			{
				CurrentColor++;
				CurrentColorText++;
				//CurrentColorArrow++;
			}

				TAXI.ChangeTexture(CurrentColor);
				TRUCK.ChangeTexture(CurrentColor);
				ToiletTest.ChangeTexture(CurrentColor); // Placeholder, change to F1 later
				ARROW.ChangeTexture(CurrentColor);
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
				CurrentColorText = S_TOTAL - 1;
				//CurrentColorArrow = A_TOTAL - 1;
			}
			else
			{
				CurrentColor--;
				CurrentColorText--;
				//CurrentColorArrow--;
			}
			TAXI.ChangeTexture(CurrentColor);
			TRUCK.ChangeTexture(CurrentColor);
			ToiletTest.ChangeTexture(CurrentColor); // Placeholder, change to F1 later
			ARROW.ChangeTexture(CurrentColor);
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
	//std::cout << Selected; //Debug
	//==============================================================
}

SceneCustomisation::~SceneCustomisation()
{

}