#include "SceneLevelSelect.h"



SceneLevelSelect::SceneLevelSelect()
{
}

SceneLevelSelect::~SceneLevelSelect()
{
}


void SceneLevelSelect::InitDerived()
{
	//CUBE.Init(MeshBuilder::GenerateCube(Color(1, 0, 1)), "", Vector3(0, 20, 0));
	CUBE.Init("OBJ//toilet.obj", "Image//toilet.tga", Vector3(0, -20, 0));
	CUBE.SetMaterial(shiny);
}

void SceneLevelSelect::RenderDerived()
{
	RenderObject(&CUBE);
}

void SceneLevelSelect::UpdateDerived(double dt)
{
	//CUBE.IncrementScale(Vector3(dt, dt, dt));
}

void SceneLevelSelect::UpdateDerivedBounced(double dt)
{
	//CUBE.IncrementRotate(Vector3(0, 10, 0));
	if (Application::IsKeyPressed(VK_LCONTROL))
	{
		RequestChangeScene(0);
	}
}

