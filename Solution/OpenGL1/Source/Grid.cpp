#include "Grid.h"



Grid::Grid()
{
	this->traversalIndex = 0;
	this->head = tail = nullptr;
	this->current = forTraversing= nullptr;
}

void Grid::CreateLinkedList(std::vector<Vertex>** vbo)
{
	head = new GridCell(-GRID_LENGTH_HALF, -GRID_LENGTH_HALF);
	tail = forTraversing = current = head;
	for (int z = -GRID_LENGTH_HALF; z <= GRID_LENGTH_HALF; z += GRID_UNIT)
	{
		for (int x = -GRID_LENGTH_HALF; x <= GRID_LENGTH_HALF; x += GRID_UNIT)
		{
 			if (x == -GRID_LENGTH_HALF && z == -GRID_LENGTH_HALF) 
				continue;
			else
				current = new GridCell(x, z);

			tail->SetNext(current);
			current->SetPrev(tail);

			tail->PushToAdjacents(current);
			current->PushToAdjacents(tail);

			tail = current;
		}
	}
	current = head;

	AssignCell(vbo);
}

GridCell** Grid::FindCell(int x, int z)
{
	int traverseAmount = 0;
	traverseAmount = ((z + GRID_LENGTH_HALF) * (GRID_LENGTH_HALF * 2 + 1)) + (x + GRID_LENGTH_HALF);
	traverseAmount = Math::Clamp(traverseAmount, 0, GRID_MAX_CELLS - 1);
	std::cout << "Cell:" << traverseAmount << "   ";
	
	if (traversalIndex > traverseAmount)
	{
		//traverse forward
		for (int i = 0; i < traversalIndex - traverseAmount; ++i)
		{
			current = current->GetPrev();
		}
	}
	else if (traversalIndex < traverseAmount)
	{
		//traverse forward
		for (int i = 0; i < traverseAmount - traversalIndex; ++i)
		{
			current = current->GetNext();
		}
	}

	traversalIndex = traverseAmount;
	return &current;
}

void Grid::AssignCell(std::vector<Vertex>** vbo)
{
	current = head;
	for (Vertex &v : **vbo)
	{
		(*FindCell((int)v.pos.x, (int)v.pos.z))->PushVertToCell(&v);
	}
}

Grid::~Grid()
{
}
