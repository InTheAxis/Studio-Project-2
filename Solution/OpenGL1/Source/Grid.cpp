#include "Grid.h"



Grid::Grid()
{
}

void Grid::GenerateGrid(std::vector<Vertex>* vboPtr)
{
	//init grid std::vector
	GridCell* temp = nullptr;
	for (int z = -GRID_LENGTH_HALF; z <= GRID_LENGTH_HALF; z += GRID_UNIT)
	{
		for (int x = -GRID_LENGTH_HALF; x <= GRID_LENGTH_HALF; x += GRID_UNIT)
		{
			temp = new GridCell(x, z);
			this->grid.emplace_back(temp);
		}
	}

	//set adjacents
	int indexes[9] = { 0 };
	for (int z = -GRID_LENGTH_HALF; z <= GRID_LENGTH_HALF; z += GRID_UNIT)
	{
		for (int x = -GRID_LENGTH_HALF; x <= GRID_LENGTH_HALF; x += GRID_UNIT)
		{
			indexes[0] = CalcIndex(x, z);
			if (x > -GRID_LENGTH_HALF)
				indexes[1] = CalcIndex(x - 1, z);
			if (x > -GRID_LENGTH_HALF && z > -GRID_LENGTH_HALF)
				indexes[2] = CalcIndex(x - 1, z - 1);
			if (z > -GRID_LENGTH_HALF)
				indexes[3] = CalcIndex(x, z - 1);
			
			if (x < GRID_LENGTH_HALF)
				indexes[4] = CalcIndex(x + 1, z);
			if (x < GRID_LENGTH_HALF && z < GRID_LENGTH_HALF)
				indexes[5] = CalcIndex(x + 1, z + 1);
			if (z < GRID_LENGTH_HALF)
				indexes[6] = CalcIndex(x, z + 1);
			
			if (x > -GRID_LENGTH_HALF && z < GRID_LENGTH_HALF)
				indexes[2] = CalcIndex(x - 1, z + 1);
			if (x < GRID_LENGTH_HALF && z > -GRID_LENGTH_HALF)
				indexes[2] = CalcIndex(x + 1, z - 1);

			for (int i = 1; i < 9; ++i)
				grid[indexes[0]]->PushToAdjacents(grid[indexes[i]]);
		}
	}

	//assign verts to cells
	AssignCells(vboPtr);
}

GridCell* Grid::FindCell(int x, int z)
{
	if (x < -GRID_LENGTH_HALF || z < -GRID_LENGTH_HALF || x > GRID_LENGTH_HALF || z > GRID_LENGTH_HALF)
		return nullptr;

	return grid[CalcIndex(x, z)];
}

void Grid::AssignCells(std::vector<Vertex>* vboPtr)
{
	for (Vertex &v : *vboPtr)
	{
		FindCell((int)v.pos.x, (int)v.pos.z)->PushVertToCell(&v);
	}
}

int Grid::CalcIndex(int x, int z)
{
	return ((z + GRID_LENGTH_HALF) * (GRID_LENGTH_HALF * 2 + 1)) + (x + GRID_LENGTH_HALF);
}

Grid::~Grid()
{
}
