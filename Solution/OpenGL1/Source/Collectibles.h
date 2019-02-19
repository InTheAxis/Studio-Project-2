#ifndef COLLECTIBLES_H
#define COLLECTIBLES_H
#include "GameObject.h"
#include "Car.h"

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
	

protected:
	float maxActiveTime;
	float activeTime;
	
	bool PickedUp;

	const float PICKUP_RANGE = 0.5f;

	
};

#endif

