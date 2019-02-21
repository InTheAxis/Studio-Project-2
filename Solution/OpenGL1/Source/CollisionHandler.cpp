#include "CollisionHandler.h"


CollisionHandler* CollisionHandler::instance = nullptr;

CollisionHandler::CollisionHandler()
{
	this->penetrationDist = Vector3(0, 0, 0);
}

CollisionHandler * CollisionHandler::GetInstance()
{
	if (CollisionHandler::instance == nullptr)
	{
		instance = new CollisionHandler;
	}

	return instance;
}

//bool CollisionHandler::CheckCollision(Collidable* still, RigidBody* moving)
//{
//	return false;
//}
//
//bool CollisionHandler::CheckCollision(RigidBody* rb1, RigidBody* rb2)
//{
//	return false;
//}

void CollisionHandler::ResolveCollision(Collidable* c1, Collidable* c2)
{

}

CollisionHandler::~CollisionHandler()
{
}








//working GJK for 2D
bool CollisionHandler::CheckCollision(Collidable* A, Collidable* B)
{
	//init var
	direction = INITIAL_DIR;
	pointA = Vector3(0, 0, 0);
	simplex.clear();
	//get first point, and build 0-simplex
	pointA = GetMPoint(A, B, direction);
	if (pointA.Dot(direction) < 0)
		return false; //no intersection
	simplex.emplace_back(pointA);
	direction = -pointA;

	Vector3 b, c, acPerp, abPerp;
	while (true)
	{
		//get next point
		pointA = GetMPoint(A, B, direction);		
		//check if the point has passed the origin, if no then no intersect
		if (pointA.Length() == 0)
			return true; //intersect, A and B share same point
		if (pointA.Dot(direction) < 0)
			return false; //no intersection
		//add to simplex
		simplex.emplace_back(pointA); 
	
		//handle line segment, 1-simplex
		if (simplex.size() == 2)
		{
			b = simplex[0];
			direction = TripleCrossProduct(b - pointA, -pointA, b - pointA);
			if (direction.Length() == 0) //if a and b are exactly opposite, cross is zero
				direction = Vector3(b.x - pointA.x, 0, pointA.z - b.z); 
			continue; //skip to next iteration
		}

		//handling triangle, 2-simplex
		b = simplex[1];
		c = simplex[0];
		if (b.Length() - c.Length() < 0.0001f && b.Length() - pointA.Length() < 0.0001f) //prevent infinite loop if simplex has all same points
			return true;
		acPerp = TripleCrossProduct(b - pointA, c - pointA, c - pointA);
		
		if (acPerp.Dot(-pointA) > 0) //if beyond ac
		{
			direction = acPerp;
		}
		else //else beyond ab or in triangle
		{
			abPerp = TripleCrossProduct(c - pointA, b - pointA, b - pointA);

			if (abPerp.Dot(-pointA) < 0) //if within triangle
			{
				return true;
			}
			//else beyond ab
			std::swap(simplex[0], simplex[1]);

			direction = abPerp;
		}		

		std::swap(simplex[1], simplex[2]);
		simplex.pop_back(); //remove duplicate in simplex
	}

	return false;
}

Vector3 CollisionHandler::GetMPoint(Collidable *A, Collidable *B, Vector3 dir)
{
	Vector3 p1 = A->GetCollider()->GetFurthestPoint(dir);
	Vector3 p2 = B->GetCollider()->GetFurthestPoint(-dir);
	return p1 - p2;
}