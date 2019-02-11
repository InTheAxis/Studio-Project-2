#include "Camera2.h"

Camera2::Camera2()
{
}

void Camera2::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	this->view = (target - position).Normalized();
	this->right = view.Cross(up);
	this->right.y = 0;
	this->right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
	this->yaw = pitch = 0;
	this->noclip = true;
	this->disableMovement = false;
	this->disableCamMovement = false;
}

void Camera2::ReInit(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position =  pos;
	this->target = target;
	this->view = (target - position).Normalized();
	this->right = view.Cross(up);
	this->right.y = 0;
	this->right.Normalize();
	this->up = right.Cross(view).Normalized();
	this->yaw = pitch = 0;
}

void Camera2::Update(double dt, Vector3 angles, bool captureMouse)
{
	if (!disableCamMovement)
	{
		//inputs
		if (!captureMouse) //for keyboard
		{
			if (Application::IsKeyPressed(VK_UP))
			{
				angles.y += CAM_DEADZONE + 100 * CAM_SPEED * dt;
			}
			else if (Application::IsKeyPressed(VK_DOWN))
			{
				angles.y -= CAM_DEADZONE + 100 * CAM_SPEED * dt;
			}
			if (Application::IsKeyPressed(VK_LEFT))
			{
				angles.x += CAM_DEADZONE + 100 * CAM_SPEED * dt;
			}
			else if (Application::IsKeyPressed(VK_RIGHT))
			{
				angles.x -= CAM_DEADZONE + 100 * CAM_SPEED * dt;
			}
		}
		//else do nothing for mouse
		//preventing y overflow, 0.95f (out of 1) is the max i allowed
		if ((view.y > 0.95f && angles.y > 0) || (view.y < -0.95f && angles.y < 0))
			angles.y = 0;
		//if magnitude > deadzone, rotate by yaw, else reset yaw
		if (Math::FAbs(angles.x) > CAM_DEADZONE)
			yaw = (float)(angles.x * CAM_SPEED * dt);
		else
			yaw = 0;
		//if magnitude > deadzone, rotate by pitch, else reset pitch
		if (Math::FAbs(angles.y) > CAM_DEADZONE)
			pitch = (float)(angles.y * CAM_SPEED * dt);
		else
			pitch = 0;		
		//setting matrices
		rotationMatrixP.SetToRotation(pitch, right.x, right.y, right.z);
		rotationMatrixY.SetToRotation(yaw, 0, 1, 0);
		//multiply!
		view = (rotationMatrixP * rotationMatrixY * view).Normalize();
		//calculate the other two vectors, assuming camera is never upside down
		right = (view.Cross(Vector3(0, 1, 0))).Normalize();
		up = (right.Cross(view)).Normalize();

		//the trigo method
		//use += and -= with pitch and yaw instead, more expensive but easier explain
		/*view.x = sinf(Math::DegreeToRadian(yaw));
		view.y = tanf(Math::DegreeToRadian(pitch));
		view.z = cosf(Math::DegreeToRadian(yaw));*/
	}
	if (!disableMovement)
	{
		if (noclip)
		{
			if (Application::IsKeyPressed(VK_SPACE))
			{
				position.y = position.y + up.y * MOVE_SPEED * static_cast<float>(dt);
			}
			if (Application::IsKeyPressed(VK_LSHIFT))
			{
				position.y = position.y - up.y * MOVE_SPEED * static_cast<float>(dt);
			}
		}
		else
		{
			if (Application::IsKeyPressed(VK_LSHIFT))
			{
				position.y = position.y - up.y * MOVE_SPEED * static_cast<float>(dt);

				if (position.y < CROUCH_HEIGHT)
					position.y = CROUCH_HEIGHT;
			}
		}

		if (Application::IsKeyPressed('W'))
		{
			position.x = position.x + view.x * MOVE_SPEED * static_cast<float>(dt);
			position.z = position.z + view.z * MOVE_SPEED * static_cast<float>(dt);
			target = position + view;
		}
		if (Application::IsKeyPressed('A'))
		{
			position = position - right * MOVE_SPEED * static_cast<float>(dt);
		}
		if (Application::IsKeyPressed('S'))
		{
			position.x = position.x - view.x * MOVE_SPEED * static_cast<float>(dt);
			position.z = position.z - view.z * MOVE_SPEED * static_cast<float>(dt);
		}
		if (Application::IsKeyPressed('D'))
		{
			position = position + right * MOVE_SPEED * static_cast<float>(dt);
		}
	}

	if (!noclip)
	{
		//outer-bounds check		 
		//checking if the absolute value, then setting it to the bounds size multiplied by positive or negative sign
		if (Math::FAbs(this->position.x) > BOUNDS_SIZE)
		{
			position.x = (Math::FAbs(this->position.x) / this->position.x) * BOUNDS_SIZE;
		}
		if (Math::FAbs(this->position.z) > BOUNDS_SIZE)
		{
			position.z = (Math::FAbs(this->position.z) / this->position.z) * BOUNDS_SIZE;
		}
		if (this->position.y > BOUNDS_SIZE)
		{
			position.y = BOUNDS_SIZE; //dont nedd bother checking downwards, since there will be ground collision
		}
	}

	//update values
	target = position + view;
}

void Camera2::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
	this->Init(position, target, up);
}

void Camera2::ToggleMovement()
{
	disableMovement = !disableMovement;
}

void Camera2::ToggleMovement(bool b)
{
	disableMovement = !b;
}

void Camera2::ToggleCamMovement()
{
	disableCamMovement = !disableCamMovement;
}

void Camera2::ToggleNoClip()
{
	noclip = !noclip;
}

bool Camera2::isLookingAt(Vector3 targetPoint)
{
	Vector3 v = targetPoint - this->position;
	float angle = Math::RadianToDegree(acosf(v.Normalize().Dot(this->view) / this->view.Length()));
	
	return angle < (FOV * 0.5f);
}

Camera2::~Camera2()
{
}