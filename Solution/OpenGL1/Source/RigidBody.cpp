#include "RigidBody.h"



RigidBody::RigidBody()
{
	this->forward = up = right = Vector3(0, 0, 0);
	this->mass = s = u = v = a = 0;
	this->theta = omega = 0;
	this->staticCoeff = maxStaticFriction = kineticFriction = brakeFriction = 0;
	this->maxDrag = dragForce = 0;
	this->forceForward = forceRight = 0;
	this->REV_FORCE = 0;
	this->rotationMatrix.SetToIdentity();
}

//rmb to set stats first
void RigidBody::CreateRigidBody(Vector3 forward, float mass, float staticCoeff, float kineticCoeff)
{
	this->forward = forward;
	this->mass = mass;
	this->staticCoeff = staticCoeff;
	this->kineticFriction = kineticCoeff * GRAVITY * mass;
	this->maxStaticFriction = staticCoeff * GRAVITY * mass;
	this->REV_FORCE = maxStaticFriction * REV_FORCE_MULTIPLIER;

	if (maxStaticFriction < kineticCoeff)
		std::cout << "RigidBody: Static friction must be larger!" << std::endl;
}

void RigidBody::AddForceForward(Vector3 f)
{
	forceForward = f.z;
}

void RigidBody::AddForceRight(Vector3 f)
{
	forceRight = f.z;
}

void RigidBody::AddBrakeFriction(Vector3 f)
{
	brakeFriction = f.z;
}

void RigidBody::UpdateSuvat(double dt)
{
	//calc fnet and hence accel
	if (Math::FAbs(forceForward) + REV_FORCE > maxStaticFriction) //if static friction overcome start moving
	{
		//update accel
		this->a = (forceForward - kineticFriction - dragForce - brakeFriction) / mass;
		if (Math::FAbs(a) < 0.01f)
			a = 0;

		//update maxDrag
		this->maxDrag = int(forceForward - kineticFriction); //since both should be constant
		if (dragForce != maxDrag)
		{
			//update drag
			dragForce = MathExtended::Lerpf(dragForce, maxDrag, DRAG_RATE);
		}
	}
	else if (forceForward == 0) //means no pedal, friction shld kick in to slow down car
	{
		int direction = v / (Math::FAbs(v)); //1 or -1
		if (Math::FAbs(v) > 0.01f) //if within this range assume 0
		{
			//update accel in opp dir
			this->a = (-1 * direction * (kineticFriction + brakeFriction + 0.8f * dragForce)) / mass;

			if (dragForce != 0)
			{
				//update drag
				dragForce = -MathExtended::Lerpf(-dragForce, 0, DRAG_RATE);
			}
		}
		else
		{
			dragForce = 0;
			u = v = a = 0;
		}
	}
	this->v = u + a * float(dt); //calc final speed
	this->s = v * float(dt); //update displacement
	this->u = v; //update new initial speed
}

void RigidBody::UpdateRotation(double dt)
{
	if (Math::FAbs(forceRight) > 0 && Math::FAbs(v) > 2.2f)
	{
		omega = v / ((mass * Math::Square(v)) / forceRight);
		theta = omega * dt;
	}
	else if (Math::FAbs(theta) < 0.03f)
	{
		omega = theta = 0;
	}
}

RigidBody::~RigidBody()
{
}
