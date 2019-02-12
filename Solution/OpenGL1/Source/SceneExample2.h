#ifndef SCENE_EXAMPLE2
#define SCENE_EXAMPLE2

#include "Scene.h"
#include "Paintable.h"

class SceneExample2 : public Scene
{
public:
	SceneExample2();
	~SceneExample2();
protected:
	Paintable CUBE;

	GameObject QUAD;

	virtual void InitDerived();
	virtual void RenderDerived();
	virtual void UpdateDerived(double dt);
	virtual void UpdateDerivedBounced(double dt);
};

#endif // !SCENE_EXAMPLE
