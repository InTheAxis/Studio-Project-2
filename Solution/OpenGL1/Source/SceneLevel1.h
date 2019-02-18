#ifndef SCENELEVEL1
#define SCENELEVEL1
#include "Scene.h"
#include "LoadSceneButton.h"

class SceneLevel1 :public Scene
{
public:
	SceneLevel1();
	~SceneLevel1();
protected:
	virtual void InitDerived();
	virtual void RenderDerived();
	virtual void UpdateDerived(double dt);
	virtual void UpdateDerivedBounced(double dt);
private:
	LoadSceneButton resume, exit;
	GameObject car;
	GameObject skybox;
	std::vector<Button*> allButtons;
	int buttonindex;
	int totalbuttons;
};

#endif
