#ifndef SCENE_EXAMPLE
#define SCENE_EXAMPLE

#include "Scene.h"

class SceneExample : public Scene
{
public:
	SceneExample();
	~SceneExample();
protected:
	GameObject CUBE;

	virtual void InitDerived();
	virtual void RenderDerived();
	virtual void UpdateDerived(double dt);
	virtual void UpdateDerivedBounced(double dt);
};

#endif // !SCENE_EXAMPLE
