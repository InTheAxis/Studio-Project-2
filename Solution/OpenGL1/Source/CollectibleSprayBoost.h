#ifndef SPRAYBOOST_H
#define SPRAYBOOST_H

#include "Collectibles.h"
#include "Application.h"
#include "Paintable.h"

class CollectibleSprayBoost :public Collectibles
{
public:
	CollectibleSprayBoost();
	~CollectibleSprayBoost();
	virtual bool CheckAbsorption(Vector3 objectLocation);
	virtual void ApplyEffect(GameObject *object, double dt);
	virtual bool GetPickedUp();
	//void ApplyEffect(Paintable *object, double dt);
protected:
	bool pickedUp;
	float activeTime;
	float maxActiveTime;
};

#endif