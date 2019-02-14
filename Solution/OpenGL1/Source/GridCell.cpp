#include "GridCell.h"



GridCell::GridCell()
{
}

GridCell::GridCell(float upleftX, float upleftZ)
{
	this->upleft = Vector3(upleftX, 0, upleftZ);
	this->next = prev = nullptr;
}

void GridCell::ChangeColorCell(Vector3 centerVert, Color color)
{
	for (Vertex* v : this->cell)
	{
		Vector3 temp = Vector3(v->pos.x, 0, v->pos.z) - centerVert;
		temp.y = 0; //temporary, so i dont have to go so close to ground to test, remove!
		if (Math::Square(temp.x) + Math::Square(temp.z) < VERT_RANGE) // i dont want to square root
		{
			std::cout << "Repainting: " << v->pos.x << ", " << v->pos.z << "\n";
			v->color = color;
		}
	}
}

void GridCell::SetNext(GridCell* cell)
{
	this->next = cell;
}

GridCell* GridCell::GetNext()
{
	return next;
}

void GridCell::SetPrev(GridCell* cell)
{
	this->prev = cell;
}

GridCell* GridCell::GetPrev()
{
	return prev;
}

void GridCell::PushToAdjacents(GridCell* cell)
{
	bool exists = false;
	for (GridCell* g : adjacents)
	{
		if (g == cell)
		{
			exists = true;
			break;
		}
	}
	if (!exists)
		this->adjacents.push_back(cell);
}

void GridCell::PushVertToCell(Vertex* v)
{
	this->cell.push_back(v);
}

Vector3 GridCell::GetUpleft()
{
	return upleft;
}

GridCell::~GridCell()
{
}
