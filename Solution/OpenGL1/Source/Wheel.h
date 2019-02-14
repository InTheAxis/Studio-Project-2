#ifndef WHEEL_H
#define WHEEL_H

#include "GameObject.h"
#include "Car.h"

class Wheel : public GameObject
{
public:
	Wheel();
	void Roll(double dt);
	~Wheel();
protected:

};


#endif // !WHEEL_H