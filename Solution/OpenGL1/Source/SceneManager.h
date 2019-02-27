#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Scene.h"
//include all yo scenes here
//test scenes, add them solution if needed?
//#include "SceneExampleCar.h"
//#include "SceneExampleColl.h"
//#include "SceneExampleInk.h"
//#include "SceneExampleCarInk.h"
//#include "SceneExampleFBO.h"
//actual scenes
#include "SceneEmpty.h"
#include "SceneStart.h"
#include "SceneLevelSelect.h"
#include "SceneGame.h"
#include "SceneResult.h"
#include "SceneGarage.h"
#include "SceneHoodInk.h"

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

	SceneEmpty empty;
	SceneStart startMenu;
	//SceneLevelSelect levels;  removed
	SceneGame game;
	SceneResult results;
	SceneGarage garage;
	SceneHoodInk theHood;

	enum gameScenes
	{
		EMPTY = 0,
		START,
		HOOD,
		LEVEL_1,
		RESULTS,
		PAUSE,
		GARAGE,

		NUM_OF_SCENES
	};
	Scene* allScenes[NUM_OF_SCENES];
};

#endif //SCENE_MANAGER_H
