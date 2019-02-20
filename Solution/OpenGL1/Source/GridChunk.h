#ifndef GRID_CHUNK_H
#define GRID_CHUNK_H

#include "GridCell.h"

class GridChunk
{
public:
	GridChunk(int x, int z, int length);
	void PushToAdjacents(GridChunk*);
	void PushToChunkCells(GridCell*);
	std::vector<GridCell*> GetCells();
	std::vector<GridChunk*> GetAdjacents();
	~GridChunk();
private:
	int CHUNK_LENGTH;
	Vector3 upleft, center;
	std::vector<GridCell*> chunkCells;
	std::vector<GridChunk*> adjacents;
};

#endif

