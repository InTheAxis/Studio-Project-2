#include "Paintable.h"



Paintable::Paintable()
{
	vbo = nullptr;
}

std::vector<Vertex>** Paintable::GetVBO()
{
	if (vbo == nullptr)
		vbo = this->objectMesh->GetVBData();
	return &(this->vbo);
}

void Paintable::ChangeColor(Grid* currentGrid, Vector3 centerVert, Color color)
{
	(*currentGrid->FindCell((int)centerVert.x, (int)centerVert.z))->ChangeColorCell(centerVert, color);

	this->objectMesh->SetVBData(vbo);
	MeshBuilder::ReloadVBO(this->objectMesh);
}

Paintable::~Paintable()
{
}
