#ifndef SCENE_EMPTY
#define SCENE_EMPTY

#include "Scene.h"

class SceneLoading : public Scene
{
public:
	SceneLoading();
	~SceneLoading();
protected:

	virtual void InitDerived();
	virtual void RenderDerived();
	virtual void UpdateDerived(double dt);
	virtual void UpdateDerivedBounced(double dt);
};

#endif // !SCENE_EMPTY
