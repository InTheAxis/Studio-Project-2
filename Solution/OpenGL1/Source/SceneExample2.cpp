#include "SceneExample2.h"



SceneExample2::SceneExample2()
{
}


void SceneExample2::InitDerived()
{
	CUBE.Init(MeshBuilder::GenerateCube(Color(1, 0, 1)), "", Vector3(0, 20, 0));
	//CUBE.Init("OBJ//toilet.obj", "Image//toilet.tga", Vector3(0, -20, 0));
	CUBE.SetMaterial(shiny);
}

void SceneExample2::RenderDerived()
{
	RenderObject(&CUBE);
}

void SceneExample2::UpdateDerived(double dt)
{
	//CUBE.IncrementScale(Vector3(dt, dt, dt));
	CUBE.SetScale(Vector3(1, 1, 1));
}

void SceneExample2::UpdateDerivedBounced(double dt)
{
	CUBE.IncrementRotate(Vector3(0, 10, 0));
}

SceneExample2::~SceneExample2()
{
}
