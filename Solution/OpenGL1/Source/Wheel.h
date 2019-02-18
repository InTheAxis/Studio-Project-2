#ifndef WHEEL_H
#define WHEEL_H

#include "GameObject.h"

class Wheel : public GameObject
{
public:
	Wheel();
	void Roll(float u, float v, double dt);
	void SetRadius(float);
	~Wheel();
private:
	float omegaI, omegaF, theta, radius;
};


#endif // !WHEEL_H