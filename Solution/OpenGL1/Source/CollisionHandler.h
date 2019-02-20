#ifndef  COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#define _coll CollisionHandler::GetInstance()

#include "Vector3.h"
#include "Collider.h"
#include "Collidable.h"
#include "Utility.h"

//singleton class to handle collision check and resolution

class CollisionHandler
{
public:
	static CollisionHandler* GetInstance();

	//recieves two objects, returns a bool if true
	bool CheckCollision(Collidable* A, Collidable* B);
	//overloaded resolvers to handle each type of collision
	void ResolveCollision(Collidable* A, Collidable* B); //generic one
	
	~CollisionHandler();
private:
	CollisionHandler();
	static CollisionHandler* instance;
	
	Vector3 GetMPoint(Collidable* A, Collidable* B, Vector3 dir); //gets Minkowski point
	bool EvolveSimplex(std::vector<Vector3> *simplex, Vector3 *dir);

	std::vector<Vector3> simplex; //up to 3-simplex
	Vector3 direction, pointA;
	Vector3 penetrationDist;

	const Vector3 INITIAL_DIR = Vector3(1, 1, 1);
};

#endif // ! COLLISION_HANDLER_H