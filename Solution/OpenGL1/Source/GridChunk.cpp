#include "GridChunk.h"

int GridChunk::chunkCount = 0;

GridChunk::GridChunk()
{
}

GridChunk::GridChunk(int x, int z, int length)
{
	this->upleft = Vector3(x, 0, z);
	CHUNK_LENGTH = length;
	this->center = upleft + Vector3(length * 0.5f, 0, length * 0.5f);
	std::cout << "Center " << chunkCount << ": " << center.x << " " << center.y << " " << center.z << std::endl;
	chunkCount++;
}

void GridChunk::PushToAdjacents(GridChunk* g)
{
	bool exists = false;
	if (g == this)
		exists = true;
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

std::vector<GridCell*> GridChunk::GetCells()
{
	return chunkCells;
}

std::vector<GridChunk*> GridChunk::GetAdjacents()
{
	return adjacents;
}

GridChunk::~GridChunk()
{
}


int GridChunk::GetChunkCount()
{
	return chunkCount;
}

Vector3 GridChunk::GetCenter()
{
	return this->center;
}
