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

	GridCell* GetNext();
	void SetNext(GridCell*);
	GridCell* GetPrev();
	void SetPrev(GridCell*);
	void PushToAdjacents(GridCell*);
	void PushVertToCell(Vertex*);
	Vector3 GetUpleft();
	~GridCell();

private:
	//link
	GridCell* next, *prev; //link to next cell
	std::vector<GridCell*> adjacents; //adjacent 8 cells, total 9
	//data
	std::vector<Vertex*> cell; //the part of the vbo i want to search
	Vector3 upleft;

	const float VERT_RANGE = 0.25f; //square of the radius i want
};

#endif //! PAINTABLE_CEL_H