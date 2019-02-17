#include "SceneExampleInk.h"



SceneExampleInk::SceneExampleInk()
{
}


void SceneExampleInk::InitDerived()
{

	QUAD1.Init("OBJ//ground-low.obj", "Image//color2.tga", Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));
	QUAD2.Init("OBJ//ground-high.obj", "", Vector3(0, 0.3f, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));

	QUAD1.SetMaterial(dull);
	QUAD2.SetMaterial(dull);

	std::cout << "Generating grid for level\n";
	level.GenerateGrid(QUAD2.GetVBO());
	std::cout << "Done!\n";
}

void SceneExampleInk::RenderDerived()
{
	RenderObject(&QUAD1);
	RenderObject(&QUAD2);
}

void SceneExampleInk::UpdateDerived(double dt)
{
	if (Application::IsKeyPressed('F'))
	{
		QUAD2.ChangeColor(&level, camera[currentCam]->position, Color(1,0,1));
	}

	if (Application::IsKeyPressed('G'))
	{
		QUAD2.ChangeColor(&level, camera[currentCam]->position, Color(1, 1, 1));
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
