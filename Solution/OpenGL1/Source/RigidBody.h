#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "GameObject.h"
#include "Mtx44.h"
#include "MyMathExtended.h"
#include "Collidable.h"

class RigidBody : public Collidable
{
public:
	RigidBody();
	void CreateRigidBody(Vector3 forward, float mass, float staticCoeff, float kineticCoeff);
	void UpdateSuvat(double dt);
	void UpdateRotation(double dt);
	void UpdateTorque(double dt);

	void SetTorque(float leverArm, float torqueForce, float lengthA, float lengthB);
	float GetSpeed();
	~RigidBody();
protected:
	Vector3 forward, up, right;
	float mass, s, u, v, a;
	float theta, omega;
	float staticCoeff, maxStaticFriction, kineticFriction;
	float maxDrag, dragForce;

	float forceForward, forceRight, brakeFriction;
	float REV_FORCE; //derived const to help with starting car

	Vector3 torque, leverArm, torqueForce;
	float momentOfInertia, lengthA, lengthB;
	float torqueTheta;

	float forwardCollisionForce, rightCollisionForce;

	Mtx44 rotationMatrix;

	const float DRAG_RATE = 0.01f;
	const float REV_FORCE_MULTIPLIER = 0.8f;
	const float GRAVITY = 9.8f;

	void AddForceForward(Vector3 f); //add a force
	void AddForceRight(Vector3 f);
	void AddBrakeFriction(float brakeFriction);
	void AddTorqueForce(float torqueForce);
	void AddCollisionForce(float forwardCollisionForce, float rightCollisionForce);
};

#endif // !RIGIDBODY_H