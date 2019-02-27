#include "BuildMap.h"
#include <ctime>


BuildMap::BuildMap()
{
	ObjCount = 0;
	location = Vector3(0, 0, 0);
	prevCenter = NULL;
	distanceAI = NULL;
}

BuildMap::~BuildMap()
{

}

void BuildMap::SetOccupied(Grid *currentGrid, Vector3 pos)
{
	GridChunk* targetChunk = currentGrid->FindChunk((int)pos.x, (int)pos.z);
	occupied.push_back(targetChunk->GetCenter());
}

bool BuildMap::GenerateObj(Grid* currentGrid)
{
	std::vector<GridChunk*> temp = currentGrid->GetAllChunks(); //temp stores all chunks
	int x = Math::RandIntMinMax(0, temp.size() - 1);
	std::vector<GridChunk*> currAdj = temp[x]->GetAdjacents(); //currAdj stores all adjacent chunks
	for (Vector3 &v : occupied)
	{
		if (v == temp[x]->GetCenter())
		{
			return false;
		}
		for (unsigned int it = 0; it < currAdj.size(); it++)
		{
			if (v == currAdj[it]->GetCenter())
				return false;
		}
	}
	location = temp[x]->GetCenter();
	occupied.push_back(location);
	std::vector<GridChunk*> tempAdj = temp[x]->GetAdjacents();
	for (unsigned int it = 0; it < tempAdj.size(); it++)
	{
		occupied.push_back(tempAdj[it]->GetCenter());
	}
	location.y = 0.25f;
	++ObjCount;
	return true;
	/*switch (ObjCount)
	{
	case 0:
	{
		location = temp[0]->GetCenter();
		ObjCount++;
	}
	break;
	case 1:
	{
		location = temp[temp.size() - 1]->GetCenter();
		ObjCount++;
	}
	break;
	}
	location.y = 0.25f;
	return true;*/
}

Vector3 BuildMap::GetDestination(Grid *currentGrid, Color color, Vector3 AIpos)
{
	GridChunk* targetChunk = currentGrid->FindChunk((int)AIpos.x, (int)AIpos.z); //Find chunk the AI is on
	
	std::vector<GridChunk*> Adjacents = targetChunk->GetAdjacents(); //Get the adjacent chunks of current chunk and pass into vector Adjacents
	for (unsigned int it = 0; it < Adjacents.size(); it++) //iterate throught vector adjacents to get its' cell
	{
		if (Adjacents[it]->GetCenter() != prevCenter) //check if the adjacent chunk was the previous chunk
		{
			std::vector<GridCell*> AdjCells = Adjacents[it]->GetCells(); //Get the cells within the current chunk
			for (unsigned int it = 0; it < AdjCells.size(); it++) //iterate through the cells of the current adjacent chunk
			{
				std::vector<Vertex*> CellVert = AdjCells[it]->GetCellVertex(); //get the vertices of the current cell of the current adjacent chunk
				for (unsigned int it = 0; it < CellVert.size(); it++) //iterate through the vertices to find the Vert that is colored opposite to its own color
				{
					if (CellVert[it]->color.r == color.r && CellVert[it]->color.g == color.g && CellVert[it]->color.b == color.b) //if found
					{
						prevCenter = targetChunk->GetCenter(); //save current chunk's center
						return Vector3(CellVert[it]->pos.x, 0, CellVert[it]->pos.y); //return the vertices of the colored area
					}
				}
			}
		}
	}

	bool found = false;
	bool same = false;
	int count = 0;
	std::vector<GridChunk*> temp = currentGrid->GetAllChunks(); //temp stores all chunks
	while (!found)
	{
		int x = Math::RandIntMinMax(0, temp.size() - 1);
		for (unsigned int it = 0; it < occupied.size(); it++)
		{
			if (temp[x]->GetCenter() == prevCenter)
				same = true;
			if (temp[x]->GetCenter() == occupied[it])
				same = true;
			if (same)
				break;
		}
		if (!same)
		{
			found = true;
			prevCenter = targetChunk->GetCenter();
			return temp[x]->GetCenter();
		}
		count++;
		if (count == 10)
			prevCenter = Vector3(0, 0, 20);
			return Vector3(0, 0, 20);
	}
	
	distanceAI = NULL;
}


Vector3 BuildMap::GetLocation()
{
	return location;
}

Vector3 BuildMap::GenerateRandNum(int length)
{
	float x = Math::RandFloatMinMax(-length, length);
	std::cout << "X: " << x << std::endl;//get GRID_LENGTH_HALF
	float z = Math::RandFloatMinMax(-length, length);
	std::cout << "Z: " << z << std::endl;
	chunkPos = Vector3(x, 0, z);
	return chunkPos;
}

std::string BuildMap::GenerateRandObj(int x)
{
	std::string filename;
	switch (x)
	{
	case 1:
	{
		filename = "OBJ//Building.obj";
	}
	break;
	case 2:
	{
		filename = "OBJ//Building.obj";
	}
	break;
	case 3:
	{
		//filename = ;
	}
	break;
	}
	return filename;
}

std::string BuildMap::GetObjTex(int x)
{
	std::string filename;
	switch (x)
	{
	case 1:
	{
		filename = "Image//color2.tga";
	}
	break;
	case 2:
	{
		filename = "Image//BuildingTex.tga";
	}
	break;
	case 3:
	{

	}
	break;
	}

	return filename;
}

Vector3 BuildMap::GetRandRotate(int x)
{
	Vector3 rotateB;
	switch (x)
	{
	case 1: 
	{
		rotateB = Vector3(0, 90, 0);
	}
	break;
	case 2:
	{
		rotateB = Vector3(0, 180, 0);
	}
	break;
	case 3:
	{
		rotateB = Vector3(0, 270, 0);
	}
	break;
	default:
	{
		rotateB = Vector3(0, 0, 0);
	}
	break;
	}

	return rotateB;
}

Vector3 BuildMap::GetRandScale(int x)
{
	Vector3 scaleB;

	switch (x)
	{
	case 1:
	{
		scaleB = Vector3(0.5, 1, 0.5);
	}
	break;
	case 2:
	{
		scaleB = Vector3(0.5, 1.5, 0.5);
	}
	break;
	case 3:
	{
		scaleB = Vector3(0.5, 2, 0.5);
	}
	break;
	default:
	{
		scaleB = Vector3(0.5, 2.5, 0.5);
	}
	break;
	}

	return scaleB;
}

int BuildMap::GetObjectCount()
{
	return ObjCount;
}