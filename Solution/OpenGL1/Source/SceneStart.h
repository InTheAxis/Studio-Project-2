#ifndef SCENE_START
#define SCENE_START

#include "Scene.h"

class SceneStart : public Scene
{
public:
	SceneStart();
	~SceneStart();
protected:

	int size;

	bool decreaseSize;
	bool increaseSize;

	GameObject Play;
	GameObject LevelSelect;
	GameObject Exit;

	virtual void InitDerived();
	virtual void RenderDerived();
	virtual void UpdateDerived(double dt);
	virtual void UpdateDerivedBounced(double dt);
};

#endif // !SCENE_START
