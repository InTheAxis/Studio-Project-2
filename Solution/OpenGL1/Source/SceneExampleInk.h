#ifndef SCENE_EXAMPLE2
#define SCENE_EXAMPLE2

#include "Scene.h"
#include "Paintable.h"

class SceneExampleInk : public Scene
{
public:
	SceneExampleInk();
	~SceneExampleInk();
protected:
	GameObject QUAD1;
	Paintable QUAD2;

	virtual void InitDerived();
	virtual void RenderDerived();
	virtual void UpdateDerived(double dt);
	virtual void UpdateDerivedBounced(double dt);
};

#endif // !SCENE_EXAMPLE
