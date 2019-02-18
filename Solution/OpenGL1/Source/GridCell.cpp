#include "GridCell.h"

GridCell::GridCell(float upleftX, float upleftZ)
{
	this->upleft = Vector3(upleftX, 0, upleftZ);
}

void GridCell::ChangeColorCell(Vector3 centerVert, Color color)
{
	for (Vertex* &v : this->cell)
	{
		if (v->color.r == color.r && v->color.g == color.g && v->color.b == color.b) 
			continue;
		//else 
		Vector3 temp = Vector3(v->pos.x, 0, v->pos.z) - centerVert;
		temp.y = 0; //temporary, so i dont have to go so close to ground to test, remove!
		float dist = Math::Square(temp.x) + Math::Square(temp.y) + Math::Square(temp.z);
		if (dist <= VERT_RANGE) // i dont want to square root
		{
			std::cout << "Repainting: " << v->pos.x << ", " << v->pos.z << "\n";
			v->color = color;
		}
	}
}

std::vector<GridCell*> GridCell::GetAdjacents()
{
	return this->adjacents;
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
