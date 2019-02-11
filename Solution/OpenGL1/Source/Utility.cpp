#include "Utility.h"

Position operator*(const Mtx44 &lhs, const Position &rhs)
{
	float b[4];
	for (int i = 0; i < 4; i++)
	{
		b[i] = lhs.a[0 * 4 + i] * rhs.x + lhs.a[1 * 4 + i] 
			* rhs.y + lhs.a[2 * 4 + i] * rhs.z 
			+ lhs.a[3 * 4 + i] * 1;
	}
	
	return Position(b[0], b[1], b[2]);
}

Plane::Plane()
{
}

Plane::~Plane()
{
}

Plane::Plane(Vector3 n, Vector3 p)
{
	this->normal = n;
	this->point = p;
}

float Plane::DistancePointPlane(Vector3 targetPoint)
{
	normal.Normalize();
	float distPlaneFromO = this->point.Dot(normal);
	float distPointfromO = targetPoint.Dot(normal);

	return distPointfromO - distPlaneFromO;
}