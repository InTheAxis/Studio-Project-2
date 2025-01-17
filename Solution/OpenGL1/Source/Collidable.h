#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include "GameObject.h"
#include "Collider.h"

class Collidable : public GameObject
{
public:
	Collidable();
	//define a collider shape, which assumes object is initialised axis aligned
	void DefineRect2DCollider(Vector3 size);
	void DefineBoxCollider(Vector3 size);
	void DefineCircle2DCollider(Vector3 radius);

	Collider* GetCollider();

	void UpdateCollider();
	~Collidable();
protected:
	Collider* collider;
};

#endif

