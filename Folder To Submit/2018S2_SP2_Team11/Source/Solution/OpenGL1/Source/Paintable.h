#ifndef PAINTABLE_H
#define PAINTABLE_H

#include "GameObject.h"
#include "Grid.h"
#include "Paint.h"

/*NOTE, ONLY USE SINGLE SURFACE AND HIGH POLY MESHES FOR THIS CLASS*/


class Paintable : public GameObject
{
public:
	Paintable();

	std::vector<Vertex>* GetVBO();
	void ChangeColor(Grid* currentGrid, Vector3 centerVert, Color color, float range = 0.6f); //soft max range is ~0.7f
	void ResetPaint();

	//takes in the vertex colors, the two paints, and stores perecentage covered for each paint
	static void CalculateCoverage(std::vector<Color> vertColors, Paint* team1, Paint* team2);

	~Paintable();
private:
	std::vector<Vertex>* vboPtr;
};

#endif // !PAINTABLE_H
