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
	GridChunk* targetChunk = currentGrid->FindChunk((int)pos.x, (int)pos.z); //gets the pos at which an OBJ is occupying then find its chunks center.
	occupied.push_back(targetChunk->GetCenter()); //sets the chunk's center which its on, and sets it as occupied
}

bool BuildMap::GenerateObj(Grid* currentGrid)
{
	std::vector<GridChunk*> temp = currentGrid->GetAllChunks(); //temp stores all chunks
	int x = Math::RandIntMinMax(0, temp.size() - 1);
	std::vector<GridChunk*> currAdj = temp[x]->GetAdjacents(); //currAdj stores all adjacent chunks
	for (Vector3 &v : occupied) 
	{
		if (v == temp[x]->GetCenter()) //checks if the center of randomised chunk is already a chunk thats occupied
		{
			return false; //if yes, return false, and function gets called again
		}
		for (unsigned int it = 0; it < currAdj.size(); it++) //else it will also check if its adjacent chunk's centers are occupied as well
		{
			if (v == currAdj[it]->GetCenter())
				return false; //if yes, return false, and function gets called again
		}
	}
	location = temp[x]->GetCenter(); //sets location vector3, to the randomised chunks center if its not occupied and also if its adjacent chunks are not occupied
	occupied.push_back(location); //updates the occupied <vector>
	std::vector<GridChunk*> tempAdj = temp[x]->GetAdjacents(); 
	for (unsigned int it = 0; it < tempAdj.size(); it++)
	{
		occupied.push_back(tempAdj[it]->GetCenter()); //updates occupied with the randomised chunks adjacent centers
	}
	location.y = 0.25f; //sets the location of the obj to this height
	++ObjCount; //adds to the count of the object
	return true;
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

	//if the adjacents chunk's center of the current chunk has no paint on it, choose a random chunk thats not occupied to set as next destination for ai to move towards
	bool found = false;
	bool same = false;
	int count = 0;
	std::vector<GridChunk*> temp = currentGrid->GetAllChunks(); //temp stores all chunks
	while (!found) //if a suitable randomised destination is not found
	{
		int x = Math::RandIntMinMax(0, temp.size() - 1); 
		for (unsigned int it = 0; it < occupied.size(); it++) //iterates through all the saved occupied chunk centers
		{
			if (temp[x]->GetCenter() == prevCenter) //if the randomised chunk is the same as the previous chunk center, loop again (to make sure ai doesnt go back and forth)
				same = true;
			if (temp[x]->GetCenter() == occupied[it]) //if any of the occupied matches the center of the randomised chunk
				same = true;
			if (same)
				break; //loop again
		}
		if (!same) //else, a randomised destination has been found
		{
			found = true;
			prevCenter = targetChunk->GetCenter(); 
			return temp[x]->GetCenter(); //return the new destination
		}
		count++;
		if (count == 10) //if loops too many times
			prevCenter = Vector3(0, 0, 20); //return a default location for ai to moves towards
			return Vector3(0, 0, 20);
	}
	
	distanceAI = NULL;
	return Vector3(0, 0, 0);
}


Vector3 BuildMap::GetLocation()
{
	return location;
}

Vector3 BuildMap::GenerateRandNum(int length)
{
	float x = Math::RandFloatMinMax((float)-length, (float)length);
	float z = Math::RandFloatMinMax((float)-length, (float)length);
	chunkPos = Vector3(x, 0, z);
	return chunkPos;
}

std::string BuildMap::GetObjTex(int x)
{
	//get a random texture for buildings
	std::string filename;
	switch (x)
	{
	case 1:
	{
		filename = "Image//BuildingTex2.tga";
	}
	break;
	case 2:
	{
		filename = "Image//BuildingTex.tga";
	}
	break;
	case 3:
	{
		filename = "Image//BuildingTex3.tga";
	}
	break;
	case 4:
	{
		filename = "Image//BuildingTex4.tga";
	}
	break;
	}
	return filename;
}

Vector3 BuildMap::GetRandRotate(int x)
{
	//get random rotate
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
	//get random scale
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