#include "AI.h"
#include "MyMath.h"
#include <iostream>

AI::AI()
{
	detected = true;
	turn = false;
	brakeState = false;
	brakeFriction = 1000.f;
	prevPos = NULL;
	redirect = false;
	first = true;
}

AI::~AI()
{
}

void AI::SetNextForward(Vector3 newTarget)
{
	this->nextForward = (newTarget - this->translate);//Gets new view vector 
	detected = false;
}

void AI::SetNewLocation(Vector3 pos)
{
	this->newPosition = pos; //set new destination
}

Vector3 AI::GetNewLocation()
{
	return this->newPosition; //gets new destination
}

void AI::CalcAngle()
{
	float angle;
	float numerator = forward.Dot(nextForward);
	float denominator = ((forward.Length()) * (nextForward.Length()));
	angle = acosf(numerator/denominator);
	angle = Math::RadianToDegree(angle); //calc angle from current view to destination
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
	if (first) //if first move, return true so it can set destination
	{
		first = false;
		return true;
	}
	if (((newPosition - translate).Length() < 5)) //if within 5 magnitude radius of the destination, return true to set new destination
	{
		detected = true;
	}
	else
	{
		detected = false; //else return false and continue moving
	}
	return detected;
}

bool AI::ReDirect(Vector3 pos)
{
	if (!detected) //if moving
	{
		if (this->prevPos == pos) //if stuck at same pos even though moving
		{
			redirect = true; //return true
			std::cout << "redirected " << std::endl;
			reCount++; //this adds to check if still stuck even though redirect is called (used to turn car away from building its stuck at)
		}
	}
	else
	{
		redirect = false; //else return false
		reCount = 0;
	}
	this->prevPos = pos; //saves previous position
	return redirect;
}

int AI::GetReCount()
{
	return reCount;
}

int AI::SetDir()
{
	int dir;
	if (forward.Cross(nextForward).y < 0) //checks which direction to turn and sets the direction
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

void AI::RollFront(float u, float v, float angle, double dt)
{
}

void AI::RollBack(float u, float v, double dt)
{
}