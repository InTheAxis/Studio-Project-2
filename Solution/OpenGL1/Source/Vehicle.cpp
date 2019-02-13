#include "Vehicle.h"



Vehicle::Vehicle()
{
	thrustForce = 98000;
	turningSpeed = 100;
}

void Vehicle::MoveForward(int dir, double dt)
{
	if (!dir)
		this->forceForward = 0;
	this->AddForce(Vector3(0, 0, dir * thrustForce * (float)dt));

	this->translate += s * this->forward.Normalize();
}
void Vehicle::MoveRight(int dir, double dt)
{
	float angleY = -1 * dir * turningSpeed * dt;
	rotationMatrix.SetToRotation(angleY, 0, 1, 0);
	forward = rotationMatrix * forward;
	
	this->rotate.y += angleY;
}

void Vehicle::SetStats(float thrustForce, float turningSpeed)
{
	this->thrustForce = thrustForce;
	this->turningSpeed = turningSpeed;
}


Vehicle::~Vehicle()
{
}
