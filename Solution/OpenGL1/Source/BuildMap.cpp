#include "BuildMap.h"
#include <ctime>


BuildMap::BuildMap()
{
	ObjCount = 0;
	location = Vector3(0, 0, 0);
}

BuildMap::~BuildMap()
{

}

bool BuildMap::GenerateObj(Grid* currentGrid)
{
	std::vector<GridChunk*> temp = currentGrid->GetAllChunks();
	int x = Math::RandIntMinMax(0, temp.size() - 1);
	std::vector<GridChunk*> currAdj = temp[x]->GetAdjacents();
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

Vector3 BuildMap::GetLocation()
{
	return location;
}

Vector3 BuildMap::GenerateRandNum(int length)
{
	float x = Math::RandFloatMinMax(-length, length);
	float z = Math::RandFloatMinMax(-length, length);
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