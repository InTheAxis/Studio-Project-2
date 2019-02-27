#include "SceneExampleInk.h"



SceneExampleInk::SceneExampleInk()
{
}


void SceneExampleInk::InitDerived()
{

	floor.Init("floor", "OBJ//taxi.obj", "Screenshots//test.tga", Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));
	paintLayer.Init("paint", "OBJ//ground-high.obj", "", Vector3(0, 0.3f, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));

	floor.SetMaterial(dull);
	paintLayer.SetMaterial(dull);

	std::cout << "Generating grid for level\n";
	level.GenerateGrid(paintLayer.GetVBO());
	std::cout << "Done!\n";

	yellow.SetPaintColor(Color(1, 1, 0));
	purple.SetPaintColor(Color(1, 0, 1));

}

void SceneExampleInk::RenderFrameBuffer()
{
	RenderObject(&floor, false);
}

void SceneExampleInk::RenderDerived()
{	
	RenderObject(&floor);
	RenderObject(&paintLayer);
}

void SceneExampleInk::UpdateDerived(double dt)
{
	if (Application::IsKeyPressed('F'))
	{
		paintLayer.ChangeColor(&level, camera[currentCam]->position, Color(1,0,1));
	}

	if (Application::IsKeyPressed('G'))
	{
		paintLayer.ChangeColor(&level, camera[currentCam]->position, Color(1, 1, 0));
	}
}

void SceneExampleInk::UpdateDerivedBounced(double dt)
{
	if (Application::IsKeyPressed(VK_LCONTROL))
	{
		RequestChangeScene(1);
	}

	if (Application::IsKeyPressed(VK_RETURN))
	{
		Paintable::CalculateCoverage(ReadFromFBO(m_frameBufferID), &yellow, &purple);

		std::cout << yellow.GetPercentage() << "Y\n";
		std::cout << purple.GetPercentage() << "P\n";

		WriteFromFBO(m_frameBufferID, "Screenshots//test.tga");
	}
}

SceneExampleInk::~SceneExampleInk()
{
}
