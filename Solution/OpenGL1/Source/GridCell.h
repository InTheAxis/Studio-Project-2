#ifndef GRID_CEL_H
#define GRID_CEL_H

#include <vector>
#include "Vertex.h"

class GridCell
{
public:
	GridCell(float upleftX, float upleftZ);
	
	void ChangeColorCell(Vector3 centerVert, Color color);
	
	//getter setters
	std::vector<GridCell*> GetAdjacents();
	void PushToAdjacents(GridCell*);
	void PushVertToCell(Vertex*);
	Vector3 GetUpleft();
	~GridCell();

private:
	std::vector<GridCell*> adjacents; //adjacent 8 cells
	std::vector<Vertex*> cell; //the part of the vbo i want to search
	Vector3 upleft;

	const float VERT_RANGE = 0.6f * 0.6f; //square of the radius i want
};

#endif //! PAINTABLE_CEL_H