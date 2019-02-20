#ifndef PARTICLE_EFFECT_H
#define PARTICLE_EFFECT_H
#include "Collectibles.h"

class CollectibleParticleEffect:public Collectibles
{
public:
	CollectibleParticleEffect();
	~CollectibleParticleEffect();
	virtual bool CheckAbsorption(Vector3 objectLocation);
	virtual void ApplyEffect(GameObject *object, double dt);

protected:

private:
	//float particleY[3] = {0.5f,0.75f,1.5f};
	//float particleZ[3] = { 0.5,1,2 };
	int particleIndex;
	float number;
};

#endif
