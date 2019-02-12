#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include "Mesh.h"
#include "Vertex.h"
#include "Vector3.h"
#include "LoadOBJ.h"

/******************************************************************************/
/*!
		Class MeshBuilder:
\brief	Provides methods to generate mesh of different shapes
*/
/******************************************************************************/
class MeshBuilder
{
public:
	static Mesh* GenerateOBJ(const std::string &file_path);
	static Mesh* GenerateText(unsigned numRow, unsigned numCol);
	
	//primitives
	static Mesh* GenerateAxes(float lengthX = 5000, float lengthY = 5000, float lengthZ = 5000);
	static Mesh* GenerateQuad(Color color);
	static Mesh* GenerateCube(Color color);

	//reloading vbo
	static void ReloadVBO(Mesh* targetMesh);
};
#endif