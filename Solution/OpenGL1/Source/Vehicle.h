#ifndef VEHICLE_H
#define VEHICLE_H

#include "RigidBody.h"

class Vehicle : public RigidBody
{
public:
	Vehicle();
	void MoveForward(int dir, double dt);
	void MoveRight(int dir, double dt);
	void SetStats(float thrustForce, float turningSpeed);
	~Vehicle();
protected:
	float thrustForce, turningSpeed;
	int gearBox;
	float accelLimit;
};

#endif // !VEHICLE_H