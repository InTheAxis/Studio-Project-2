#include "SceneManager.h"



SceneManager::SceneManager()
{
	currentIndex = 0; //default
	
	allScenes[0] = &example;
	allScenes[1] = &example2;
}

Scene* SceneManager::GetScene(int index)
{
	currentIndex = index;
	if (index >= NUM_OF_SCENES)
		return nullptr;
	else
		return allScenes[index];
}

Scene* SceneManager::GetNextScene()
{
	return GetScene(currentIndex + 1);
}

SceneManager::~SceneManager()
{
}
