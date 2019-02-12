#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "GameObject.h"

class RigidBody : public GameObject
{
public:
	RigidBody();
	~RigidBody();
private:
	Vector3 foward, up, right;
	float s, u, v, a, t;
};

#endif // !RIGIDBODY_H