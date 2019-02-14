#ifndef GRID_CEL_H
#define GRID_CEL_H

#include <vector>
#include "Vertex.h"

class GridCell
{
public:
	GridCell();
	GridCell(float upleftX, float upleftZ);
	void ChangeColorCell(Vector3 centerVert, Color color);
	void PushToCell(Vertex* v, int x, int z);
	bool CompareXZ(int x, int z);

	GridCell* GetNext();
	void SetNext(GridCell*);
	void PushToAdjacents(GridCell*);
	void PushVertToCell(Vertex*);
	Vector3 GetUpleft();
	~GridCell();

private:
	//link
	GridCell* next; //link to next cell for creation
	std::vector<GridCell*> adjacents; //adjacent 8 cells, total 9
	//data
	std::vector<Vertex*> cell; //the part of the vbo i want to search
	Vector3 verts[4]; //the bounding vertices, upleft, upright, downleft, downright
	int x, z; //to see in which quadrant: -x, +x, -z, +z

	const float VERT_RANGE = 0.5f * 0.5f; //square of the radius i want
	const float CELL_LENGTH = 1; 
};

#endif //! PAINTABLE_CEL_H