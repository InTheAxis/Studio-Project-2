#include "SceneManager.h"



SceneManager::SceneManager()
{
	//temporary init
	for (int i = 0; i < NUM_OF_SCENES; ++i)
	{
		allScenes[i] = &example2;
	}

	allScenes[1] = &StartMenu;
	allScenes[2] = &Levels;
}

Scene* SceneManager::GetFirstScene()
{
	currentIndex = 0;
	return allScenes[0];
}

void SceneManager::SetCurrentScene(Scene** s)
{
	this->currentScene = s;
}

void SceneManager::ChangeScene(int index)
{
	*currentScene = allScenes[index];
	(*currentScene)->Init();
}

void SceneManager::PollForSceneChangeEvent()
{
	int index = 999;
	if (allScenes[currentIndex]->GetChangeSceneEvent(&index))
	{
		currentIndex = index;
		ChangeScene(index);
	}
}

SceneManager::~SceneManager()
{
}
