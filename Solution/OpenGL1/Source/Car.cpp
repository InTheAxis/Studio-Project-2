#include "Car.h"


Car::Car()
{
	wheels[0].Init("wheel", "OBJ//LeftWheel.obj", "Image//taxi.tga", Vector3(0.419f, 0.169f, 0.582f));
	wheels[1].Init("wheel", "OBJ//RightWheel.obj", "Image//taxi.tga", Vector3(-0.419f, 0.169f, 0.582f));
	wheels[2].Init("wheel", "OBJ//LeftWheel.obj", "Image//taxi.tga", Vector3(0.427f, 0.169f, -0.735f));
	wheels[3].Init("wheel", "OBJ//RightWheel.obj", "Image//taxi.tga", Vector3(-0.427f, 0.169f, -0.735f));

	for (int i = 0; i < 4; i++)
	{
		wheels[i].SetRadius(wheelRadius);
		this->AddChild(&(wheels[i]));
	}
}

void Car::RollFront(float u, float v, float angle, double dt)
{
	for (int i = 0; i < 2; i++)
	{
		wheels[i].RollFront(u, v, angle, dt);
	}
}

void Car::RollBack(float u, float v, double dt)
{
	for (int i = 2; i < 4; i++)
	{
		wheels[i].RollBack(u, v, dt);
	}
}

Car::~Car()
{
}