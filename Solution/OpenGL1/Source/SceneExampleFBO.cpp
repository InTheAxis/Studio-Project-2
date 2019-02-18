#include "SceneExampleFBO.h"

SceneExampleFBO::SceneExampleFBO()
{
}


void SceneExampleFBO::InitDerived()
{
	test1.Init(MeshBuilder::GenerateCube(Color(1, 1, 0, 1)), "", NULL, NULL, Vector3(10, 10, 10));
	test2.Init(MeshBuilder::GenerateCube(Color(1, 0, 1, 1)), "", Vector3(0, 2, -10), NULL, Vector3(10, 10, 10));
	testCar.GetPaint()->SetPaintColor(Color(1, 1, 0));
}

void SceneExampleFBO::RenderFrameBuffer()
{
	//RenderTextOnScreen(&TEXT, "LOADING", Color(1, 1, 1), 1, orthSize.x * 0.5f - 3, orthSize.y * 0.5f);
	RenderObjectOnScreen(&test1, false);
	RenderObjectOnScreen(&test2, false);
}

void SceneExampleFBO::RenderDerived()
{
	//RenderTextOnScreen(&TEXT, "LOADING", Color(1, 1, 1), 1, orthSize.x * 0.5f - 3, orthSize.y * 0.5f);
	RenderObjectOnScreen(&test1, false);
	RenderObjectOnScreen(&test2, false);
	RenderTextOnScreen(&TEXT, "PRESS ENTER, CHECK SCREENSHOTS FOLDER", Color(1, 1, 1), 1, orthSize.x * 0.5f - 3, orthSize.y * 0.5f);
}

void SceneExampleFBO::UpdateDerived(double dt)
{
}

void SceneExampleFBO::UpdateDerivedBounced(double dt)
{
	if (Application::IsKeyPressed(VK_RETURN))
	{
		std::vector<Color> colors = ReadFromFBO(m_frameBufferID);
		
		Paintable::CalculateCoverage(colors, testCar.GetPaint(), testCar.GetPaint());
		std::cout << testCar.GetPaint()->GetPercentage() << "\n";

		WriteFromFBO(m_frameBufferID, "Screenshots//test.tga");
	}
	if (Application::IsKeyPressed(VK_LCONTROL))
	{
		//RequestChangeScene(1);
	}
}

SceneExampleFBO::~SceneExampleFBO()
{
}
