#include "GameObject.h"



GameObject::GameObject()
{
	this->translate = Vector3(0, 0, 0);
	this->rotate = Vector3(0, 0, 0);
	this->scale = Vector3(1, 1, 1);
}

void GameObject::Init(std::string name, std::string filePathOBJ, std::string filePathTGA, Vector3 translate, Vector3 rotate, Vector3 scale)
{
	this->objectMesh = MeshBuilder::GenerateOBJ(filePathOBJ);
	this->AddTexture(filePathTGA); //load in a texture
	this->ChangeTexture(0); //default 
	if (translate != NULL)
		this->translate = translate;
	if (rotate != NULL)
		this->rotate = rotate;
	if (scale != NULL)
		this->scale = scale;
}

void GameObject::Init(std::string name, Mesh* mesh, std::string filePathTGA, Vector3 translate, Vector3 rotate, Vector3 scale)
{
	this->objectMesh = mesh;
	this->AddTexture(filePathTGA); //load in a texture, put "" if none
	this->ChangeTexture(0); //default 
	if (translate != NULL)
		this->translate = translate;
	if (rotate != NULL)
		this->rotate = rotate;
	if (scale != NULL)
		this->scale = scale; 
}

void GameObject::Render()
{
	objectMesh->Render();
}

void GameObject::Render(unsigned offset, unsigned count)
{
	objectMesh->Render(offset, count);
}

void GameObject::AddTexture(std::string filePathTGA)
{
	if (filePathTGA == "") return;
	this->textureIDs.push_back(LoadTGA(filePathTGA.c_str())); 
}

unsigned GameObject::GetTextureID()
{
	return objectMesh->textureID;
}

void GameObject::ChangeTexture(int textureIndex)
{
	if (textureIDs.size() <= 0) return;
	objectMesh->textureID = this->textureIDs[textureIndex];
}

Material* GameObject::GetMaterial()
{
	return &(objectMesh->material);
}

void GameObject::SetMaterial(Material m)
{
	objectMesh->material = m;
}

Vector3 GameObject::GetTranslate()
{
	return translate;
}
Vector3 GameObject::GetRotate()
{
	return rotate;
}
Vector3 GameObject::GetScale()
{
	return scale;
}
void GameObject::SetTranslate(Vector3 t)
{
	this->translate = t;
}
void GameObject::SetRotate(Vector3 r)
{
	this->rotate = r;
}
void GameObject::SetScale(Vector3 s)
{
	this->scale = s;
}
void GameObject::IncrementTranslate(Vector3 t)
{
	this->translate += t;
}
void GameObject::IncrementRotate(Vector3 r)
{
	this->rotate += r;
}
void GameObject::IncrementScale(Vector3 s)
{
	this->scale += s;
}


GameObject::~GameObject()
{
}
