#ifndef GRID_H
#define GRID_H

//a class to store a linked list of grid cells
#include "GridCell.h"
#include "GridChunk.h"

class Grid
{
public:
	Grid();
	int GetGridLengthHalf();
	void GenerateGrid(std::vector<Vertex>* vboPtr);
	GridCell* FindCell(int x, int z); //find cell from xz
	GridChunk* FindChunk(int x, int z); //find chunk from xz
	~Grid();

	std::vector<GridChunk*> GetAllChunks();

private:
	std::vector<GridCell*> allCells;
	std::vector<GridChunk*> allChunks;
	
	void AssignVertsCells(std::vector<Vertex>* vboPtr);
	int CalcIndexForCells(int x, int z);
	void AssignCellsChunks();
	int CalcIndexForChunks(int x, int z);

	//length refers to how many cells
	const int GRID_LENGTH_HALF = 52;
	const int CELL_UNIT = 1;
	const int GRID_MAX_CELLS = (GRID_LENGTH_HALF * 2 + 1) * (GRID_LENGTH_HALF * 2 + 1);
	const int CHUNK_LENGTH = 3;
};

#endif //! GRID_H