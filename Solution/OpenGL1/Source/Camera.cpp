#include "Camera.h"

Camera::Camera()
{
}

void Camera::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	this->view = (target - position).Normalized();
	this->right = view.Cross(up);
	this->right.y = 0;
	this->right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
	this->prevCursorPos = Vector3(Application::cursorX, Application::cursorY, 0);

	InitDerived();
}

void Camera::ReInit(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = pos;
	this->target = target;
	this->view = (target - position).Normalized();
	this->right = view.Cross(up);
	this->right.y = 0;
	this->right.Normalize();
	this->up = right.Cross(view).Normalized();
	this->prevCursorPos = Vector3(Application::cursorX, Application::cursorY, 0);

	InitDerived();
}

Camera::~Camera()
{
}