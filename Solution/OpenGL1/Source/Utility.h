#ifndef UTILITY_H
#define UTILITY_H
#include "Vertex.h"
#include "Mtx44.h"

Position operator*(const Mtx44 &lhs, const Position &rhs);

//A class to contain two vec3 and a helper function
class Plane 
{
public:
	Plane();
	~Plane();
	Plane(Vector3 n, Vector3 p);
	float DistancePointPlane(Vector3 targetPoint);
	Vector3 normal;
	Vector3 point;
};
#endif

