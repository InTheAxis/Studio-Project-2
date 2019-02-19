#ifndef COLLIDER_H
#define COLLIDER_H

#include "GameObject.h"

class Collider : public GameObject
{
public:
	Collider();
	void PushToHullPoints(Vector3);
	~Collider();
private:
	std::vector<Vector3> hullPoints; //defining the enclosing convex hull
};
#endif

