#ifndef SCENE_EXAMPLE_FBO
#define SCENE_EXAMPLE_FBO

#include "Scene.h"

class SceneExampleFBO : public Scene
{
public:
	SceneExampleFBO();
	~SceneExampleFBO();
protected:

	virtual void InitDerived();
	virtual void RenderDerived();
	virtual void UpdateDerived(double dt);
	virtual void UpdateDerivedBounced(double dt);
};

#endif // !SCENE_EXAMPLE_FBO
