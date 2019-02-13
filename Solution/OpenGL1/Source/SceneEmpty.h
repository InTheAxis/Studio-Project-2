#ifndef SCENE_EMPTY
#define SCENE_EMPTY

#include "Scene.h"

class SceneEmpty : public Scene
{
public:
	SceneEmpty();
	~SceneEmpty();
protected:

	virtual void InitDerived();
	virtual void RenderDerived();
	virtual void UpdateDerived(double dt);
	virtual void UpdateDerivedBounced(double dt);
};

#endif // !SCENE_EMPTY
