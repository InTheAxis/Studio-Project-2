#include "SceneEmpty.h"



SceneEmpty::SceneEmpty()
{
}


void SceneEmpty::InitDerived()
{
}

void SceneEmpty::RenderDerived()
{
	RenderLoading();
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
