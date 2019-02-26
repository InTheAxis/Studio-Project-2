#include "Collider.h"



Collider::Collider()
{
	this->objectMesh = MeshBuilder::GenerateAxes(0.5f, 0.5f, 0.5f);
	for (int i = 0; i < 3; ++i)
		rotationMatrix[i].SetToIdentity();
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
		/*actual transformations*/
		hullPoints[i] = rotationMatrix[1] * startingPoints[i];
		hullPoints[i] += translate;

		/*transformations for rendering*/
		//removing scale when generating mesh
		Vector3 temp = Vector3(hullPoints[i].x / scale.x, hullPoints[i].y / scale.y, hullPoints[i].z / scale.z);

		//draw lines from first half ot second half remove the scale
		if (i < hullPoints.size() * 0.5f)
			lineStart.emplace_back(temp);
		else
			lineEnd.emplace_back(temp);
	}
	
	//generate the mesh to be rendered
	this->objectMesh = MeshBuilder::GenerateLines(lineStart, lineEnd, Color(1.f, 0.f, 1.f)); 
	lineEnd.clear();
	lineStart.clear();
}

Vector3 Collider::GetFurthestPoint(Vector3 dir)
{
	Vector3* ret = nullptr;
	float distance = 0, maxDist = -999999999999;
	for (Vector3 &v : hullPoints)
	{
		distance = v.Dot(dir);
		if (distance > maxDist)
		{
			maxDist = distance;
			ret = &v;
		}
	}
	if (ret)
		return *ret;
	else
		std::cout << "Error: no point found?";
}

Collider::~Collider()
{
}
