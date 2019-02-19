#ifndef SPEEDBOOST_H
#define SPEEDBOOST_H
#include "Collectibles.h"

class SpeedBoost :public Collectibles
{
public:
	SpeedBoost();
	~SpeedBoost();
	virtual bool CheckAbsorption(Vector3 objectLocation);
	virtual void ApplyEffect(GameObject *object,double dt);

protected:
	//float activeTime;
};

#endif


