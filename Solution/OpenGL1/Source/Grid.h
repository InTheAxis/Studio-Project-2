#ifndef GRID_H
#define GRID_H

//a class to store a linked list of grid cells
#include "GridCell.h"

class Grid
{
public:
	Grid();
	void GenerateGrid(std::vector<Vertex>* vboPtr);
	GridCell* FindCell(int x, int z); //traverse list to find cell
	~Grid();
private:
	std::vector<GridCell*> grid;
	
	void AssignCells(std::vector<Vertex>* vboPtr);
	int CalcIndex(int x, int z);

	const int GRID_LENGTH_HALF = 5;
	const int GRID_UNIT = 1;
	const int GRID_MAX_CELLS = (GRID_LENGTH_HALF * 2 + 1) * (GRID_LENGTH_HALF * 2 + 1);
};

#endif //! GRID_H