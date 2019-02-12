#ifndef CAMERA_1_H
#define CAMERA_1_H

#include "Vector3.h"
#include "Mtx44.h"
#include "Application.h"
#include "Utility.h"
#include "Camera.h"

class Camera1 : public Camera
{
public:

	Camera1();
	~Camera1();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void ReInit(const Vector3& pos, const Vector3& target, const Vector3& up); //init but dont set defaults
	virtual void Update(double dt, Vector3 angles, bool captureMouse);
	virtual void Reset();
	virtual void ToggleNoClip();

private:
	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;

	Vector3 offset = Vector3(0, 10, -10);

	Mtx44 rotationMatrixP;

	const float CAM_SPEED = 50;
};

#endif
