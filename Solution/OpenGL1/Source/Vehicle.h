#ifndef VEHICLE_H
#define VEHICLE_H

#include "RigidBody.h"

class Vehicle : public RigidBody
{
public:
	Vehicle();
	void MoveForward(int dir, double dt);
	void MoveRight(int dir, double dt);
	void Brake(double dt);
	virtual void RollFront(float u, float v, double dt) = 0;
	virtual void RollBack(float u, float v, double dt) = 0;
	void SetStats(float thrustForce, float turningSpeed, float wheelRadius);
	void SetGear(int gear);
	int GetGear();
	float GetAngleY();
	~Vehicle();
protected:
	float thrustForce, turningSpeed;
	int gearNumber;
	float angleY;
	float wheelRadius;
	const float MAX_FORCE = 20000.f;
	const float BRAKE_FORCE = 1.f;
};

#endif // !VEHICLE_H