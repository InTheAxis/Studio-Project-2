#ifndef PAINTABLE_H
#define PAINTABLE_H

#include "GameObject.h"

/*NOTE, ONLY USE SINGLE SURFACE AND HIGH POLY MESHES FOR THIS CLASS*/


class Paintable : public GameObject
{
public:
	Paintable();

	void ChangeColor(Vector3 centerVert);

	~Paintable();
private:

	const float VERT_RANGE = 1;
};

#endif // !PAINTABLE_H
