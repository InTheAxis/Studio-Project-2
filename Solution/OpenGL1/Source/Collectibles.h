#ifndef COLLECTIBLES_H
#define COLLECTIBLES_H
#include "GameObject.h"
#include "Car.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>

class Collectibles :public GameObject
{
public:
	Collectibles();
	~Collectibles();
	virtual bool CheckAbsorption(Vector3 objectLocation) = 0;
	virtual void ApplyEffect(GameObject *object,double dt) = 0;
	float GetActiveTime();
	void SetActiveTime();
	bool GetPickedUp();
	void SetPickedUp(bool PickedUp);
	float RandomNumberGenerator();

protected:
	float maxActiveTime;
	float activeTime;
	
	bool pickedUp;

	const float PICKUP_RANGE = 0.5f;
	float MapRange = 100;
	
};

#endif

