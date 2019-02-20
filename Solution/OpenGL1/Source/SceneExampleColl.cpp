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

	car.DefineBoxCollider(Vector3(2, 2, 2));
	test.DefineBoxCollider(Vector3(2, 2, 2));
	test2.DefineBoxCollider(Vector3(2, 2, 2));

	test.IncrementTranslate(Vector3(0, 0, 0));

	car.SetMaterial(shiny);
	floor.SetMaterial(dull);
	ramp.SetMaterial(dull);
}

void SceneExampleColl::RenderDerived()
{
	RenderObject(&floor);
	RenderObject(&ramp);
	RenderObject(&test);
	RenderObject(&test2);

	if (DEBUG)
	{
		RenderObject(test.GetCollider());
		RenderObject(test2.GetCollider());
		std::string temp = "Coll: " + std::to_string(collide);
		RenderTextOnScreen(&TEXT, temp, Color(1, 0, 1), 1, 0, 0);
	}
}

void SceneExampleColl::UpdateDerived(double dt)
{	
	if (Application::IsKeyPressed(VK_UP))
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
	}

	car.UpdateSuvat(dt);
	car.UpdateRotation(dt);
	car.UpdateRotation(dt);
	//car.UpdateTorque(dt);

	if (!currentCam)
		camera[0]->Update(dt, car.GetTranslate(), car.GetAngle()); //update camera


	test.UpdateCollider();
	test2.UpdateCollider();
	collide = _coll->CheckCollision(&test2, &test);
}

void SceneExampleColl::UpdateDerivedBounced(double dt)
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

SceneExampleColl::~SceneExampleColl()
{
}
