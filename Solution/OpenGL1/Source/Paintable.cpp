#include "Paintable.h"



Paintable::Paintable()
{
	vboPtr = nullptr;
}

std::vector<Vertex>* Paintable::GetVBO()
{
	if (vboPtr == nullptr)
		vboPtr = this->objectMesh->GetVBData();
	return this->vboPtr;
}

void Paintable::ChangeColor(Grid* currentGrid, Vector3 centerVert, Color color, float range)
{
	GridCell* targetCell = currentGrid->FindCell((int)centerVert.x, (int)centerVert.z);
	if (targetCell != nullptr)
	{
		targetCell->ChangeColorCell(centerVert, color, range);
		std::vector<GridCell*> adjCells = targetCell->GetAdjacents();
		for (GridCell* &gc : adjCells)
		{
			gc->ChangeColorCell(centerVert, color, range);
		}
	}

	this->objectMesh->SetVBData(vboPtr);
	MeshBuilder::ReloadVBO(this->objectMesh);
}

void Paintable::CalculateCoverage(std::vector<Color> vertColors, Paint* team1, Paint* team2)
{
	int numOfColor[2] = { 0,0 };
	int totalNum = 0;
	for (Color &c : vertColors)
	{
		//clear color 0,0,0 by default
		if (c.r == 0 && c.g == 0 && c.b == 0)
		{
			//ignore
		}
		//paint team 1
		else if (c.r == team1->GetPaintColor().r &&
			c.g == team1->GetPaintColor().g &&
			c.b == team1->GetPaintColor().b)
		{
			numOfColor[0]++;
		}
		//paint team 2
		else if (c.r == team2->GetPaintColor().r &&
			c.g == team2->GetPaintColor().g &&
			c.b == team2->GetPaintColor().b)
		{
			numOfColor[1]++;
		}
		else
		{
			totalNum++;
		}
	}

	totalNum = totalNum + numOfColor[0] + numOfColor[1];

	team1->SetPercentage((float)numOfColor[0] / (float)totalNum * 100.0f);
	team2->SetPercentage((float)numOfColor[1] / (float)totalNum * 100.0f);
}

Paintable::~Paintable()
{
}
