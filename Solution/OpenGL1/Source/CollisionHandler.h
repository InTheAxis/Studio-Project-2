#ifndef  COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#define _coll CollisionHandler::GetInstance()

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

	//overloaded checkers to handle each type of collision
	/*bool CheckCollision(Collidable* still, RigidBody* moving);
	bool CheckCollision(RigidBody* rb1, RigidBody* rb2);*/
	//overloaded resolvers to handle each type of collision
	void ResolveCollision(Collidable* c1, Collidable* c2); //generic one
	
	bool CheckCollision(Collidable* A, Collidable* B);

	~CollisionHandler();
private:
	CollisionHandler();
	static CollisionHandler* instance;

	Vector3 penetrationDist;

	const Vector3 INITIAL_DIR = Vector3(1, 1, 1);
	



	std::vector<Vector3> simplex; //up to 3-simplex
	Vector3 direction, pointA;
	Vector3 GetMPoint(Collidable* A, Collidable* B, Vector3 dir); //gets Minkowski diff
};

#endif // ! COLLISION_HANDLER_H