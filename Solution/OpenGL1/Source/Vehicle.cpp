#include "Vehicle.h"



Vehicle::Vehicle()
{
	engineForce = 20000;
	turningForce = 4500;
	brakeFriction = 5000;
	gearNumber = 1;
	wheelRadius = 0.001f;
	angleY = 0.0f;
	torqueForce = 2000;
	torqueAngle = 0.0f;
}

void Vehicle::MoveForward(int dir, double dt)
{
	if (!dir)
	{
		this->forceForward = 0;
	}
	this->AddForceForward(Vector3(0, 0, dir * engineForce));

	this->translate += s * this->forward.Normalize();

	this->RollFront(u, v, dt);
	this->RollBack(u, v, dt);
}

void Vehicle::MoveRight(int dir, double dt)
{
	if (!dir)
	{
		this->forceRight = 0;
		this->angleY = 0;
	}
	this->AddForceRight(Vector3(0, 0, dir * turningForce));

	angleY = Math::RadianToDegree(-theta);
	rotationMatrix.SetToRotation(angleY, 0, 1, 0);
	forward = rotationMatrix * forward;
	this->rotate.y += angleY;
}

void Vehicle::TorqueRotation(int dir, double dt)
{
	if (!dir)
	{
		this->torqueForce = 0;
		this->torqueAngle = 0;
	}
	this->AddTorqueForce(Vector3(0, 0, dir * torqueForce));

	torqueAngle = Math::RadianToDegree(torque);
	rotationMatrix.SetToRotation(torqueAngle, 0, 0, 1);
	forward = rotationMatrix * forward;
	this->rotate.z += torqueAngle;
}

void Vehicle::Brake(bool brake)
{
	if (brake)
		this->AddBrakeFriction(Vector3(0, 0, brakeFriction));
	else
		this->AddBrakeFriction(Vector3(0, 0, 0));
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

	/*switch (gearNumber) {
	case 0:
		engineForce = engineForce;
		break;
	case 1:
		engineForce = engineForce / 5;
		break;
	case 2:
		engineForce = (engineForce / 5) * 2;
		break;
	case 3:
		engineForce = (engineForce / 5) * 3;
		break;
	case 4:
		engineForce = (engineForce / 5) * 4;
		break;
	case 5:
		engineForce = engineForce;
		break;
	default:
		break;
	}*/
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
