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
		QUAD2.ChangeColor(camera[currentCam]->position);
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
