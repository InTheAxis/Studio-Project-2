#ifndef PAINTABLE_H
#define PAINTABLE_H

#include "GameObject.h"
#include "Grid.h"

/*NOTE, ONLY USE SINGLE SURFACE AND HIGH POLY MESHES FOR THIS CLASS*/


class Paintable : public GameObject
{
public:
	Paintable();

	std::vector<Vertex>** GetVBO();
	void ChangeColor(Grid* currentGrid, Vector3 centerVert, Color color);

	~Paintable();
private:
	std::vector<Vertex>* vbo;
	Grid* currentGrid;

	const float VERT_RANGE = 0.5f * 0.5f; //square of the radius i want
};

#endif // !PAINTABLE_H
