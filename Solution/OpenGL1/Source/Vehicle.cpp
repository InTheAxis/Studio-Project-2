#include "Vehicle.h"



Vehicle::Vehicle()
{
	thrustForce = MAX_FORCE / 5;
	turningSpeed = 20.f;
	gearNumber = 1;
	wheelRadius = 0.001f;
	angleY = 0.0f;
	InitMaxThrustForce(MAX_FORCE);
}

void Vehicle::MoveForward(int dir, double dt)
{
	if (!dir)
		this->forceForward = 0;
	this->AddForceForward(Vector3(0, 0, dir * thrustForce * (float)dt));

	this->translate += s * this->forward.Normalize();

	this->RollFront(u, v, dt);
	this->RollBack(u, v, dt);
}

void Vehicle::MoveRight(int dir, double dt)
{
	if (v < 1 || u < 1) return;
	if (!dir)
		this->forceRight = 0;
	this->AddForceRight(Vector3(0, dir * turningSpeed * (float)dt, 0));

	angleY = -1 * forceRight * dt;
	rotationMatrix.SetToRotation(angleY, 0, 1, 0);
	forward = rotationMatrix * forward;
	this->rotate.y += angleY;
}

void Vehicle::Brake(bool brake)
{
	if (brake)
		this->AddBrakeFriction(Vector3(0, 0, BRAKE_FRICTION));
	else
		this->AddBrakeFriction(Vector3(0, 0, 0));
}

void Vehicle::SetStats(float thrustForce, float turningSpeed, float wheelRadius)
{
	this->thrustForce = thrustForce;
	this->turningSpeed = turningSpeed;
	this->wheelRadius = wheelRadius;
}

void Vehicle::SetGear(int gear)
{
	if (gear >= 0 && gear < 6)
	{
		this->gearNumber = gear;
	}

	switch (gearNumber) {
	case 0:
		thrustForce = MAX_FORCE / 5;
		break;
	case 1:
		thrustForce = MAX_FORCE / 5;
		break;
	case 2:
		thrustForce = (MAX_FORCE / 5) * 2;
		break;
	case 3:
		thrustForce = (MAX_FORCE / 5) * 3;
		break;
	case 4:
		thrustForce = (MAX_FORCE / 5) * 4;
		break;
	case 5:
		thrustForce = MAX_FORCE;
		break;
	default:
		thrustForce = MAX_FORCE / 5;
		break;
	}
	InitMaxThrustForce(MAX_FORCE);
}

int Vehicle::GetGear()
{
	return gearNumber;
}

int Vehicle::GetThrustForce()
{
	return thrustForce;
}

Vector3 Vehicle::GetAngle()
{
	return Vector3(0, angleY, 0);
}

Vehicle::~Vehicle()
{
}
