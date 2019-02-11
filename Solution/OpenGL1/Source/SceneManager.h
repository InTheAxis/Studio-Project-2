#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Scene.h"
//include all yo scenes here
#include "SceneExample.h"
#include "SceneExample2.h"
#include "SceneStart.h"
#include "SceneLevelSelect.h"

class SceneManager
{
public:
	SceneManager();
	Scene* GetFirstScene();

	void SetCurrentScene(Scene**);
	void ChangeScene(int index);
	void PollForSceneChangeEvent();

	~SceneManager();
private:
	Scene** currentScene;
	int currentIndex;

	SceneExample example;
	SceneExample2 example2;
	
	SceneStart StartMenu;
	SceneLevelSelect Levels;

	enum gameScenes
	{
		ENTRY_POINT,
		START,
		LEVEL_SELECT,
		LEVEL_1,
		RESULTS,
		PAUSE,
		NUM_OF_SCENES
	};
	Scene* allScenes[NUM_OF_SCENES];
};

#endif //SCENE_MANAGER_H
