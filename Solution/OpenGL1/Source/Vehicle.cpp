#include "Vehicle.h"



Vehicle::Vehicle()
{
	engineForce = 10000;
	turningForce = 4500;
	brakeFriction = 5000;
	gearNumber = 1;
	wheelRadius = 0.001f;
	angleY = 0.0f;
	turningLerpf = 0;
	torqueForce = 0;
}

void Vehicle::MoveForward(int dir, double dt)
{
	if (!dir)
	{
		this->forceForward = 0;
	}
	this->AddForceForward(Vector3(0, 0, dir * engineForce));

	this->translate += s * this->forward.Normalize();

	this->RollFront(u, v, angleY, dt);
	this->RollBack(u, v, dt);
}

void Vehicle::MoveRight(int dir, double dt)
{
	if (!dir)
	{
		this->forceRight = 0;
		this->angleY = 0;
		this->turningLerpf = 0;
	}
	this->AddForceRight(Vector3(dir * turningForce, 0, 0));

	angleY = Math::RadianToDegree(-theta);
	rotationMatrix.SetToRotation(angleY, 0, 1, 0);
	forward = rotationMatrix * forward;
	this->rotate.y += angleY;

	if (dir == 1)
	{
		turningLerpf = MathExtended::Lerpf(turningLerpf, 25, 0.2);
		this->RollFront(u, v, angleY - turningLerpf, dt);
	}
	else if (dir == -1)
	{
		turningLerpf = MathExtended::Lerpf(turningLerpf, 25, 0.2);
		this->RollFront(u, v, angleY + turningLerpf, dt);
	}
}

void Vehicle::TorqueRotation(int dir, double dt)
{
	if (!dir)
	{
		SetRotateAndPivot(Vector3(0, 0, 0), Vector3(0, 0, 0));
	}
	else
	{
		this->AddTorqueForce(dir * 5000);
		SetRotateAndPivot(Vector3(torqueTheta, 0, 0), Vector3(0, 0, leverArm.x));
	}
}

void Vehicle::Brake(bool brake)
{
	if (brake)
		this->AddBrakeFriction(brakeFriction);
	else
		this->AddBrakeFriction(0);
}

void Vehicle::SetStats(float engineForce, float brakeFriction, float turningForce, float wheelRadius)
{
	this->engineForce = engineForce;
	this->brakeFriction = brakeFriction;
	this->turningForce = turningForce;
	this->wheelRadius = wheelRadius;
}

void Vehicle::SetGear(int gear)
{
	if (gear >= 0 && gear <= 5)
	{
		this->gearNumber = gear;
	}

	switch (gearNumber) {
	case 0:
		engineForce = 15000;
		break;
	case 1:
		engineForce = 15000;
		break;
	case 2:
		engineForce = 17500;
		break;
	case 3:
		engineForce = 20000;
		break;
	case 4:
		engineForce = 22500;
		break;
	case 5:
		engineForce = 25000;
		break;
	default:
		break;
	}
}

int Vehicle::GetGear()
{
	return gearNumber;
}

float Vehicle::GetEngineForce()
{
	return engineForce;
}

float Vehicle::GetBrakeFriction()
{
	return brakeFriction;
}

float Vehicle::GetTurningForce()
{
	return turningForce;
}

Vector3 Vehicle::GetAngle()
{
	return Vector3(0, angleY, 0);
}

Paint* Vehicle::GetPaint()
{
	return &paint;
}

Vehicle::~Vehicle()
{
}
