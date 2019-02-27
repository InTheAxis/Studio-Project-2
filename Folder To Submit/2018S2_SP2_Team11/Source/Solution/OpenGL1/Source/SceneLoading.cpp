#include "SceneLoading.h"



SceneLoading::SceneLoading()
{
}


void SceneLoading::InitDerived()
{
}

void SceneLoading::RenderDerived()
{
	RenderTextOnScreen(&TEXT, "LOADING", Color(1, 1, 1), 1, orthSize.x * 0.5f - 3, orthSize.y * 0.5f);
}

void SceneLoading::UpdateDerived(double dt)
{
}

void SceneLoading::UpdateDerivedBounced(double dt)
{
	if (Application::IsKeyPressed(VK_LCONTROL))
	{
		RequestChangeScene(1);
	}
}

SceneLoading::~SceneLoading()
{
}
