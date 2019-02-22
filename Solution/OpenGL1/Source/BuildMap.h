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
	bool GenerateObj(Grid *currentGrid);
	Vector3 GetLocation();
	std::string GenerateRandObj(int);
	std::string GetObjTex(int);
	Vector3 GetRandRotate(int);
	Vector3 GetRandScale(int);
	int GetObjectCount(); //returns generated object count
private:
	Vector3 GenerateRandNum(int length);
	Vector3 location;
	Vector3 chunkPos;

	int ObjCount;
	std::vector<Vector3> occupied;

	int x;
};
#endif // !BUILD_MAP_H

