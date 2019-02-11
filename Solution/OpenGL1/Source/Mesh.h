#ifndef MESH_H
#define MESH_H

#include <string>
#include "Vertex.h"
#include "Material.h"

/******************************************************************************/
/*!
		Class Mesh:
\brief	To store VBO (vertex & color buffer) and IBO (index buffer)
*/
/******************************************************************************/
class Mesh
{
public:
	enum DRAW_MODE
	{
		DRAW_TRIANGLES, //default mode
		DRAW_TRIANGLE_STRIP,
		DRAW_LINES,
		DRAW_FAN,
		DRAW_MODE_LAST,
	};
	Mesh();
	~Mesh();
	void Render();
	void Render(unsigned offset, unsigned count);

	//todo: make these private

	//for meshbuilder to access
	DRAW_MODE mode;
	unsigned vertexBuffer;
	unsigned colorBuffer;
	unsigned indexBuffer;
	unsigned indexSize;
	//for gameobject to access
	Material material;
	unsigned textureID;
};

#endif