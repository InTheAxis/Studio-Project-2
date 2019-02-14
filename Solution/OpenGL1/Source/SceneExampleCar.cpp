#include "SceneExampleCar.h"

SceneExampleCar::SceneExampleCar()
{
}


void SceneExampleCar::InitDerived()
{
	floor.Init(MeshBuilder::GenerateQuad(Color(1, 1, 1)), "", Vector3(0, -5, 0), Vector3(0, 0, 0), Vector3(50, 1, 50));
	car.Init(MeshBuilder::GenerateCube(Color(0, 0, 1, 0.5f)), "", Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(2, 2, 4));
	car.CreateRigidBody(Vector3(0, 0, 10), 1200, 0.4, 0.2);

	car.SetMaterial(shiny);
	floor.SetMaterial(dull);
}

void SceneExampleCar::RenderDerived()
{
	RenderObject(&floor);
	RenderObject(&car);
}

void SceneExampleCar::UpdateDerived(double dt)
{	
	if (Application::IsKeyPressed(VK_UP))
		car.MoveForward(1, dt);
	else if (Application::IsKeyPressed(VK_DOWN))
		car.MoveForward(-1, dt);
	else
		car.MoveForward(0, dt);

	//todo make actual turn
	if (Application::IsKeyPressed(VK_LEFT))
		car.MoveRight(-1, dt);
	else if (Application::IsKeyPressed(VK_RIGHT))
		car.MoveRight(1, dt);

	car.UpdateSuvat(dt);

	if (!currentCam)
		camera[0]->Update(dt, car.GetTranslate(), car.GetRotate()); //update camera
}

void SceneExampleCar::UpdateDerivedBounced(double dt)
{	
	if (Application::IsKeyPressed(VK_LCONTROL))
	{
		RequestChangeScene(1);
	}
	/*if (Application::IsKeyPressed('Z'))
	{
		car.SetGears(car.GetGear() - 1);
	}
	if (Application::IsKeyPressed('X'))
	{
		car.SetGears(car.GetGear() + 1);
	}*/
}

SceneExampleCar::~SceneExampleCar()
{
}
