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
			tempCell = new GridCell(x, z);
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
}

GridCell* Grid::FindCell(int x, int z)
{
	if (Math::FAbs(x) > GRID_LENGTH_HALF || Math::FAbs(z) > GRID_LENGTH_HALF)
		return nullptr;

	return allCells[CalcIndexForCells(x, z)];
}

GridChunk * Grid::FindChunk(int x, int z)
{
	return nullptr;
}

void Grid::AssignVertsCells(std::vector<Vertex>* vboPtr)
{
	bool error;
	for (Vertex &v : *vboPtr)
	{
		if (Math::FAbs(v.pos.x) > GRID_LENGTH_HALF || Math::FAbs(v.pos.z) > GRID_LENGTH_HALF)
			error = true;
		else
			FindCell((int)v.pos.x, (int)v.pos.z)->PushVertToCell(&v);
	}
	if (error)
		std::cout << " ERROR: Grid length too small, vertices outside cells\n";
}

int Grid::CalcIndexForCells(int x, int z)
{
	return ((z + GRID_LENGTH_HALF) * (GRID_LENGTH_HALF * 2 + 1)) + (x + GRID_LENGTH_HALF);
}

void Grid::AssignCellsChunks()
{
	for (GridCell* &gc : allCells)
	{

	}
}

int Grid::CalcIndexForChunks(int x, int z)
{
	return 0;
}

Grid::~Grid()
{
}
