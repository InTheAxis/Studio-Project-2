#ifndef  COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#define _coll CollisionHandler::GetInstance()
#define TOLERANCE 0.0001f

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
	bool CheckCollision2D(RigidBody* A, Collidable* B);
	bool CheckCollision(RigidBody* A, Collidable* B);
	//overloaded resolvers to handle each type of collision
	void ResolveCollision2D(RigidBody* A, Collidable* B); //generic one
	void ResolveCollision(RigidBody* A, Collidable* B);
	
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
	void CalculatePenetration2D(Collidable *A, Collidable *B);
	void CalculatePenetration(Collidable *A, Collidable *B);
	struct Edge
	{
		Edge() {}
		Edge(const Vector3 &a, const Vector3 &b)
		{
			points[0] = a; points[1] = b;
		}
		Vector3 points[2];
		float distance;
		Vector3 normal;
		int index; //for removing it
	};
	struct Face
	{
		Face() {}
		Face(const Vector3 &a, const Vector3 &b, const Vector3 &c)
		{
			Edge e1(a, b);
			edges[0] = e1;
			Edge e2(b, c);
			edges[1] = e2;
			Edge e3(c, a);
			edges[2] = e3;
			Vector3 ab = b - a;
			Vector3 ac = c - a;
			normal = ((ab).Cross(ac));
			if (!(normal.Length() < TOLERANCE))
				normal.Normalize();

			distance = Math::FAbs(a.Dot(normal));
		}
		float distance;
		Edge edges[3];
		Vector3 normal;
	};
};

#endif // ! COLLISION_HANDLER_H