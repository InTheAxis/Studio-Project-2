#include "SceneExampleCarInk.h"

SceneExampleCarInk::SceneExampleCarInk()
{
}


void SceneExampleCarInk::InitDerived()
{
	car.Init("OBJ//taxi.obj", "Image//taxi.tga", Vector3(0, 0, 0));
	car.CreateRigidBody(Vector3(0, 0, 10), 1200, 0.1f, 0.09f);
	floor.Init("OBJ//ground-low.obj", "Image//color2.tga");
	paintLayer.Init("OBJ//ground-high.obj", "", Vector3(0, 0.25f, 0));

	car.SetMaterial(shiny);
	floor.SetMaterial(dull);
	paintLayer.SetMaterial(dull);

	std::cout << "Generating grid for level\n";
	level.GenerateGrid(paintLayer.GetVBO());
	std::cout << "Done!\n";
}

void SceneExampleCarInk::RenderDerived()
{
	RenderObject(&floor);
	RenderObject(&paintLayer);
	RenderObject(&car);
}

void SceneExampleCarInk::UpdateDerived(double dt)
{	
	if (Application::IsKeyPressed(VK_UP) && car.GetGear() > 0)
	{
		car.MoveForward(1, dt);
	}
	else if (Application::IsKeyPressed(VK_UP) && car.GetGear() == 0)
	{
		car.MoveForward(-1, dt);
	}
	else
	{
		car.MoveForward(0, dt);
	}

	if (Application::IsKeyPressed(VK_DOWN))
	{
		car.Brake(true);
	}
	else
	{
		car.Brake(false);
	}

	//todo make actual turn
	if (Application::IsKeyPressed(VK_LEFT))
	{
		car.MoveRight(-1, dt);
	}
	else if (Application::IsKeyPressed(VK_RIGHT))
	{
		car.MoveRight(1, dt);
	}
	else
	{
		car.MoveRight(0, dt);
	}
	car.UpdateSuvat(dt);
	car.UpdateRotation(dt);
	
	if (!currentCam)
		camera[0]->Update(dt, car.GetTranslate(), car.GetAngle()); //update camera

	 paintLayer.ChangeColor(&level, car.GetTranslate(), Color(1, 0, 1));

	 if (Application::IsKeyPressed('F'))
		 paintLayer.ChangeColor(&level, camera[1]->position, Color(1, 1, 0));

}

void SceneExampleCarInk::UpdateDerivedBounced(double dt)
{	
	if (Application::IsKeyPressed(VK_LCONTROL))
	{
		RequestChangeScene(1);
	}
	if (Application::IsKeyPressed('Z'))
	{
		car.SetGear(car.GetGear() - 1);
	}
	if (Application::IsKeyPressed('X'))
	{
		car.SetGear(car.GetGear() + 1);
	}
}

SceneExampleCarInk::~SceneExampleCarInk()
{
}
