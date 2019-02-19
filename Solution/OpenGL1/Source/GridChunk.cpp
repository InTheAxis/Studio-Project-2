#include "GridChunk.h"

GridChunk::GridChunk(int x, int z, int length)
{
	this->upleft = Vector3(x, 0, z);
	CHUNK_LENGTH = length;
	this->center = upleft + Vector3(length * 0.5f, 0, length * 0.5f);
}

void GridChunk::PushToAdjacents(GridChunk* g)
{
	bool exists = false;
	for (GridChunk* gc : adjacents)
	{
		if (gc == g)
		{
			exists = true;
			break;
		}
	}
	if (!exists)
		this->adjacents.emplace_back(g);
}

void GridChunk::PushToChunkCells(GridCell* gc)
{
	this->chunkCells.emplace_back(gc);
}

GridChunk::~GridChunk()
{
}
