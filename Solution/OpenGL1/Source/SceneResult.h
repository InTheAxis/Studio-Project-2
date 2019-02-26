#ifndef SCENE_RESULT_H
#define SCENE_RESULT_H

#include "Scene.h"
#include "Vehicle.h"
#include "Paintable.h"

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

	virtual void InitDerived();
	virtual void RenderDerived();
	virtual void UpdateDerived(double dt);
	virtual void UpdateDerivedBounced(double dt);
};



#endif // ! SCENE_RESULT_H