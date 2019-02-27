#ifndef BUILD_MAP_H
#define BUILD_MAP_H

#include "GameObject.h"
#include "Grid.h"
#include <iostream>

class BuildMap : public GameObject
{
public:
	BuildMap();
	~BuildMap();
	void SetOccupied(Grid* currentGrid, Vector3 pos);
	bool GenerateObj(Grid *currentGrid);
	Vector3 GetLocation();
	std::string GetObjTex(int);
	Vector3 GetRandRotate(int);
	Vector3 GetRandScale(int);
	int GetObjectCount(); //returns generated object count
	Vector3 GetDestination(Grid *currentGrid, Color color, Vector3 AIpos);
private:
	Vector3 GenerateRandNum(int length);
	Vector3 location;
	Vector3 chunkPos;
	Vector3 prevCenter;
	float distanceAI;

	int ObjCount;
	std::vector<Vector3> occupied;

	int x;
};
#endif // !BUILD_MAP_H

