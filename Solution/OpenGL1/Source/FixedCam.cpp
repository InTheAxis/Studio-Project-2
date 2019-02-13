#include "FixedCam.h"

FixedCam::FixedCam()
{
}

void FixedCam::InitDerived()
{
	rotationMatrixP.SetToIdentity();
}

void FixedCam::Update(double dt, Vector3 translate, Vector3 rotate)
{
	this->target = translate;

	rotationMatrixP.SetToRotation(rotate.y * dt, 0, 1, 0);
	this->position = rotationMatrixP * position;
	this->offset = rotationMatrixP * offset;

	this->position = target + offset;
	this->view = (position - target).Normalized();
	this->right = (view.Cross(Vector3(0, 1, 0))).Normalized();
	this->up = (right.Cross(view)).Normalized();
}

void FixedCam::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
	this->ReInit(position, target, up);
}

FixedCam::~FixedCam()
{
}