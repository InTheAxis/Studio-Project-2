#ifndef SPEEDBOOST_H
#define SPEEDBOOST_H
#include "Collectibles.h"
#include "MyMathExtended.h"

class CollectibleSpeedBoost :public Collectibles
{
public:
	CollectibleSpeedBoost();
	~CollectibleSpeedBoost();
	virtual bool CheckAbsorption(Vector3 objectLocation);
	virtual void ApplyEffect(GameObject *object,double dt);

protected:
	//float activeTime;
};

#endif


