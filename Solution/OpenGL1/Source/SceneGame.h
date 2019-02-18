#ifndef SCENE_GAME_H
#define SCENE_GAME_H
#include "Scene.h"
#include "LoadSceneButton.h"
#include "Cursor.h"

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
	GameObject car;
	GameObject skybox;
	std::vector<Button*> allButtons;
	
	int buttonIndex;

	const int NUM_OF_BUTTONS = 2;
};

#endif
