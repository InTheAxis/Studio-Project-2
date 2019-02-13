#ifndef FREE_CAM_H
#define FREE_CAM_H

#include "Vector3.h"
#include "Mtx44.h"
#include "Application.h"
#include "Utility.h"
#include "Camera.h"

class FreeCam : public Camera
{
public:
	FreeCam();
	~FreeCam();
	virtual void Update(double dt, Vector3 translate, Vector3 rotate);
	virtual void Reset();

	void ToggleMovement();
	void ToggleMovement(bool);
	void ToggleCamMovement();
	void ToggleInvert(bool x, bool y);
	void ToggleNoClip();
	bool GetNoClip();
	bool isLookingAt(Vector3 targetPoint);

private:
	virtual void InitDerived();
	
	bool disableMovement, disableCamMovement;
	
	Mtx44 rotationMatrixP, rotationMatrixY;

	float yaw, pitch;
	bool noclip, invertX, invertY;

	const float MOVE_SPEED = 30;
	const float CAM_SPEED = 1.5f;
	const float CAM_DEADZONE = 1.f;
	const float FOV = 50;
};

#endif