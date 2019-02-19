#ifndef GRID_CEL_H
#define GRID_CEL_H

#include <vector>
#include "Vertex.h"

class GridCell
{
public:
	GridCell(float upleftX, float upleftZ);
	
	void ChangeColorCell(Vector3 centerVert, Color color, float range = 0.6f);
	
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
};

#endif //! PAINTABLE_CEL_H