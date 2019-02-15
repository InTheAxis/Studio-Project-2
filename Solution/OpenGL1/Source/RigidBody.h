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
	void UpdateRotation(double dt);
	~RigidBody();
protected:
	Vector3 forward, up, right;
	float s, u, v, a;
	float theta, omegaI, omegaF, alpha;
	float forceForward, forceRight;
	float staticCoeff, maxStaticFriction, kineticFriction;
	float mass;
	float REV_FORCE; //derived const
	Mtx44 rotationMatrix;
	const float REV_FORCE_MULTIPLIER = 0.8f;
	const float GRAVITY = 9.8f;
	const float PI = 3.142f;

	void AddForceForward(Vector3 f); //add a force
	void AddForceRight(Vector3 f);
	void AddKineticFriction(Vector3 f);
};

#endif // !RIGIDBODY_H