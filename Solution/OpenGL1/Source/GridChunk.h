#ifndef GRID_CHUNK_H
#define GRID_CHUNK_H

#include "GridCell.h"

class GridChunk
{
public:
	Vector3 GetCenter();
	static int GetChunkCount();

	GridChunk();
	GridChunk(int x, int z, int length);
	void PushToAdjacents(GridChunk*);
	void PushToChunkCells(GridCell*);
	std::vector<GridCell*> GetCells();
	std::vector<GridChunk*> GetAdjacents();
	~GridChunk();
private:
	static int chunkCount;
	int CHUNK_LENGTH;
	Vector3 upleft, center;
	std::vector<GridCell*> chunkCells;
	std::vector<GridChunk*> adjacents;
};

#endif

