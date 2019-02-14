#ifndef GRID_H
#define GRID_H

//a class to store a linked list of grid cells
#include "GridCell.h"

class Grid
{
public:
	Grid();
	void CreateLinkedList(std::vector<Vertex>** vbo); //where the loop throug the vbo is
	GridCell** FindCell(int x, int z); //traverse list to find cell
	std::vector<GridCell**> FindCells(int x, int z); //traverse list to find cella
	~Grid();
private:
	GridCell* head, *tail; //first cell and last cell
	GridCell* forTraversing; //dont use for anything else
	GridCell* current; //stores current cell that is occupied

	int traversalIndex;

	void AssignCell(std::vector<Vertex>** vbo);

	const int GRID_LENGTH_HALF = 5;
	const int GRID_UNIT = 1;
	const int GRID_MAX_CELLS = (GRID_LENGTH_HALF * 2 + 1) * (GRID_LENGTH_HALF * 2 + 1);
};

#endif //! GRID_H