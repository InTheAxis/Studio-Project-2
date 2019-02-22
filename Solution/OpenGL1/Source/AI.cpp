#include "AI.h"
#include "MyMath.h"
#include <iostream>

AI::AI()
{
	spotCount = 1;
	detected = true;
	turn = false;
	brakeState = false;
	brakeFriction = 30000.f;
}

AI::~AI()
{
}

void AI::SetNextForward(Vector3 newTarget)
{
	this->newPosition = newTarget;
	this->nextForward = (newTarget - this->translate);//Gets new view vector
	detected = false;
}

void AI::CalcAngle()
{
	float angle;
	float numerator = forward.Dot(nextForward);
	float denominator = ((forward.Length()) * (nextForward.Length()));
	angle = acosf(numerator/denominator);
	angle = Math::RadianToDegree(angle);
	if (angle > 5)
	{
		turn = true;
	}
	else
	{
		turn = false;
	}
}

bool AI::CheckToMove()//temporary test
{
	if (((newPosition - translate).Length() < 1))
	{
		detected = true;
	}
	else
	{
		detected = false;
	}
	return detected;
}

int AI::SetDir()
{
	int dir;
	if (forward.Cross(nextForward).y < 0)
	{
		dir = 1;
	}
	else
	{
		dir = -1;
	}
	return dir;
}

bool AI::IfTurn()
{
	return turn;
}

bool AI::IfDetected()
{
	return detected;
}

int AI::CheckBrake()
{
	spotCount++;
	return spotCount;
}

void AI::IncrementBrake(float x)
{
	if (this->u > 0)
		brakeFriction += x;
	else
		this->u = 0;
}

void AI::RollFront(float u, float v, float angle, double dt)
{
}

void AI::RollBack(float u, float v, double dt)
{
}