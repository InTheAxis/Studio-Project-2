#include "SceneExampleFBO.h"

SceneExampleFBO::SceneExampleFBO()
{
}


void SceneExampleFBO::InitDerived()
{
}

void SceneExampleFBO::RenderDerived()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID);
	glClearColor(1, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	RenderTextOnScreen(&TEXT, "LOADING", Color(1, 1, 1), 1, orthSize.x * 0.5f - 3, orthSize.y * 0.5f);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	RenderTextOnScreen(&TEXT, "PRESS LCTRL, CHECK SCREENSHOTS FOLDER", Color(1, 1, 1), 1, orthSize.x * 0.5f - 3, orthSize.y * 0.5f);
}

void SceneExampleFBO::UpdateDerived(double dt)
{
}

void SceneExampleFBO::UpdateDerivedBounced(double dt)
{
	if (Application::IsKeyPressed(VK_LCONTROL))
	{
		std::vector<Color> test = ReadFromFBO(m_frameBufferID);
		
		WriteFromFBO(m_frameBufferID, "Screenshots//test.tga");
		//RequestChangeScene(1);
	}
}

SceneExampleFBO::~SceneExampleFBO()
{
}
