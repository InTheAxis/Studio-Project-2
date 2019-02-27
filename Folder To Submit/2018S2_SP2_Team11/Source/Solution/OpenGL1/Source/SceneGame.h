#ifndef SCENE_GAME_H
#define SCENE_GAME_H
#include "Scene.h"
#include "LoadSceneButton.h"
#include "Cursor.h"
#include "CollectibleSpeedBoost.h"
#include "Car.h"
#include "Grid.h"
#include "Paintable.h"
#include "CollectibleParticleEffect.h"
#include "BuildMap.h"
#include "AI.h"
#include "CollisionHandler.h"
#include <Windows.h>
#include <mmsystem.h>
#include "CollectibleSprayBoost.h"

class SceneGame :public Scene
{
public:
	SceneGame();
	~SceneGame();
protected:
	virtual void InitDerived();
	virtual void RenderDerived();
	virtual void UpdateDerived(double dt);
	virtual void UpdateDerivedBounced(double dt);
private:
	//basically all renderable objects
	Cursor mouse;
	LoadSceneButton resumeButton, exitButton;
	GameObject floor,resumeText,exitText;
	Grid level;
	GridChunk level_chunk;
	Car* car;
	AI ai;
	Paintable paintLayer;
	BuildMap map;

	std::vector<Collidable> Objects;
	Collidable frontWall,backWall,leftWall,rightWall;

	CollectibleSpeedBoost speedboost;
	CollectibleSprayBoost sprayBoost;
	CollectibleParticleEffect particleEffect;
	std::vector<Button*> allButtons;
	
	GameObject needle;
	
	//other variables
	float speedometerAngle;
	double timer;

	//constants
	const int NUM_OF_BUTTONS = 2;
	const int TIMER_MAX = 20;
	const float MAX_SPEED = 160;

};

#endif
