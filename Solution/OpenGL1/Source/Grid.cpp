#include "Grid.h"



Grid::Grid()
{
	this->head = tail = nullptr;
	this->current = forTraversing= nullptr;
}

void Grid::CreateLinkedList(std::vector<Vertex>** vbo)
{
	start = new GridCell(STARTX, STARTZ);
	head = new GridCell(-GRID_LENGTH_HALF, -GRID_LENGTH_HALF);
	tail = forTraversing = current = head;
	for (int z = -GRID_LENGTH_HALF; z <= GRID_LENGTH_HALF; z += GRID_UNIT)
	{
		for (int x = -GRID_LENGTH_HALF; x <= GRID_LENGTH_HALF; x += GRID_UNIT)
		{
 			if (x == -GRID_LENGTH_HALF && z == -GRID_LENGTH_HALF) 
				continue;
			if (x == STARTX && z == STARTZ)
				current = start;
			else
				current = new GridCell(x, z);

			tail->SetNext(current);
			tail = current;
		}
	}
	current = start;

	AssignCell(vbo);
}

void Grid::AssignCell(std::vector<Vertex>** vbo)
{
	std::vector<Vertex*> cellTemp;
	Vector3 upleftTrunc;
	int traverseAmount = 0;

	for (Vertex &v : **vbo)
	{
		forTraversing = head;
		
		upleftTrunc = Vector3((int)(v.pos.x), 0, (int)(v.pos.z)); //gets the nearest vertex, doesnt work if GRID_UNIT != 1

		traverseAmount = ((upleftTrunc.z + GRID_LENGTH_HALF) * (GRID_LENGTH_HALF * 2 + 1)) + (upleftTrunc.x + GRID_LENGTH_HALF);
		
		std::cout << traverseAmount;

		traverseAmount = Math::Clamp(traverseAmount, 0, GRID_MAX_CELLS - 1);

		std::cout << ":" << traverseAmount << "   ";

		for (int i = 0; i < traverseAmount; ++i)
		{
			forTraversing = forTraversing->GetNext();
		}

		forTraversing->PushVertToCell(&v);
	}
}

Grid::~Grid()
{
}
