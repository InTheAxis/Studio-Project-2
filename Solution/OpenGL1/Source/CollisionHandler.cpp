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

bool CollisionHandler::CheckCollision(Collidable* still, RigidBody* moving)
{
	return false;
}

bool CollisionHandler::CheckCollision(RigidBody* rb1, RigidBody* rb2)
{
	return false;
}

void CollisionHandler::ResolveCollision(Collidable* c1, Collidable* c2)
{

}

CollisionHandler::~CollisionHandler()
{
}








//partially working GJK

//bool CollisionHandler::CheckCollision(Collidable* A, Collidable* B)
//{
//	//init var
//	direction = INITIAL_DIR;
//	pointA = Vector3(0, 0, 0);
//	simplex.clear();
//	//get first point, and build 0-simplex
//	pointA = GetMPoint(A, B, direction);
//	simplex.emplace_back(pointA);
//	direction = -pointA;
//
//	while (true)
//	{
//		//get next point
//		pointA = GetMPoint(A, B, direction);
//		
//		//check if the point has passed the origin, if no then no intersect
//		if (pointA.Dot(direction) < 0)
//		{
//			return false; //no intersection
//		}
//
//		//add to simplex
//		simplex.emplace_back(pointA); 
//
//		//update simplex and direction, and check if origin is in simplex
//		if (EvolveSimplex(&simplex, &direction)) 
//		{
//			return true; //intersection
//		}
//	}
//}

//Vector3 CollisionHandler::GetMPoint(Collidable *A, Collidable *B, Vector3 dir)
//{
//	Vector3 p1 = A->GetCollider()->GetFurthestPoint(dir);
//	Vector3 p2 = B->GetCollider()->GetFurthestPoint(-dir);
//	return p1 - p2;
//}

//bool CollisionHandler::EvolveSimplex(std::vector<Vector3> *simplex, Vector3 *dir)
//{
//	Vector3 a, b, c;
//	a = simplex->back();
//
//	switch (simplex->size())
//	{
//		case 2:
//		{
//			b = (*simplex)[0];
//			if ((b - a).Dot(-a) > 0)
//			{
//				*dir = TripleCrossProduct(b - a, -a, b - a);
//			}
//			else
//			{
//				*dir = -a;
//				simplex->erase(simplex->begin()); //remove b
//			}
//			break;
//		}
//		case 3:
//		{
//			c = (*simplex)[0];
//			b = (*simplex)[1];
//
//			Vector3 abcPerp = (c - a).Cross(b - a);
//			Vector3 abPerp = TripleCrossProduct(c - a, b - a, b - a);
//			Vector3 acPerp = TripleCrossProduct(b - a, c - a, c - a);
//
//			if(acPerp.Dot(-a) > 0)
//			{
//				if ((c - a).Dot(-a) > 0)
//				{
//					*dir = TripleCrossProduct(c - a, -a, c - a);
//					simplex->erase(simplex->begin() + 1); //remove b
//				}
//				else
//				{
//					//*repeated
//					if ((b - a).Dot(-a) > 0)
//					{
//						*dir = TripleCrossProduct(b - a, -a, b - a);
//						simplex->erase(simplex->begin()); //remove c
//					}
//					else
//					{
//						*dir = -a;
//						simplex->erase(simplex->begin()); //remove c
//						simplex->erase(simplex->begin()); //remove b
//					}
//				}
//			}
//			else
//			{
//				//*repeated
//				if (abPerp.Dot(-a) > 0)
//				{
//					if ((b - a).Dot(-a) > 0)
//					{
//						*dir = TripleCrossProduct(b - a, -a, b - a);
//						simplex->erase(simplex->begin()); //remove c
//					}
//					else
//					{
//						*dir = -a;
//						simplex->erase(simplex->begin()); //remove c
//						simplex->erase(simplex->begin()); //remove b
//					}
//				}
//				else
//				{
//					if (abcPerp.Dot(-a) > 0)
//					{
//						*dir = abcPerp;
//					}
//					else
//					{
//						*dir = -abcPerp;
//						Vector3 temp = (*simplex)[0];
//						(*simplex)[0] = (*simplex)[1];
//						(*simplex)[1] = temp;
//					}
//					return true;
//				}
//			}
//			break;
//		}
//		case 4:
//		{
//			break;
//		}
//	}
//
//	return false;
//}

