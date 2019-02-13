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
	void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	void ReInit(const Vector3& pos, const Vector3& target, const Vector3& up); //init but dont set defaults
	
	virtual void Update(double dt, Vector3 translate, Vector3 rotate) = 0;
	virtual void Reset() = 0;

	virtual void InitDerived() = 0;
protected:
	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;

	Vector3 prevCursorPos;
};

#endif
