#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"
#include "Wheel.h"

class Car : public Vehicle
{
public:
	Car();
	void RollFront(double dt);
	void RollBack(double dt);
	~Car();
protected:

};

#endif // !CAR_H