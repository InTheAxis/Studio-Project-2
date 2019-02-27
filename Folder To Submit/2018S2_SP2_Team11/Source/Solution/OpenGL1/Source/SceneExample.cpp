#include "SceneExample.h"



SceneExample::SceneExample()
{
}


void SceneExample::InitDerived()
{
	//CUBE.Init(MeshBuilder::GenerateCube(Color(1, 0, 1)), "", Vector3(0, 20, 0));
	CUBE.Init("cube", "OBJ//toilet.obj", "Image//toilet.tga", Vector3(0, 0, 0));
	CUBE.SetMaterial(shiny);
	std::cout << "Scene1";
}

void SceneExample::RenderDerived()
{
	RenderObject(&CUBE);
}

void SceneExample::UpdateDerived(double dt)
{
	//CUBE.IncrementScale(Vector3(dt, dt, dt));
}

void SceneExample::UpdateDerivedBounced(double dt)
{
	//CUBE.IncrementRotate(Vector3(0, 10, 0));
	if (Application::IsKeyPressed(VK_LCONTROL))
	{
		RequestChangeScene(1);
	}		
}

SceneExample::~SceneExample()
{
}
