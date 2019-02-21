#ifndef SCENE_RESULT_H
#define SCENE_RESULT_H

#include "Scene.h"

class SceneResult : public Scene
{
public:
	SceneResult();
	~SceneResult();

protected:
	GameObject result;

	virtual void InitDerived();
	virtual void RenderDerived();
	virtual void UpdateDerived(double dt);
	virtual void UpdateDerivedBounced(double dt);
};



#endif // ! SCENE_RESULT_H