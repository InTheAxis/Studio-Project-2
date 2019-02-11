#include "SceneExample.h"



SceneExample::SceneExample()
{
}


void SceneExample::InitDerived()
{
	//CUBE.Init(MeshBuilder::GenerateCube(Color(1, 0, 1)), "", Vector3(0, 20, 0));
	CUBE.Init("OBJ//toilet.obj", "Image//toilet.tga", Vector3(0, -20, 0));
	CUBE.SetMaterial(shiny);
}

void SceneExample::RenderDerived()
{
	RenderObject(&CUBE);
}

void SceneExample::UpdateDerived(double dt)
{
	CUBE.IncrementScale(Vector3(dt, dt, dt));
}

void SceneExample::UpdateDerivedBounced(double dt)
{
	CUBE.IncrementRotate(Vector3(0, 10, 0));
}

SceneExample::~SceneExample()
{
}
