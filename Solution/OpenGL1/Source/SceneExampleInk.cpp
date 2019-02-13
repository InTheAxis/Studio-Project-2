#include "SceneExampleInk.h"



SceneExampleInk::SceneExampleInk()
{
}


void SceneExampleInk::InitDerived()
{
	CUBE.Init(MeshBuilder::GenerateCube(Color(1, 1, 1, 0.5f)), "", Vector3(0, 5, 0));
	QUAD1.Init(MeshBuilder::GenerateQuad(Color(1, 0, 1)), "", Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(10, 10, 10));
	QUAD2.Init("OBJ//test ground.obj", "", Vector3(0, 0.1f, 0));

	CUBE.SetMaterial(dull);
//	QUAD.SetMaterial(dull);
}

void SceneExampleInk::RenderDerived()
{
	RenderObject(&QUAD1);
	RenderObject(&QUAD2);
	RenderObject(&CUBE);
}

void SceneExampleInk::UpdateDerived(double dt)
{
	if (Application::IsKeyPressed('F'))
	{
		CUBE.ChangeColor(Vector3(0, 0, 0));
		QUAD2.ChangeColor(Vector3(0, 0, 0));
	}
}

void SceneExampleInk::UpdateDerivedBounced(double dt)
{
	if (Application::IsKeyPressed(VK_LCONTROL))
	{
		RequestChangeScene(1);
	}
}

SceneExampleInk::~SceneExampleInk()
{
}
