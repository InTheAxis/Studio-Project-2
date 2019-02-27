#include "SceneHoodInk.h"

SceneHoodInk::SceneHoodInk()
{

}

void SceneHoodInk::InitDerived()
{
	//Camera Initialisation
	currentCam = FIXED_TOP_DOWN;
	//camera[0]->Init(Vector3(0, 2, 5), Vector3(0, 0.0f, 0), Vector3(0, 1, 0)); //Camera Initialisation

	//Mouse Initialisation
	mouse.Init("mouse", MeshBuilder::GenerateCube(Color(1, 0, 0)), "", Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 0));

	TEXT.Init("Text", MeshBuilder::GenerateText(16, 16), "Image//Fonts//calibri.tga");

	Taxi.Init("Taxi", "OBJ//Taxi.obj", "Image//red.tga", Vector3(0, 3, 0));
	Taxi.CreateRigidBody(Vector3(0, 0, 10), 1200, 0.1f, 0.09f);
	TaxiHood.Init("TaxiHood", "OBJ//TaxiHood.obj", "Screenshots//test.tga", Vector3(0, 0, 0));
	TaxiWheels.Init("TaxiWheels", "OBJ//TaxiWheels.obj", "Image//red.tga", Vector3(0, 0, 0));

	Truck.Init("Truck", "OBJ//Truck.obj", "Image//red.tga", Vector3(0, 3, 0));
	Truck.CreateRigidBody(Vector3(0, 0, 10), 1200, 0.1f, 0.09f);
	TruckHood.Init("TruckHood", "OBJ//TruckHood.obj", "Screenshots//test.tga", Vector3(0, 0, 0));
	TruckWheels.Init("TruckWheels", "OBJ//TruckWheels.obj", "Image//red.tga", Vector3(0, 0, 0));

	F1.Init("F1", "OBJ//F1.obj", "Image//red.tga", Vector3(0, 3, 0));
	F1.CreateRigidBody(Vector3(0, 0, 10), 1200, 0.1f, 0.09f);
	F1Hood.Init("F1Hood", "OBJ//F1Hood.obj", "Screenshots//test.tga", Vector3(0, 0, 0));
	F1Wheels.Init("F1Wheels", "OBJ//F1Wheels.obj", "Image//red.tga", Vector3(0, 0, 0));
	
	floor.Init("Floor", "OBJ//Ground-HighPoly-Flat.obj", "Image//Black.tga");
	paintLayer.Init("PaintLayer", "OBJ//Ground-HighPoly-Flat.obj", "", Vector3(0, 0.25f, 0));

	Taxi.SetMaterial(shiny);
	Truck.SetMaterial(shiny);
	F1.SetMaterial(shiny);

	floor.SetMaterial(dull);
	paintLayer.SetMaterial(dull);

	Taxi.AddChild(&(TaxiHood));
	Taxi.AddChild(&(TaxiWheels));

	Truck.AddChild(&(TruckHood));
	Truck.AddChild(&(TruckWheels));

	F1.AddChild(&(F1Hood));
	F1.AddChild(&(F1Wheels));

	//yellow.SetPaintColor(Color(1, 1, 0));
	//purple.SetPaintColor(Color(1, 0, 1));

	R, G, B = 0;
	CurrentColor = C_RED;

	//MouseX = mouse.GetTranslate().x;
	//MouseY = mouse.GetTranslate().y;

	//mouse.SetOrthSize(orthSize);
	//mouse.SetAllButton(allButtons);

	std::cout << "Generating grid for level\n";
	level.GenerateGrid(paintLayer.GetVBO());
	std::cout << "Done!\n";
	mouse.SetOrthSize(orthSize);

}

void SceneHoodInk::RenderFrameBuffer()
{
	RenderObject(&paintLayer, false);
}

void SceneHoodInk::RenderDerived()
{
	RenderObject(&floor);
	RenderObject(&paintLayer);
	//RenderObject(&Quad);
	//std::cout << "Test " << std::endl;

	//=================================== Test =============================================
	//RenderObject(&Taxi);
	//RenderObject(&Truck);
	//RenderObject(&F1);
	//RenderObject(&F1Hood); 

	//RenderTextOnScreen(&TEXT, Instructions, Color(1, 1, 1), 3.f, 20.f, 20.f);
	//RenderTextOnScreen(&TEXT, Screenshot, Color(1, 1, 1), 3.f, 20.f, 20.f);
	//=======================================================================================
	RenderObjectOnScreen(&mouse, false);
}

void SceneHoodInk::UpdateDerived(double dt)
{
	//camera[0]->target = Vector3(0, 0, 0);
	//camera[0]->position = Vector3(0, 8.f, 0);

	mouse.Move(dt);

	//if (Application::IsKeyPressed(VK_LBUTTON)) //WORKING
	//{
	//	paintLayer.ChangeColor(&level, Vector3(((mouse.GetTranslate().x * -1) + 30), 0, ((mouse.GetTranslate().y) - 15)), Color(R, G, B));
	if (Application::IsKeyPressed(VK_LBUTTON))
	{
		paintLayer.ChangeColor(&level, Vector3((((mouse.GetTranslate().x * -1) + 30)/2.7), 0, ((mouse.GetTranslate().y) - 15)/1.85), Color(R, G, B), 0.5);
	}
	//if (Application::IsKeyPressed(Application::leftMouseClick)) // TEST
	//{
	//	paintLayer.ChangeColor(&level, camera[currentCam]->position, Color(R, G, B));
	//}
	
}

void SceneHoodInk::UpdateDerivedBounced(double dt)
{
	//================ Paint Color Switching ================
	if (CurrentColor == C_RED)
	{
		R = 1;
		G = 0;
		B = 0;
	}
	else if (CurrentColor == C_GREEN)
	{
		R = 0;
		G = 1;
		B = 0;
	}
	else if (CurrentColor == C_BLUE)
	{
		R = 0;
		G = 0;
		B = 1;
	}
	else if (CurrentColor == C_YELLOW)
	{
		R = 1;
		G = 1;
		B = 0;
	}
	else if (CurrentColor == C_PURPLE)
	{
		R = 1;
		G = 0;
		B = 1;
	}
	//=====================================================
	if (Application::IsKeyPressed(VK_LEFT))
	{
		if (CurrentColor == C_RED)
		{
			CurrentColor = C_PURPLE;
		}
		else
		{
			CurrentColor--;
		}
	}
	if (Application::IsKeyPressed(VK_RIGHT))
	{
		if (CurrentColor == C_PURPLE)
		{
			CurrentColor = 0;
		}
		else
		{
			CurrentColor++;
		}
	}
	//=======================================================

	if (Application::IsKeyPressed(VK_RETURN))
	{
		WriteFromFBO(m_frameBufferID, "Screenshots//test.tga");
	}

	if (Application::IsKeyPressed(VK_ESCAPE))
	{
		RequestChangeScene(6);
	}
}

SceneHoodInk::~SceneHoodInk()
{
}