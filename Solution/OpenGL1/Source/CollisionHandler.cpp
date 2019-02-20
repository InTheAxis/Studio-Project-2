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

bool CollisionHandler::CheckCollision(Collidable* A, Collidable* B)
{
	//init var
	direction = INITIAL_DIR;
	pointA = Vector3(0, 0, 0);
	simplex.clear();
	//get first point, and build 0-simplex
	pointA = GetMPoint(A, B, direction);
	simplex.emplace_back(pointA);
	direction = -pointA;

	while (true)
	{
		//get next point
		pointA = GetMPoint(A, B, direction);
		
		//check if the point has passed the origin, if no then no intersect
		if (pointA.Dot(direction) < 0)
		{
			return false; //no intersection
		}

		//add to simplex
		simplex.emplace_back(pointA); 

		//update simplex and direction, and check if origin is in simplex
		if (EvolveSimplex(&simplex, &direction)) 
		{
			return true; //intersection
		}
	}
}

void CollisionHandler::ResolveCollision(Collidable* A, Collidable* B)
{

}

Vector3 CollisionHandler::GetMPoint(Collidable *A, Collidable *B, Vector3 dir)
{
	Vector3 p1 = A->GetCollider()->GetFurthestPoint(dir);
	Vector3 p2 = B->GetCollider()->GetFurthestPoint(-dir);
	return p1 - p2;
}

bool CollisionHandler::EvolveSimplex(std::vector<Vector3> *simplex, Vector3 *dir)
{
	Vector3 a, b, c;
	a = simplex->back();

	if (simplex->size() == 3)
	{
		c = (*simplex)[0];
		b = (*simplex)[1];

		Vector3 abPerp = TripleCrossProduct(c - a, b - a, b - a);
		Vector3 acPerp = TripleCrossProduct(b - a, c - a, c - a);

		if (abPerp.Dot(-a) > 0) 
		{
			simplex->erase(simplex->begin());//remove c
			*dir = abPerp;
		}
		else 
		{
			// is the origin in R3
			if (acPerp.Dot(-a) > 0) 
			{
				simplex->erase(simplex->begin() + 1); //remove b
				*dir = acPerp;
			}
			else 
			{
				return true; //fourth point is within triangle
			}
		}
	}
	else
	{
		b = (*simplex)[0];
		*dir = TripleCrossProduct(b - a, -a, b - a);
	}
	return false;
}

CollisionHandler::~CollisionHandler()
{
}
