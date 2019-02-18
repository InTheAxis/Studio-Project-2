#include "SceneManager.h"



SceneManager::SceneManager()
{
	//temporary init
	for (int i = 0; i < NUM_OF_SCENES; ++i)
	{
		allScenes[i] = &empty;
	}

	allScenes[0] = &example;
	allScenes[START] = &startMenu;
	allScenes[LEVEL_SELECT] = &levels;
	allScenes[LEVEL_1] = &game;
	allScenes[CUSTOMISATION_SCREEN] = &garage;
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
