#include "SceneManager.h"



SceneManager::SceneManager()
{
	//temporary init
	for (int i = 0; i < NUM_OF_SCENES; ++i)
	{
		allScenes[i] = &empty;
	}

	allScenes[START] = &startMenu;
	/*allScenes[LEVEL_SELECT] = &levels;*/
	allScenes[LEVEL_1] = &game;
	allScenes[RESULTS] = &results;
	allScenes[GARAGE] = &garage;
	allScenes[HOOD] = &theHood;
}

Scene* SceneManager::GetFirstScene()
{
	currentIndex = 1;
	return allScenes[currentIndex];
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
		for (GameObject* &go : allScenes[currentIndex]->RetriveDontDestroy())
		{
			std::cout << "Storing \"" << go->GetName() << "\" in memory ";
			std::cout << "from Scene index: " << currentIndex << "\n";
			allScenes[index]->PushToDontDestroy(go);
		}
		currentIndex = index;
		ChangeScene(index);
	}
}

SceneManager::~SceneManager()
{
}
