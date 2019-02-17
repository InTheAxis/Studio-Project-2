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
	RenderTextOnScreen(&TEXT, "LOADING", Color(1, 1, 1), 1, orthSize.x * 0.5f - 3, orthSize.y * 0.5f);
	glReadBuffer(GL_COLOR_ATTACHMENT0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void SceneExampleFBO::UpdateDerived(double dt)
{
}

void SceneExampleFBO::UpdateDerivedBounced(double dt)
{
	if (Application::IsKeyPressed(VK_LCONTROL))
	{
		ScreenshotToTGA(m_frameBufferID, "test.tga");
		//RequestChangeScene(1);
	}
}

SceneExampleFBO::~SceneExampleFBO()
{
}
