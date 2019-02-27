#include "MeshBuilder.h"
#include <GL\glew.h>


//loading in of objects 
Mesh* MeshBuilder::GenerateOBJ(const std::string &file_path)
{
	//Read vertices, texcoords & normals from OBJ
	std::vector<Position> vertices;
	std::vector<TexCoord> uvs;
	std::vector<Vector3> normals;
	bool success = LoadOBJ(file_path.c_str(), vertices,
		uvs, normals);
	if (!success)
		return NULL;
	
	//Index the vertices, texcoords & normals properly
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	IndexVBO(vertices, uvs, normals, index_buffer_data, vertex_buffer_data);
	
	//Create the mesh and call glBindBuffer, glBufferData
	//Use triangle list and remember to set index size
	Mesh *mesh = new Mesh;

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->SetVBData(&vertex_buffer_data);
	mesh->SetDefaultVBData(&vertex_buffer_data);

	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

//generate text
Mesh* MeshBuilder::GenerateText(unsigned numRow, unsigned numCol)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float width = 1.f / numCol;
	float height = 1.f / numRow;
	int offset = 0;
	for (unsigned i = 0; i < numRow; ++i)
	{
		for (unsigned j = 0; j < numCol; ++j)
		{
			Vertex v;
			float u1 = j * width;
			float v1 = 1.f - height - i * height;			
			// Add 4 vertices into vertex_buffer_data
			v.pos.Set(0, 0, 0);
			v.texCoord.Set(u1, v1);
			vertex_buffer_data.push_back(v);
			v.pos.Set(1, 0, 0);
			v.texCoord.Set(u1 + width, v1);
			vertex_buffer_data.push_back(v);
			v.pos.Set(1, 1, 0);
			v.texCoord.Set(u1 + width, v1 + height);
			vertex_buffer_data.push_back(v);
			v.pos.Set(0, 1, 0);
			v.texCoord.Set(u1, v1 + height);
			vertex_buffer_data.push_back(v);
			// Add 6 indices into index_buffer_data
			index_buffer_data.push_back(offset + 0);
			index_buffer_data.push_back(offset + 1);
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 3);
			index_buffer_data.push_back(offset + 0);
			offset += 4;
		}
	}

	Mesh *mesh = new Mesh;

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->SetDefaultVBData(&vertex_buffer_data);
	mesh->SetVBData(&vertex_buffer_data);

	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a reference Axes; Use red for x-axis, green for y-axis, blue for z-axis
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - x-axis should start at -lengthX / 2 and end at lengthX / 2
\param lengthY - y-axis should start at -lengthY / 2 and end at lengthY / 2
\param lengthZ - z-axis should start at -lengthZ / 2 and end at lengthZ / 2

\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateAxes(float lengthX, float lengthY, float lengthZ)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	v.normal = Vector3(0, 0, 0);
	v.pos.Set(-lengthX, 0, 0);
	v.color.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, 0, 0);
	v.color.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0, -lengthY, 0);
	v.color.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0, lengthY, 0);
	v.color.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0, 0, -lengthZ);
	v.color.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0, 0, lengthZ);
	v.color.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);

	std::vector<GLuint> index_buffer_data;
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(5);

	Mesh *mesh = new Mesh;

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->SetVBData(&vertex_buffer_data);
	mesh->SetDefaultVBData(&vertex_buffer_data);

	mesh->mode = Mesh::DRAW_LINES;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a quad; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param color = color of mesh

\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateQuad(Color color)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	v.color = color;
	v.normal = Vector3(0, 1, 0).Normalize();
	
	v.pos.Set(-0.5f, 0.5f, 0);
	v.texCoord.Set(0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, 0);
	v.texCoord.Set(1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0);
	v.texCoord.Set(1, 1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0);
	v.texCoord.Set(0, 1);
	vertex_buffer_data.push_back(v);

	std::vector<GLuint> index_buffer_data {
		0, 2, 3,
		0, 1, 2
	};

	Mesh *mesh = new Mesh;

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->SetVBData(&vertex_buffer_data);
	mesh->SetDefaultVBData(&vertex_buffer_data);
	
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a cube; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param color = color of mesh

\return Pointer to mesh storing VBO/IBO of cube
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateCube(Color color)
{
	Vertex v;
	v.color = color;
	std::vector<Vertex> vertex_buffer_data;

	//front
	v.normal = Vector3(0, 0, -1).Normalize();
	v.pos.Set(0.5f, -0.5f, -0.5f);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, -0.5f);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, -0.5f);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, -0.5f);
	vertex_buffer_data.push_back(v);

	//right
	v.normal = Vector3(1, 0, 0).Normalize();
	v.pos.Set(0.5f, 0.5f, -0.5f);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, 0.5f);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0.5f);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, -0.5f);
	vertex_buffer_data.push_back(v);

	//back
	v.normal = Vector3(0, 0, 1).Normalize();
	v.pos.Set(0.5f, 0.5f, 0.5f);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, 0.5f);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0.5f);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0.5f);
	vertex_buffer_data.push_back(v);

	//left
	v.normal = Vector3(-1, 0, 0).Normalize();
	v.pos.Set(-0.5f, 0.5f, 0.5f);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, -0.5f);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, -0.5f);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0.5f);
	vertex_buffer_data.push_back(v);

	//top
	v.normal = Vector3(0, 1, 0).Normalize();
	v.pos.Set(0.5f, 0.5f, -0.5f);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, -0.5f);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, 0.5f);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, 0.5f);
	vertex_buffer_data.push_back(v);

	//bottom
	v.normal = Vector3(0, -1, 0).Normalize();
	v.pos.Set(-0.5f, -0.5f, -0.5f);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, -0.5f);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0.5f);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0.5f);
	vertex_buffer_data.push_back(v);

	std::vector<GLuint> index_buffer_data{
		0, 1, 2, 0, 2, 3, //front
		4, 5, 6, 4, 6, 7, //right
		8, 9, 10, 8, 10, 11, //top
		12, 13, 14, 12, 14, 15, //back
		16, 17, 18, 16, 18, 19, //left 
		20, 21, 22, 20, 22, 23 //bottom
	};

	Mesh *mesh = new Mesh;

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->SetVBData(&vertex_buffer_data);
	mesh->SetDefaultVBData(&vertex_buffer_data);

	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh * MeshBuilder::GenerateLines(std::vector<Vector3> &lineStart, std::vector<Vector3> &lineEnd, Color color)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	v.color = color;
	v.normal = Vector3(0, 1, 0).Normalize();
	v.texCoord.Set(0, 0);

	for (unsigned int i = 0; i < lineStart.size() && i < lineEnd.size(); ++i)
	{
		v.pos.Set(lineStart[i].x, lineStart[i].y, lineStart[i].z);
		vertex_buffer_data.push_back(v);
		v.pos.Set(lineEnd[i].x, lineEnd[i].y, lineEnd[i].z);
		vertex_buffer_data.push_back(v);
	}

	std::vector<GLuint> index_buffer_data;
	for (unsigned int i = 0; i < (lineStart.size() * 2) && i < (lineEnd.size() * 2); ++i)
	{
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh;

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->SetVBData(&vertex_buffer_data);
	mesh->SetDefaultVBData(&vertex_buffer_data);

	mesh->mode = Mesh::DRAW_LINES;

	return mesh;
}

void MeshBuilder::ReloadVBO(Mesh* targetMesh)
{
	glBindBuffer(GL_ARRAY_BUFFER, targetMesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, targetMesh->GetVBData()->size() * sizeof(Vertex), &targetMesh->GetVBData()->at(0), GL_STATIC_DRAW);
}