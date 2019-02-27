#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>
#include "Mesh.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"
#include "Vector3.h"

//A base class for everything that can render

class GameObject
{
public:
	GameObject();
	//init obj, name same as variable
	void Init(std::string name, std::string filePathOBJ, std::string filePathTGA = "", Vector3 translate = NULL, Vector3 rotate = NULL, Vector3 scale = NULL);
	//init primitive with texture, put "" for filepath if no texture
	void Init(std::string name, Mesh* mesh, std::string filePathTGA = "", Vector3 translate = NULL, Vector3 rotate = NULL, Vector3 scale = NULL);
	
	//basically just calls the Mesh::Render
	void Render();
	void Render(unsigned offset, unsigned count);

	void AddTexture(std::string filePathTGA); //adds a tga to a list of textures
	void AddChild(GameObject*); //attach a child to this gameobject

	//getter setters
	unsigned GetTextureID(); //getter for mesh->textureID
	void ChangeTexture(int textureIndex); //setter for textureID
	int GetTextureSize();
	Material* GetMaterial(); //getter for mesh->material
	void SetMaterial(Material);
	std::string GetName();
	std::vector<GameObject*> GetChildren(); //getter for children
	Vector3 GetTranslate();
	Vector3 GetRotate();
	Vector3 GetPivotRotate();
	Vector3 GetPivotPos();
	Vector3 GetScale();
	void SetTranslate(Vector3);
	void SetRotate(Vector3);
	void SetRotateAndPivot(Vector3 rotate, Vector3 pivotPos);
	void SetScale(Vector3);
	void IncrementTranslate(Vector3); //add to translate
	void IncrementRotate(Vector3); //add to rotate
	void IncrementScale(Vector3); //add to scale

	~GameObject();
protected:
	Mesh* objectMesh;
	std::vector<unsigned> textureIDs;
	std::vector<GameObject*> children;

	Vector3 translate, rotate, scale, rotateOnPivot, pivotPosition;
	std::string name;
};

#endif // !GAMEOBJECT_H
