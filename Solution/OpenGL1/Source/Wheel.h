#ifndef WHEEL_H
#define WHEEL_H

#include "GameObject.h"

class Wheel : public GameObject
{
public:
	Wheel();
	void RollFront(float u, float v, float angle, double dt);
	void RollBack(float u, float v, double dt);
	void SetRadius(float);
	float AddTorqueForce();
	~Wheel();
private:
	float omegaI, omegaF, theta, radius;
	float torqueForce;
};


#endif // !WHEEL_H