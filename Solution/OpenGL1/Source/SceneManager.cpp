#include "SceneManager.h"



SceneManager::SceneManager()
{
	allScenes[0] = &example;
	allScenes[1] = &example2;

	//allScenes[0] = &StartMenu;
	//allScenes[1] = &Levels;
}

Scene* SceneManager::GetFirstScene()
{
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
	if (allScenes[0]->GetChangeSceneEvent(&index))
	{
		ChangeScene(index);
	}	
}

SceneManager::~SceneManager()
{
}
