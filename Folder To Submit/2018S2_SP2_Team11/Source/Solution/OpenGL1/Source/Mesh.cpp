
#include "Mesh.h"
#include "GL\glew.h"

/******************************************************************************/
/*!
\brief
Default constructor - generate VBO/IBO here

\param meshName - name of mesh
*/
/******************************************************************************/
Mesh::Mesh()
	: mode(DRAW_TRIANGLES)
	, textureID (0)
{
	// Generate buffers
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &colorBuffer);
	glGenBuffers(1, &indexBuffer);
}

/******************************************************************************/
/*!
\brief
Destructor - delete VBO/IBO here
*/
/******************************************************************************/
Mesh::~Mesh()
{
	// Cleanup VBO here
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &colorBuffer);
	glDeleteBuffers(1, &indexBuffer);

	if (textureID > 0)
		glDeleteTextures(1, &textureID);
}

/******************************************************************************/
/*!
\brief
OpenGL render code
*/
/******************************************************************************/
void Mesh::Render()
{
	// Render VBO here
	glEnableVertexAttribArray(0); // 1st attribute buffer : vertices
	glEnableVertexAttribArray(1); // 2nd attribute buffer : colors
	glEnableVertexAttribArray(2); // 3rd attribute buffer : normals

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(
		0, // attribute 0. Must match the layout in the shader. Usually 0 is for vertex
		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		sizeof(Vertex), // stride
		(void*)0 // array buffer offset
	);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Position));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color)));

	if (textureID > 0)
	{
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color) + sizeof(Vector3)));
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	switch (mode)
	{
		default:	
		case DRAW_TRIANGLES:
			glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);
			break;
		case DRAW_LINES:
			glDrawElements(GL_LINES, indexSize, GL_UNSIGNED_INT, 0);
			break;
		case DRAW_FAN:
			glDrawElements(GL_TRIANGLE_FAN, indexSize, GL_UNSIGNED_INT, 0);
			break;
		case DRAW_TRIANGLE_STRIP:
			glDrawElements(GL_TRIANGLE_STRIP, indexSize, GL_UNSIGNED_INT, 0);
			break;
	}

	if (textureID > 0)
		glDisableVertexAttribArray(3);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}

void Mesh::Render(unsigned offset, unsigned count)
{
	// Render VBO here
	glEnableVertexAttribArray(0); // 1st attribute buffer : vertices
	glEnableVertexAttribArray(1); // 2nd attribute buffer : colors
	glEnableVertexAttribArray(2); // 3rd attribute buffer : normals

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(
		0, // attribute 0. Must match the layout in the shader. Usually 0 is for vertex
		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		sizeof(Vertex), // stride
		(void*)0 // array buffer offset
	);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Position));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color)));

	if (textureID > 0)
	{
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color) + sizeof(Vector3)));
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	switch (mode)
	{
	default:
	case DRAW_TRIANGLES:
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, (void*)(offset * sizeof(GLuint)));
		break;
	case DRAW_LINES:
		glDrawElements(GL_LINES, count, GL_UNSIGNED_INT, (void*)(offset * sizeof(GLuint)));
		break;
	case DRAW_FAN:
		glDrawElements(GL_TRIANGLE_FAN, count, GL_UNSIGNED_INT, (void*)(offset * sizeof(GLuint)));
		break;
	case DRAW_TRIANGLE_STRIP:
		glDrawElements(GL_TRIANGLE_STRIP, count, GL_UNSIGNED_INT, (void*)(offset * sizeof(GLuint)));
		break;
	}

	if (textureID > 0)
		glDisableVertexAttribArray(3);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}

std::vector<Vertex>* Mesh::GetVBData()
{
	return &vertexBufferData;
}

void Mesh::SetVBData(std::vector<Vertex>* vb)
{
	this->vertexBufferData = *vb;
}

void Mesh::SetDefaultVBData(std::vector<Vertex>* v)
{
	this->defaultVBD = *v;
}

void Mesh::ResetVBData()
{
	this->vertexBufferData = this->defaultVBD;
}
