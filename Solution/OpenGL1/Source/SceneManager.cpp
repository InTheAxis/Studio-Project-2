#include "SceneManager.h"



SceneManager::SceneManager()
{
	allScenes[0] = &example;
	allScenes[1] = &example2;
}

Scene* SceneManager::GetScene(int index)
{
	return allScenes[index];
}

SceneManager::~SceneManager()
{
}
