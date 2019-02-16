#include "RigidBody.h"



RigidBody::RigidBody()
{
	this->forward = up = right = Vector3(0, 0, 0);
	this->s = u = v = a = 0;
	this->theta = omegaI = omegaF = alpha = 0;
	this->forceForward = forceRight = 0;
	this->mass = staticCoeff = maxStaticFriction = kineticFriction = brakeFriction = 0;
	this->REV_FORCE = 0;
	this->maxDrag = 0;
	this->dragForce = 10;
	this->frameNum = 1;
	this->rotationMatrix.SetToIdentity();
}

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
	forceForward += f.z;
}

void RigidBody::AddForceRight(Vector3 f)
{
	forceRight += f.y;
}

void RigidBody::AddBrakeFriction(Vector3 f)
{
	brakeFriction = f.z;
}

void RigidBody::InitMaxThrustForce(float thrustForce)
{
	maxDrag = thrustForce - (kineticFriction + brakeFriction);
}

//int maxDrag = max force -friction
//maxDrag = maxDrag / frameNum + maxDrag / frameNum + maxDrag / frameNum ....
//frameNum = currentNum * 2 , OR currentNum << 1 

void RigidBody::UpdateSuvat(double dt)
{
	//calc fnet and hence accel
	if ((Math::FAbs(forceForward) + REV_FORCE) > maxStaticFriction) //if static friction overcome start moving
	{
		frameNum *=  2;
		dragForce += (dragForce / frameNum);
		
		this->a = (forceForward - (kineticFriction + brakeFriction + dragForce)) / mass;
	}
	else if (forceForward == 0) //means no pedal, friction shld kick in to slow down car
	{
		int direction = v / (Math::FAbs(v)); //1 or -1
		if (Math::FAbs(v) > 0.1f)
		{
			this->a = (-1 * direction * (kineticFriction + brakeFriction)) / mass;
		}
		else
		{
			u = v = a = 0;
		}
	}
	this->v = u + a * float(dt); //calc final speed
	this->s = v * float(dt); //update displacement
	this->u = v; //update new initial speed

	//std::cout << "Drag: " << dragForce << std::endl;
	//std::cout << "Accel: " << a << std::endl;
	//std::cout << "FrameNum: " <<  frameNum << std::endl;
}

void RigidBody::UpdateRotation(double dt)
{
	if (Math::FAbs(forceRight) > maxStaticFriction)
	{
		this->alpha = (forceRight - kineticFriction) / mass;
	}
	else
	{
		omegaI = omegaF = alpha = 0;
	}
	this->omegaF = omegaI + alpha * float(dt);
	this->theta = 0.5 * (omegaI + omegaF) * float(dt);
	this->omegaI = omegaF;
}

RigidBody::~RigidBody()
{
}
