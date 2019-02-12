#include "Camera1.h"

Camera1::Camera1()
{
}

void Camera1::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	this->view = (target - position).Normalized();
	this->right = view.Cross(up);
	this->right.y = 0;
	this->right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
	this->view = this->target - this->position;
}

void Camera1::ReInit(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = pos;
	this->target = target;
	this->view = (target - position).Normalized();
	this->right = view.Cross(up);
	this->right.y = 0;
	this->right.Normalize();
	this->up = right.Cross(view).Normalized();
	this->view = this->target - this->position;
}

void Camera1::Update(double dt, Vector3 target, bool captureMouse)
{
	this->target = target;

	if (Application::IsKeyPressed(VK_LEFT))
	{
		rotationMatrixP.SetToRotation(CAM_SPEED * dt, 0, 1, 0);
		this->position = rotationMatrixP * position;
		this->offset = rotationMatrixP * offset;
	}
	if (Application::IsKeyPressed(VK_RIGHT))
	{
		rotationMatrixP.SetToRotation(-CAM_SPEED * dt, 0, 1, 0);
		this->position = rotationMatrixP * position;
		this->offset = rotationMatrixP * offset;
	}

	this->position = target + offset;
	this->view = (position - target).Normalized();
	this->right = (view.Cross(Vector3(0, 1, 0))).Normalized();
	this->up = (right.Cross(view)).Normalized();

	//if (Application::IsKeyPressed(VK_UP))
	//{
	//	float pitch = (float)(MOVE_SPEED * dt);
	//	rotationMatrixP.SetToRotation(pitch, 0, 1, 0);
	//	view = rotationMatrixP * view;
	//	right = (view.Cross(Vector3(0,1,0))).Normalize();
	//	up = (right.Cross(view)).Normalize();
	//}
	//if (Application::IsKeyPressed(VK_DOWN))
	//{
	//	float pitch = (float)(MOVE_SPEED * dt);
	//	rotationMatrixP.SetToRotation(-pitch, 0, 1, 0);
	//	view = rotationMatrixP * view;
	//	right = (view.Cross(Vector3(0, 1, 0))).Normalize();
	//	up = (right.Cross(view)).Normalize();
	//}
}

void Camera1::ToggleNoClip()
{
}

void Camera1::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
	this->ReInit(position, target, up);
}

Camera1::~Camera1()
{
}