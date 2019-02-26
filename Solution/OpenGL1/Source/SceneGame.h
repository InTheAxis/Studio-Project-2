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
	virtual void RenderFrameBuffer();
private:
	Cursor mouse;
	LoadSceneButton resumeButton, exitButton;
	Car car;

	GameObject floor,resumeText,exitText;
	Grid level;
	GridChunk level_chunk;
	Paintable paintLayer;

	AI ai;
	std::vector<Collidable> Objects;
	BuildMap map;
	Collidable frontWall,backWall,leftWall,rightWall;

	CollectibleSpeedBoost speedboost;
	CollectibleParticleEffect particleEffect;
	std::vector<Button*> allButtons;
	float timer;

	const int NUM_OF_BUTTONS = 2;
	Vector3 temp;
};

#endif
