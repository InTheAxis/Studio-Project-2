#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
#include "Mtx44.h"
#include "Application.h"
#include "Utility.h"

class Camera
{
public:
	Vector3 position;
	Vector3 target;
	Vector3 up;
	Vector3 view;
	Vector3 right;

	Camera();
	~Camera();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up) = 0;
	virtual void ReInit(const Vector3& pos, const Vector3& target, const Vector3& up) = 0; //init but dont set defaults
	virtual void Update(double dt, Vector3 angles, bool captureMouse) = 0;
	virtual void Reset() = 0;
	virtual void ToggleNoClip() = 0;

private:
	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;
};

#endif
