#ifndef SCENE_EXAMPLE2
#define SCENE_EXAMPLE2

#include "Scene.h"
#include "Paintable.h"
#include "Grid.h"

class SceneExampleInk : public Scene
{
public:
	SceneExampleInk();
	~SceneExampleInk();
protected:
	Grid level;
	GameObject floor;
	Paintable paintLayer;

	Paint yellow, purple;

	virtual void InitDerived();
	virtual void RenderDerived();
	virtual void UpdateDerived(double dt);
	virtual void UpdateDerivedBounced(double dt);
	virtual void RenderFrameBuffer();
};

#endif // !SCENE_EXAMPLE
