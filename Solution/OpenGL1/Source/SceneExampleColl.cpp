#include "SceneExampleColl.h"

SceneExampleColl::SceneExampleColl()
{
}


void SceneExampleColl::InitDerived()
{
	car.Init("car", "OBJ//taxi.obj", "Image//taxi.tga", NULL, NULL, Vector3(1.f, 1.f, 1.f));
	car.CreateRigidBody(Vector3(0, 0, 10), 1200, 0.1f, 0.09f);
	floor.Init("floor", "OBJ//ground-low-flat.obj", "Image//color2.tga", Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(1.f, 1.f, 1.f));
	ramp.Init("ramp", "OBJ//ground-low-flat.obj", "Image//color2.tga", Vector3(-10, 0, 0), Vector3(0, 0, -45.f), Vector3(1.f, 1.f, 1.f));
	test.Init("test", MeshBuilder::GenerateCube(Color(1, 1, 1)));
	test2.Init("test", MeshBuilder::GenerateCube(Color(0, 1, 1)));
	test2.CreateRigidBody(Vector3(0, 0, 10), 1200, 0.1f, 0.09f);

	car.DefineRect2DCollider(Vector3(2, 2, 2));
	test.DefineCircle2DCollider(Vector3(2, 2, 2));
	test2.DefineCircle2DCollider(Vector3(2, 2, 2));

	test.IncrementTranslate(Vector3(0, 2, 2));

	car.SetMaterial(shiny);
	floor.SetMaterial(dull);
	ramp.SetMaterial(dull);
}

void SceneExampleColl::RenderDerived()
{
	RenderObject(&floor);
	RenderObject(&ramp);
	RenderObject(&test);
	RenderObject(&car);

	if (DEBUG)
	{
		RenderObject(test.GetCollider());
		RenderObject(car.GetCollider());
		std::string temp = "Coll: " + std::to_string(collide);
		RenderTextOnScreen(&TEXT, temp, Color(1, 0, 1), 1, 0, 0);
	}
}

void SceneExampleColl::UpdateDerived(double dt)
{	
	/*if (Application::IsKeyPressed(VK_UP))
	{
		test2.IncrementTranslate(Vector3(0, 0, 0.1f));
	}
	if (Application::IsKeyPressed(VK_DOWN))
	{
		test2.IncrementTranslate(Vector3(0, 0, -0.1));
	}
	if (Application::IsKeyPressed(VK_LEFT))
	{
		test2.IncrementTranslate(Vector3(0.1, 0, 0));
	}
	if (Application::IsKeyPressed(VK_RIGHT))
	{
		test2.IncrementTranslate(Vector3(-0.1, 0, 0));
	}*/

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

	if (Application::IsKeyPressed('C'))
	{
		car.TorqueRotation(1, dt);
		std::cout << car.GetTorqueTheta() << std::endl;
	}
	else
	{
		car.TorqueRotation(0, dt);
	}

	car.UpdateSuvat(dt);
	car.UpdateRotation(dt);
	car.UpdateTorque(dt);

	if (!currentCam)
		camera[0]->Update(dt, car.GetTranslate(), car.GetAngle()); //update camera


	test.UpdateCollider();
	car.UpdateCollider();
	collide = _coll->CheckCollision(&test, &car);
}

void SceneExampleColl::UpdateDerivedBounced(double dt)
{
	if (Application::IsKeyPressed(VK_LCONTROL))
	{
		RequestChangeScene(1);
	}
}

SceneExampleColl::~SceneExampleColl()
{
}
