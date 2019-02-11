#ifndef SCENE_LEVELSELECT
#define SCENE_LEVELSELECT

#include "Scene.h"

class SceneLevelSelect : public Scene
{
public:
	SceneLevelSelect();
	~SceneLevelSelect();
protected:
	GameObject CUBE;

	virtual void InitDerived();
	virtual void RenderDerived();
	virtual void UpdateDerived(double dt);
	virtual void UpdateDerivedBounced(double dt);
};

#endif // !SCENE_START

