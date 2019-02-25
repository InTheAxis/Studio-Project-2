#include "CollectibleParticleEffect.h"

CollectibleParticleEffect::CollectibleParticleEffect()
{
	/*particleIndex = 0;*/
	number = 2;
}

CollectibleParticleEffect::~CollectibleParticleEffect()
{
}

bool CollectibleParticleEffect::CheckAbsorption(Vector3 objectLocation)
{
	return false;
}

void CollectibleParticleEffect::ApplyEffect(GameObject* object, double dt)
{
	//particleIndex++;
	number += 5*dt;
	if (number > 4)
		number = 2;
	//rotate.y = object->GetRotate().y;
	translate = Vector3(0, number/4,-number);
	if (particleIndex >= 3)
		particleIndex = 0;
}

