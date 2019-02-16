#include "Paintable.h"



Paintable::Paintable()
{
	vboPtr = nullptr;
	cellToColor = nullptr;
}

std::vector<Vertex>* Paintable::GetVBO()
{
	if (vboPtr == nullptr)
		vboPtr = this->objectMesh->GetVBData();
	return this->vboPtr;
}

void Paintable::ChangeColor(Grid* currentGrid, Vector3 centerVert, Color color)
{
	//todo
	GridCell* targetCell = currentGrid->FindCell((int)centerVert.x, (int)centerVert.z);
	if (targetCell != nullptr)
	{
		targetCell->ChangeColorCell(centerVert, color);
		std::vector<GridCell*> adjCells = targetCell->GetAdjacents();
		for (GridCell* &gc : adjCells)
		{
			gc->ChangeColorCell(centerVert, color);
		}
	}

	this->objectMesh->SetVBData(vboPtr);
	MeshBuilder::ReloadVBO(this->objectMesh);
}

Paintable::~Paintable()
{
}
