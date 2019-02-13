#include "SceneEmpty.h"



SceneEmpty::SceneEmpty()
{
}


void SceneEmpty::InitDerived()
{
}

void SceneEmpty::RenderDerived()
{
	RenderTextOnScreen(&TEXT, "LOADING", Color(1, 1, 1), 1, 0, 0);
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
