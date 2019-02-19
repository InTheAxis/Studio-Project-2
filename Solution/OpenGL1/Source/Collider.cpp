#include "Collider.h"



Collider::Collider()
{
	this->objectMesh = MeshBuilder::GenerateAxes(0.5f, 0.5f, 0.5f);
	for (int i = 0; i < 3; ++i)
		rotationMatrix[0].SetToIdentity();
}

void Collider::PushToHullPoints(Vector3 p)
{
	this->hullPoints.emplace_back(p);
	this->startingPoints.emplace_back(p);
}

void Collider::UpdateHull(Vector3 translate, Vector3 rotate)
{
	rotationMatrix[1].SetToRotation(rotate.y, 0, 1, 0); //only handle y rotation for now
	for (int i = 0; i < hullPoints.size(); ++i)
	{
		hullPoints[i] = rotationMatrix[1] * startingPoints[i];
		hullPoints[i] += translate;

		if (i < hullPoints.size() * 0.5f)
			lineStart.emplace_back(hullPoints[i] - translate);
		else
			lineEnd.emplace_back(hullPoints[i] - translate);
	}

	this->objectMesh = MeshBuilder::GenerateLines(lineStart, lineEnd, Color(1.f, 0.f, 1.f));
	lineEnd.clear();
	lineStart.clear();
}

Collider::~Collider()
{
}
