#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Scene.h"
//include all yo scenes here
//test scenes
#include "SceneExampleCar.h"
#include "SceneExampleInk.h"
#include "SceneExampleCarInk.h"
#include "SceneExampleFBO.h"
//actual scenes
#include "SceneEmpty.h"
#include "SceneStart.h"
#include "SceneLevelSelect.h"
#include "SceneGame.h"
#include "SceneCustomisation.h"

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

	//testing
	SceneGame example;

	//actual
	SceneEmpty empty;
	SceneStart startMenu;
	SceneLevelSelect levels;
	SceneGame game;
	SceneCustomisation garage;

	enum gameScenes
	{
		ENTRY_POINT,
		START,
		LEVEL_SELECT,
		LEVEL_1,
		RESULTS,
		PAUSE,
		CUSTOMISATION_SCREEN,

		NUM_OF_SCENES
	};
	Scene* allScenes[NUM_OF_SCENES];
};

#endif //SCENE_MANAGER_H
