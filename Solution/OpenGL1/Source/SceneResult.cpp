#include "SceneResult.h"

SceneResult::SceneResult()
{

}

void SceneResult::InitDerived()
{
	GetDontDestroyGameObject("floor");
	GetDontDestroyGameObject("paint");
}
void SceneResult::RenderDerived()
{

}

void SceneResult::UpdateDerived(double dt)
{

}

void SceneResult::UpdateDerivedBounced(double dt)
{

}

SceneResult::~SceneResult()
{

}