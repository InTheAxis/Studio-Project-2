#include "SceneStart.h"



SceneStart::SceneStart()
{
}

SceneStart::~SceneStart()
{
}


void SceneStart::InitDerived()
{
	//CUBE.Init(MeshBuilder::GenerateCube(Color(1, 0, 1)), "", Vector3(0, 20, 0));
	Play.Init(MeshBuilder::GenerateCube(Color(1, 0, 1)), "", Vector3(0, 20, 0));
	//CUBE.Init("OBJ//toilet.obj", "Image//toilet.tga", Vector3(0, -20, 0));
	Play.SetMaterial(shiny);


	LevelSelect.Init(MeshBuilder::GenerateCube(Color(1, 0, 1)), "", Vector3(0, 10, 0));
	LevelSelect.SetMaterial(shiny);
}

void SceneStart::RenderDerived()
{
	RenderObject(&Play);
	RenderObject(&LevelSelect);
}

void SceneStart::UpdateDerived(double dt)
{
	//CUBE.IncrementScale(Vector3(dt, dt, dt));
}

void SceneStart::UpdateDerivedBounced(double dt)
{
	//CUBE.IncrementRotate(Vector3(0, 10, 0));
}

