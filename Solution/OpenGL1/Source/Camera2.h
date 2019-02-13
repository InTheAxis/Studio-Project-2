#ifndef CAMERA_2_H
#define CAMERA_2_H

#include "Vector3.h"
#include "Mtx44.h"
#include "Application.h"
#include "Utility.h"
#include "Camera.h"

class Camera2 : public Camera
{
public:
	Camera2();
	~Camera2();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void ReInit(const Vector3& pos, const Vector3& target, const Vector3& up); //init but dont set defaults
	virtual void Update(double dt, Vector3 angles, bool captureMouse);
	virtual void Reset();

	void ToggleMovement();
	void ToggleMovement(bool);
	void ToggleCamMovement();
	void ToggleNoClip();
	bool isLookingAt(Vector3 targetPoint);

	bool noclip;
private:
	bool disableMovement, disableCamMovement;
	
	Mtx44 rotationMatrixP, rotationMatrixY;

	float yaw, pitch;
	
	const int BOUNDS_SIZE = 150;
	const float MOVE_SPEED = 30;
	const float CAM_SPEED = 8;
	const float CAM_DEADZONE = 1.f;
	const float CROUCH_HEIGHT = 20;
	const float STAND_HEIGHT = 25;
	const float FOV = 50;
};

#endif