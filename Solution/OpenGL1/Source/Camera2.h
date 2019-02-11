#ifndef CAMERA_2_H
#define CAMERA_2_H

#include "Vector3.h"
#include "Mtx44.h"
#include "Application.h"
#include "Utility.h"

class Camera2
{
public:
	Vector3 position;
	Vector3 target;
	Vector3 up;
	Vector3 view;
	Vector3 right;

	Camera2();
	~Camera2();
	void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	void ReInit(const Vector3& pos, const Vector3& target, const Vector3& up); //init but dont set defaults
	void Update(double dt, Vector3 angles, bool captureMouse);
	void Reset();

	void ToggleMovement();
	void ToggleMovement(bool);
	void ToggleCamMovement();
	void ToggleNoClip();
	bool isLookingAt(Vector3 targetPoint);

	bool noclip;
private:
	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;
	
	bool disableMovement, disableCamMovement;
	
	Mtx44 rotationMatrixP, rotationMatrixY;

	float yaw, pitch;
	
	const int BOUNDS_SIZE = 150;
	const float MOVE_SPEED = 50;
	const float CAM_SPEED = 8;
	const float CAM_DEADZONE = 1.f;
	const float CROUCH_HEIGHT = 20;
	const float STAND_HEIGHT = 25;
	const float FOV = 50;
};

#endif