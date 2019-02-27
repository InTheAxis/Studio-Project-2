#include "SceneEmpty.h"



SceneEmpty::SceneEmpty()
{
}


void SceneEmpty::InitDerived()
{
}

void SceneEmpty::RenderDerived()
{
	RenderTextOnScreen(&TEXT, "LOADING", Color(1, 1, 1), 1, orthSize.x * 0.5f - 3, orthSize.y * 0.5f);
}

void SceneEmpty::UpdateDerived(double dt)
{
}

void SceneEmpty::UpdateDerivedBounced(double dt)
{
	if (Application::IsKeyPressed(VK_LCONTROL))
	{
		RequestChangeScene(1);
	}
}

SceneEmpty::~SceneEmpty()
{
}
