#include "Paintable.h"



Paintable::Paintable()
{
}

std::vector<Vertex>** Paintable::GetVBO()
{
	return &(this->vbo);
}

void Paintable::GenerateGrid()
{
	vbo = this->objectMesh->GetVBData();
	for (Vertex &v : *vbo)
	{
		if (v.pos.x >= 0 && v.pos.z >= 0) //+x, +z
			grid[0].PushToCell(&v, 1, 1);
		else if (v.pos.x < 0 && v.pos.z < 0) //-x, -z
			grid[1].PushToCell(&v, -1, -1);
		else if (v.pos.x < 0 && v.pos.z >= 0) //-x, +z
			grid[2].PushToCell(&v, -1, 1);
		else if (v.pos.x >= 0 && v.pos.z < 0) //+x, -z
			grid[3].PushToCell(&v, 1, -1);
	}
}

void Paintable::ChangeColor(Vector3 centerVert, Color color)
{
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		if (grid[i].CompareXZ(int(centerVert.x), int(centerVert.z)))
		{
			grid[i].ChangeColorCell(centerVert, color);
		}
	}	

	this->objectMesh->SetVBData(vbo);
	MeshBuilder::ReloadVBO(this->objectMesh);
}

Paintable::~Paintable()
{
}
