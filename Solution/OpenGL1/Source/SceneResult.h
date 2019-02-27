#ifndef SCENE_RESULT_H
#define SCENE_RESULT_H

#include "Scene.h"
#include "Vehicle.h"
#include "Paintable.h"
#include "LoadSceneButton.h"
#include "Cursor.h"
class SceneResult : public Scene
{
public:
	SceneResult();
	~SceneResult();

protected:
	GameObject* floor;
	Vehicle* car, *ai;
	Paintable* paintLayer;
	GameObject resultBarL, resultBarR;
	
	Cursor mouse;
	LoadSceneButton exitButton;
	GameObject exitText;

	std::vector<Button*> allButtons;
	
	double elapsed;

	virtual void InitDerived();
	virtual void RenderDerived();
	virtual void UpdateDerived(double dt);
	virtual void UpdateDerivedBounced(double dt);
	virtual void RenderFrameBuffer();
};



#endif // ! SCENE_RESULT_H