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

void BuildMap::SetOccupied(Grid* currentGrid, Vector3 pos)
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
		for (int it = 0; it < currAdj.size(); it++)
		{
			if (v == currAdj[it]->GetCenter())
				return false;
		}
	}
	location = temp[x]->GetCenter();
	occupied.push_back(location);
	std::vector<GridChunk*> tempAdj = temp[x]->GetAdjacents();
	for (int it = 0; it < tempAdj.size(); it++)
	{
		occupied.push_back(tempAdj[it]->GetCenter());
	}
	location.y = 0.25f;
	++ObjCount;
	return true;
}

Vector3 BuildMap::GetDestination(Grid *currentGrid, Color color, Vector3 AIpos)
{
	//GridChunk* targetChunk = currentGrid->FindChunk((int)AIpos.x, (int)AIpos.z); //Find chunk the AI is on
	//std::vector<GridChunk*> Adjacents = targetChunk->GetAdjacents(); //Get the adjacent chunks of current chunk and pass into vector Adjacents
	//for (int it = 0; it < Adjacents.size(); it++) //iterate throught vector adjacents to get its' cell
	//{
	//	if (Adjacents[it]->GetCenter() != prevCenter) //check if the adjacent chunk was the previous chunk
	//	{
	//		std::vector<GridCell*> AdjCells = Adjacents[it]->GetCells(); //Get the cells within the current chunk
	//		for (int it = 0; it < AdjCells.size(); it++) //iterate through the cells of the current adjacent chunk
	//		{
	//			std::vector<Vertex*> CellVert = AdjCells[it]->GetCellVertex(); //get the vertices of the current cell of the current adjacent chunk
	//			for (int it = 0; it < CellVert.size(); it++) //iterate through the vertices to find the Vert that is colored opposite to its own color
	//			{
	//				if (CellVert[it]->color.r == color.r && CellVert[it]->color.g == color.g && CellVert[it]->color.b == color.b) //if found
	//				{
	//					prevCenter = targetChunk->GetCenter(); //save current chunk's center
	//					return Vector3(CellVert[it]->pos.x, 0, CellVert[it]->pos.y); //return the vertices of the colored area
	//				}
	//			}
	//		}
	//	}
	//}
	//return NULL;
	GridChunk* targetChunk = currentGrid->FindChunk((int)AIpos.x, (int)AIpos.z);
	std::vector<GridChunk*> temp = currentGrid->GetAllChunks();
	Vector3 newLocation;
	for (int it = 0; it < temp.size(); it++)
	{
		if (temp[it]->GetCenter() != prevCenter && temp[it]->GetCenter() != targetChunk->GetCenter())
		{
			std::vector<GridCell*> ChunkCells = temp[it]->GetCells();
			for (int it = 0; it < ChunkCells.size(); it++)
			{
				std::vector<Vertex*> CellVert = ChunkCells[it]->GetCellVertex();
				for (int it = 0; it < CellVert.size(); it++)
				{
					if (CellVert[it]->color.r == color.r && CellVert[it]->color.g == color.g && CellVert[it]->color.b == color.b) //if found
					{
						Vector3 distance = Vector3((CellVert[it]->pos.x - AIpos.x), 0, (CellVert[it]->pos.z - AIpos.z));
						if (distanceAI == NULL)
						{
							distanceAI = distance.Length();
							newLocation = Vector3(CellVert[it]->pos.x, 0, CellVert[it]->pos.z);
						}
						else
						{
							if (distance.Length() > 5 && distance.Length() < distanceAI)
							{
								distanceAI = distance.Length();
								newLocation = Vector3(CellVert[it]->pos.x, 0, CellVert[it]->pos.z);
							}
						}
					}
				}
			}
		}
	}
	distanceAI = NULL;
	return newLocation;
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
		filename = "OBJ//ground-low.obj";
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