#include "SceneExampleInk.h"



SceneExampleInk::SceneExampleInk()
{
}


void SceneExampleInk::InitDerived()
{

	floor.Init("OBJ//ground-low.obj", "Screenshots//test.tga", Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));
	paintLayer.Init("OBJ//ground-high.obj", "", Vector3(0, 0.3f, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));

	floor.SetMaterial(dull);
	paintLayer.SetMaterial(dull);

	std::cout << "Generating grid for level\n";
	level.GenerateGrid(paintLayer.GetVBO());
	std::cout << "Done!\n";

	yellow.SetPaintColor(Color(1, 1, 0));
	purple.SetPaintColor(Color(1, 0, 1));
}

void SceneExampleInk::RenderDerived()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	RenderObject(&paintLayer);
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
