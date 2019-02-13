#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "GameObject.h"
#include "Mtx44.h"

class RigidBody : public GameObject
{
public:
	RigidBody();
	void CreateRigidBody(Vector3 forward, float mass, float staticCoeff, float kineticCoeff);
	void UpdateSuvat(double dt);
	~RigidBody();
protected:
	Vector3 forward, up, right;
	float s, u, v, a;
	float forceForward, forceRight;
	float staticCoeff, maxStaticFriction, kineticFirction;
	float mass;

	Mtx44 rotationMatrix;

	void AddForce(Vector3 f); //add a force
	
	
	const float GRAVITY = 9.8;
};

#endif // !RIGIDBODY_H