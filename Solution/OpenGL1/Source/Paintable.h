#ifndef PAINTABLE_H
#define PAINTABLE_H

#include "GameObject.h"
#include "GridCell.h"

/*NOTE, ONLY USE SINGLE SURFACE AND HIGH POLY MESHES FOR THIS CLASS*/


class Paintable : public GameObject
{
public:
	Paintable();

	std::vector<Vertex>** GetVBO();
	void GenerateGrid();
	void ChangeColor(Vector3 centerVert, Color color);

	~Paintable();
private:
	const static int GRID_SIZE = 4;

	std::vector<Vertex>* vbo;
	GridCell grid[GRID_SIZE];
};

#endif // !PAINTABLE_H
