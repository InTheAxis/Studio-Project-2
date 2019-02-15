#include "RigidBody.h"



RigidBody::RigidBody()
{
	this->forward = up = right = Vector3(0, 0, 0);
	this->s = u = v = a = 0;
	this->theta = omegaI = omegaF = alpha = 0;
	this->staticCoeff = maxStaticFriction = kineticFriction = 0;
	this->mass = 0;
	this->forceForward = forceRight = 0;
	this->rotationMatrix.SetToIdentity();
}

void RigidBody::CreateRigidBody(Vector3 forward, float mass, float staticCoeff, float kineticCoeff)
{
	this->forward = forward;
	this->mass = mass;
	this->staticCoeff = staticCoeff;
	this->kineticFriction = kineticCoeff * GRAVITY * mass;
	this->maxStaticFriction = staticCoeff * GRAVITY * mass;

	if (maxStaticFriction < kineticCoeff)
		std::cout << "RigidBody: Static friction must be larger!" << std::endl;
}

void RigidBody::AddForceForward(Vector3 f)
{
	forceForward += f.z;
}

void RigidBody::AddForceRight(Vector3 f)
{
	forceRight += f.y;
}

void RigidBody::UpdateSuvat(double dt)
{
	//calc fnet and hence accel
	if (Math::FAbs(forceForward) > maxStaticFriction) //if static friction overcome start moving
	{
		this->a = (forceForward - kineticFriction) / mass;
	}
	else if (forceForward == 0) //means no pedal, friction shld kick in to slow down car
	{
		int direction = v / (Math::FAbs(v)); //1 or -1
		if (Math::FAbs(v) > 0.1f)
		{
			this->a = (-1 * direction * kineticFriction) / mass;
		}
		else
		{
			u = v = a = 0;
		}
	}
	this->v = u + a * float(dt); //calc final speed
	this->s = v * float(dt); //update displacement
	this->u = v; //update new initial speed
}

void RigidBody::UpdateRotation(double dt)
{
	//if (Math::FAbs(forceRight) > maxStaticFriction)
	{
		this->alpha = (forceRight - kineticFriction) / mass;
	}
	//else
	{
		//omegaI = omegaF = alpha = 0;
	}
	this->omegaF = omegaI + alpha * float(dt);
	this->theta = 0.5 * (omegaI + omegaF) * float(dt);
	this->omegaI = omegaF;

	//std::cout << "I :" << omegaI << std::endl;
	//std::cout << "F :" << omegaF << std::endl;
	//std::cout << "A :" << alpha << std::endl;
	//std::cout << "T :" << theta << std::endl;
}

RigidBody::~RigidBody()
{
}
