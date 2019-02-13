#include "FreeCam.h"

FreeCam::FreeCam()
{
}

void FreeCam::InitDerived()
{
	this->yaw = pitch = 0;
	this->disableMovement = false;
	this->disableCamMovement = false;
	this->noclip = true;
	this->invertX = invertY = false;
}

void FreeCam::Update(double dt, Vector3 translate, Vector3 rotate)
{
	if (!disableCamMovement)
	{
		Vector3 actualRotate = (prevCursorPos - rotate) * CAM_SPEED;
		if (invertX)
		{
			actualRotate.x *= -1;
		}
		if (invertY)
		{
			actualRotate.y *= -1;
		}
		//inputs
		//preventing y overflow, 0.95f (out of 1) is the max i allowed
		if ((view.y > 0.95f && actualRotate.y > 0) || (view.y < -0.95f && actualRotate.y < 0))
			actualRotate.y = 0;
		//if magnitude > deadzone, rotate by yaw, else reset yaw
		if (Math::FAbs(actualRotate.x) > CAM_DEADZONE)
			yaw = (float)(actualRotate.x * CAM_SPEED * dt);
		else
			yaw = 0;
		//if magnitude > deadzone, rotate by pitch, else reset pitch
		if (Math::FAbs(actualRotate.y) > CAM_DEADZONE)
			pitch = (float)(actualRotate.y * CAM_SPEED * dt);
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
		if (Application::IsKeyPressed(VK_SPACE))
		{
			position.y = position.y + up.y * MOVE_SPEED * static_cast<float>(dt);
		}
		if (Application::IsKeyPressed(VK_LSHIFT))
		{
			position.y = position.y - up.y * MOVE_SPEED * static_cast<float>(dt);
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

	//update values
	target = position + view;

	prevCursorPos = rotate;
}

void FreeCam::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
	this->ReInit(position, target, up);
}

void FreeCam::ToggleMovement()
{
	disableMovement = !disableMovement;
}

void FreeCam::ToggleMovement(bool b)
{
	disableMovement = !b;
}

void FreeCam::ToggleCamMovement()
{
	disableCamMovement = !disableCamMovement;
}

void FreeCam::ToggleInvert(bool x, bool y)
{
	invertX = x ? !invertX : invertX;
	invertY = y ? !invertY : invertY;
}

void FreeCam::ToggleNoClip()
{
	noclip = !noclip;
}

bool FreeCam::GetNoClip()
{
	return noclip;
}

bool FreeCam::isLookingAt(Vector3 targetPoint)
{
	Vector3 v = targetPoint - this->position;
	float angle = Math::RadianToDegree(acosf(v.Normalize().Dot(this->view) / this->view.Length()));
	
	return angle < (FOV * 0.5f);
}

FreeCam::~FreeCam()
{
}