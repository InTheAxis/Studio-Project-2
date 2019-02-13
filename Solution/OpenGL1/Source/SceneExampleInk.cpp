#include "SceneExampleInk.h"



SceneExampleInk::SceneExampleInk()
{
}


void SceneExampleInk::InitDerived()
{
	CUBE.Init(MeshBuilder::GenerateCube(Color(1, 1, 1, 0.5f)), "", Vector3(0, 5, 0));
	QUAD.Init(MeshBuilder::GenerateQuad(Color(1, 0, 1)), "", Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(10, 10, 10));

	//CUBE.Init("OBJ//toilet.obj", "Image//toilet.tga", Vector3(0, -20, 0));
	CUBE.SetMaterial(shiny);
	std::cout << "Scene2";
}

void SceneExampleInk::RenderDerived()
{
	RenderObject(&QUAD);
	RenderObject(&CUBE);
}

void SceneExampleInk::UpdateDerived(double dt)
{
	//CUBE.IncrementScale(Vector3(dt, dt, dt));
	//CUBE.SetScale(Vector3(1, 1, 1));
	if (Application::IsKeyPressed('F'))
		CUBE.ChangeColor(camera[1]->position);
}

void SceneExampleInk::UpdateDerivedBounced(double dt)
{
	//CUBE.IncrementRotate(Vector3(0, 10, 0));
	if (Application::IsKeyPressed(VK_LCONTROL))
	{
		RequestChangeScene(1);
	}
}

SceneExampleInk::~SceneExampleInk()
{
}
