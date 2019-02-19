#include "Collider.h"



Collider::Collider()
{
	this->objectMesh = MeshBuilder::GenerateAxes(1, 1, 1);
}

void Collider::PushToHullPoints(Vector3 p)
{
	this->hullPoints.emplace_back(p);
}

Collider::~Collider()
{
}
