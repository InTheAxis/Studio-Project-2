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
		Vector3 temp = Vector3(v->pos.x, v->pos.y, v->pos.z) - centerVert;
		if (temp.Length() < VERT_RANGE)
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
