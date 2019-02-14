#include "Paintable.h"



Paintable::Paintable()
{
	vbo = nullptr;
	cellToColor = nullptr;
}

std::vector<Vertex>** Paintable::GetVBO()
{
	if (vbo == nullptr)
		vbo = this->objectMesh->GetVBData();
	return &(this->vbo);
}

void Paintable::ChangeColor(Grid* currentGrid, Vector3 centerVert, Color color)
{
	//very laggy
	//std::vector<GridCell**> temp = (currentGrid->FindCells((int)centerVert.x, (int)centerVert.z));

	//for (GridCell** gc : temp)
	//{
	//	if (gc != nullptr)
	//		(*gc)->ChangeColorCell(centerVert, color);
	//}

	cellToColor = (currentGrid->FindCell((int)centerVert.x, (int)centerVert.z));
	if (cellToColor != nullptr)
		(*cellToColor)->ChangeColorCell(centerVert, color);

	this->objectMesh->SetVBData(vbo);
	MeshBuilder::ReloadVBO(this->objectMesh);
}

Paintable::~Paintable()
{
}
