#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include "GameObject.h"
#include "Collider.h"

class Collidable : public GameObject
{
public:
	Collidable();
	~Collidable();
protected:
	Collider collider;
};

#endif

