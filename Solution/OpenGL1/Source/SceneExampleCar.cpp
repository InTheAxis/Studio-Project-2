#include "SceneExampleCar.h"

SceneExampleCar::SceneExampleCar()
{
}


void SceneExampleCar::InitDerived()
{
	car.Init("OBJ//taxi.obj", "Image//taxi.tga", Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(1.f, 1.f, 1.f));
	car.CreateRigidBody(Vector3(0, 0, 10), 1200, 0.1f, 0.09f);
	floor.Init("OBJ//ground-low.obj", "Image//color2.tga", Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));
	paintLayer.Init("OBJ//ground-high.obj", "", Vector3(0, 0.3f, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));

	car.SetMaterial(shiny);
	floor.SetMaterial(dull);
	paintLayer.SetMaterial(dull);

	std::cout << "Generating grid for level\n";
	level.CreateLinkedList(paintLayer.GetVBO());
	std::cout << "Done!\n";
}

void SceneExampleCar::RenderDerived()
{
	RenderObject(&floor);
	RenderObject(&paintLayer);
	RenderObject(&car);
	RenderObject(&(car.wheels[0]));
}

void SceneExampleCar::UpdateDerived(double dt)
{	
	if (Application::IsKeyPressed(VK_UP))
	{
		car.MoveForward(1, dt);
	}
	else if (Application::IsKeyPressed(VK_DOWN))
	{
		car.MoveForward(-1, dt);
	}
	else
	{
		car.MoveForward(0, dt);
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
	car.UpdateSuvat(dt);
	car.UpdateRotation(dt);

	if (!currentCam)
		camera[0]->Update(dt, car.GetTranslate(), car.GetRotate()); //update camera

	if (Application::IsKeyPressed('F'))
	{
		paintLayer.ChangeColor(&level, car.GetTranslate(), Color(1, 0, 1));
	}
}

void SceneExampleCar::UpdateDerivedBounced(double dt)
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

SceneExampleCar::~SceneExampleCar()
{
}
