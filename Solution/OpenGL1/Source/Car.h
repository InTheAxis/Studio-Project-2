#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"
#include "Wheel.h"

class Car : public Vehicle
{
public:
	Car();
	virtual void RollFront(float u , float v, float angle, double dt);
	virtual void RollBack(float u, float v, double dt);
	~Car();
	Wheel wheels[4];
private:
};

#endif // !CAR_H