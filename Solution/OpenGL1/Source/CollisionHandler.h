#ifndef  COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#define _coll CollisionHandler::GetInstance()
#define TOLERANCE 0.000000001f

#include "Vector3.h"
#include "Collider.h"
#include "Collidable.h"
#include "RigidBody.h"
#include "Utility.h"

//singleton class to handle collision check and resolution

class CollisionHandler
{
public:
	static CollisionHandler* GetInstance();

	//using gjk
	bool CheckCollision(RigidBody* A, Collidable* B);
	bool CheckCollision3D(RigidBody* A, Collidable* B);
	//overloaded resolvers to handle each type of collision
	void ResolveCollision(RigidBody* A, Collidable* B); //generic one
	
	Vector3 penetrationDist;

	~CollisionHandler();
private:
	CollisionHandler();
	static CollisionHandler* instance;


	const Vector3 INITIAL_DIR = Vector3(1, 1, 1);
	
	//for gjk
	std::vector<Vector3> simplex, simplexCopy; //up to 3-simplex for gjk
	Vector3 direction, pointA;
	Vector3 GetMPoint(Collidable* A, Collidable* B, Vector3 dir); //gets Minkowski diff
	//for epa
	void CalculatePenetration(Collidable *A, Collidable *B);
	struct Edge
	{
		float distance;
		Vector3 normal;
		int index;
	};
};

#endif // ! COLLISION_HANDLER_H