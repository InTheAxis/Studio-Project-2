#include "Paintable.h"



Paintable::Paintable()
{
}

void Paintable::ChangeColor()
{
	this->objectMesh->GetVBData()->at(0).color.Set(1, 0, 0);
	MeshBuilder::ReloadVBO(this->objectMesh);
}

Paintable::~Paintable()
{
}
