#include "Paintable.h"



Paintable::Paintable()
{
}

void Paintable::ChangeColor(Vector3 centerVert)
{
	std::vector<Vertex>* vbo = this->objectMesh->GetVBData();
	
	for (int i = 0; i < vbo->size(); ++i)
	{
		Vertex* v = &(vbo->at(i));
		if (Math::FAbs(v->pos.x - centerVert.x) < VERT_RANGE && Math::FAbs(v->pos.z - centerVert.z) < VERT_RANGE) //y doesnt matter, since this mesh shld only be top surface
		{
			std::cout << v->pos.x << ", " << v->pos.y << "\n";
			v->color.Set(1, 0, 0);
		}
	}

	this->objectMesh->SetVBData(vbo);
	MeshBuilder::ReloadVBO(this->objectMesh);
}

Paintable::~Paintable()
{
}
