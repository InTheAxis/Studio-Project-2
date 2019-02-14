#include "GridCell.h"



GridCell::GridCell()
{
}

GridCell::GridCell(float upleftX, float upleftZ)
{
	this->verts[0] = Vector3(upleftX, 0, upleftZ); //e.g. 0, 0
	this->verts[1] = Vector3(upleftX + 1, 0, upleftZ);; //e.g. 1, 0
	this->verts[2] = Vector3(upleftX + 1, 0, upleftZ + 1); //e.g. 1, 1
	this->verts[3] = Vector3(upleftX, 0, upleftZ + 1); //e.g. 0 ,1
	this->next = nullptr;
}

void GridCell::PushToCell(Vertex* v, int x, int z)
{
	this->cell.push_back(v);
	this->x = x; this->z = z;
}

void GridCell::ChangeColorCell(Vector3 centerVert, Color color)
{
	for (Vertex* v : this->cell)
	{
		Vector3 temp = Vector3(v->pos.x, v->pos.y, v->pos.z) - centerVert;
		temp.y = 0; //temporary, so i dont have to go so close to ground to test, remove!
		if (Math::Square(temp.x) + Math::Square(temp.y) + Math::Square(temp.z) < VERT_RANGE) // i dont want to square root
		{
			std::cout << "Repainting: " << v->pos.x << ", " << v->pos.z << "\n";
			v->color = color;
		}
	}
}

bool GridCell::CompareXZ(int x, int z)
{
	return (this->x * Math::Clamp(x, -1, 1) >= 0 && this->z * Math::Clamp(z, -1, 1) >= 0); //- * - = +, + * + = +, ensures its same sign
}

void GridCell::SetNext(GridCell* cell)
{
	this->next = cell;
}

GridCell* GridCell::GetNext()
{
	return next;
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
	return verts[0];
}

GridCell::~GridCell()
{
}
