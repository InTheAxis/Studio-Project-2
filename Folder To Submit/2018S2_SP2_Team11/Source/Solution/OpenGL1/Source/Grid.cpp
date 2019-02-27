#include "Grid.h"



Grid::Grid()
{
}

void Grid::GenerateGrid(std::vector<Vertex>* vboPtr)
{
	/*CELL GENERATION*/
	//init all cells
	GridCell* tempCell = nullptr;
	for (int z = -GRID_LENGTH_HALF; z <= GRID_LENGTH_HALF; z += CELL_UNIT)
	{
		for (int x = -GRID_LENGTH_HALF; x <= GRID_LENGTH_HALF; x += CELL_UNIT)
		{
			tempCell = new GridCell((float)x, (float)z);
			this->allCells.emplace_back(tempCell);
		}
	}

	//set adjacents
	int indexes[9] = { 0 };
	for (int z = -GRID_LENGTH_HALF; z <= GRID_LENGTH_HALF; z += CELL_UNIT)
	{
		for (int x = -GRID_LENGTH_HALF; x <= GRID_LENGTH_HALF; x += CELL_UNIT)
		{
			indexes[0] = CalcIndexForCells(x, z);
			if (x > -GRID_LENGTH_HALF)
				indexes[1] = CalcIndexForCells(x - 1, z);
			if (x > -GRID_LENGTH_HALF && z > -GRID_LENGTH_HALF)
				indexes[2] = CalcIndexForCells(x - 1, z - 1);
			if (z > -GRID_LENGTH_HALF)
				indexes[3] = CalcIndexForCells(x, z - 1);
			
			if (x < GRID_LENGTH_HALF)
				indexes[4] = CalcIndexForCells(x + 1, z);
			if (x < GRID_LENGTH_HALF && z < GRID_LENGTH_HALF)
				indexes[5] = CalcIndexForCells(x + 1, z + 1);
			if (z < GRID_LENGTH_HALF)
				indexes[6] = CalcIndexForCells(x, z + 1);
			
			if (x > -GRID_LENGTH_HALF && z < GRID_LENGTH_HALF)
				indexes[7] = CalcIndexForCells(x - 1, z + 1);
			if (x < GRID_LENGTH_HALF && z > -GRID_LENGTH_HALF)
				indexes[8] = CalcIndexForCells(x + 1, z - 1);

			for (int i = 1; i < 9; ++i)
				allCells[indexes[0]]->PushToAdjacents(allCells[indexes[i]]);
		}
	}

	//assign verts to cells
	AssignVertsCells(vboPtr);

	/*CHUNK ASSIGNMENT*/
	//init chunks
	GridChunk* tempChunk = nullptr;
	for (int z = -GRID_LENGTH_HALF; z <= GRID_LENGTH_HALF; z += CHUNK_LENGTH)
	{
		for (int x = -GRID_LENGTH_HALF; x <= GRID_LENGTH_HALF; x += CHUNK_LENGTH)
		{
			tempChunk = new GridChunk(x, z, CHUNK_LENGTH);
			allChunks.emplace_back(tempChunk);
		}
	}

	//set adjacents
	int indexes2[9] = { 0 };
	for (int z = -GRID_LENGTH_HALF; z <= GRID_LENGTH_HALF; z += CHUNK_LENGTH)
	{
		for (int x = -GRID_LENGTH_HALF; x <= GRID_LENGTH_HALF; x += CHUNK_LENGTH)
		{
			indexes2[0] = CalcIndexForChunks(x, z);
			if (x - CHUNK_LENGTH > -GRID_LENGTH_HALF)
				indexes2[1] = CalcIndexForChunks(x - CHUNK_LENGTH, z);
			if (x - CHUNK_LENGTH > -GRID_LENGTH_HALF && z - CHUNK_LENGTH > -GRID_LENGTH_HALF)
				indexes2[2] = CalcIndexForChunks(x - CHUNK_LENGTH, z - CHUNK_LENGTH);
			if (z - CHUNK_LENGTH > -GRID_LENGTH_HALF)
				indexes2[3] = CalcIndexForChunks(x, z - CHUNK_LENGTH);

			if (x + CHUNK_LENGTH < GRID_LENGTH_HALF)
				indexes2[4] = CalcIndexForChunks(x + CHUNK_LENGTH, z);
			if (x + CHUNK_LENGTH < GRID_LENGTH_HALF && z + CHUNK_LENGTH < GRID_LENGTH_HALF)
				indexes2[5] = CalcIndexForChunks(x + CHUNK_LENGTH, z + CHUNK_LENGTH);
			if (z + CHUNK_LENGTH < GRID_LENGTH_HALF)
				indexes2[6] = CalcIndexForChunks(x, z + CHUNK_LENGTH);

			if (x - CHUNK_LENGTH > -GRID_LENGTH_HALF && z + CHUNK_LENGTH < GRID_LENGTH_HALF)
				indexes2[7] = CalcIndexForChunks(x - CHUNK_LENGTH, z + CHUNK_LENGTH);
			if (x + CHUNK_LENGTH < GRID_LENGTH_HALF && z - CHUNK_LENGTH> -GRID_LENGTH_HALF)
				indexes2[8] = CalcIndexForChunks(x + CHUNK_LENGTH, z - CHUNK_LENGTH);

			for (int i = 1; i < 9; ++i)
				allChunks[indexes2[0]]->PushToAdjacents(allChunks[indexes2[i]]);
		}
	}

	//assign cells to chunks
	AssignCellsChunks();
}

GridCell* Grid::FindCell(int x, int z)
{
	if (abs(x) > GRID_LENGTH_HALF || abs(z) > GRID_LENGTH_HALF)
		return nullptr;

	return allCells[CalcIndexForCells(x, z)];
}

GridChunk * Grid::FindChunk(int x, int z)
{
	return allChunks[CalcIndexForChunks(x, z)];
}

void Grid::AssignVertsCells(std::vector<Vertex>* vboPtr)
{
	bool error = false;
	for (Vertex &v : *vboPtr)
	{
		if (Math::FAbs(v.pos.x) > GRID_LENGTH_HALF || Math::FAbs(v.pos.z) > GRID_LENGTH_HALF)
			error = true;
		else
			FindCell((int)v.pos.x, (int)v.pos.z)->PushVertToCell(&v);
	}
	if (error)
		std::cout << " WARNING: Grid length too small, vertices outside cells\n";
}

int Grid::CalcIndexForCells(int x, int z)
{
	return ((z + GRID_LENGTH_HALF) * (GRID_LENGTH_HALF * 2 + 1)) + (x + GRID_LENGTH_HALF);
}

void Grid::AssignCellsChunks()
{
	for (GridCell* &gc : allCells)
	{	
		Vector3 upleftChunk = gc->GetUpleft();
		FindChunk((int)upleftChunk.x, (int)upleftChunk.z)->PushToChunkCells(gc);
	}
}

int Grid::CalcIndexForChunks(int x, int z)
{
	int ret = ((z + GRID_LENGTH_HALF) / 3 * ((GRID_LENGTH_HALF * 2 + 1) / CHUNK_LENGTH)) + ((x + GRID_LENGTH_HALF) / 3);
	return ret;
	
}

Grid::~Grid()
{
}

int Grid::GetGridLengthHalf()
{
	return GRID_LENGTH_HALF;
}



std::vector<GridChunk*> Grid::GetAllChunks()
{
	return allChunks;
}