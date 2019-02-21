#ifndef VEHICLE_H
#define VEHICLE_H

#include "RigidBody.h"
#include "Paint.h"

class Vehicle : public RigidBody
{
public:
	Vehicle();
	void MoveForward(int dir, double dt);
	void MoveRight(int dir, double dt);
	void TorqueRotation(int dir, double dt);
	void Brake(bool brake);
	
	//getter setters
	void SetStats(float engineForce, float brakeFriction, float turningForce, float wheelRadius);
	void SetGear(int gear);
	int GetGear();
	float GetEngineForce();
	float GetBrakeFriction();
	float GetTurningForce();
	Vector3 GetAngle(); //ignore x and z
	Paint* GetPaint();

	virtual void RollFront(float u, float v, float angle, double dt) = 0;
	virtual void RollBack(float u, float v, double dt) = 0;
	~Vehicle();
protected:
	float engineForce, brakeFriction, turningForce;
	int gearNumber;
	float wheelRadius;
	float angleY;
	float torqueForce;

	Paint paint;
};

#endif // !VEHICLE_H