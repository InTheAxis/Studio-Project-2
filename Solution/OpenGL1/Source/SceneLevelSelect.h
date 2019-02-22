#ifndef SCENE_LEVELSELECT
#define SCENE_LEVELSELECT

#include "Scene.h"
#include "LoadSceneButton.h"
#include "Cursor.h"

class SceneLevelSelect : public Scene
{
public:
	SceneLevelSelect();
	~SceneLevelSelect();
protected:
	virtual void InitDerived();
	virtual void RenderDerived();
	virtual void UpdateDerived(double dt);
	virtual void UpdateDerivedBounced(double dt);
private:
	GameObject title,level1Text,level2Text,level3Text;
	Cursor mouse;
	LoadSceneButton level1, level2, level3;
	std::vector<Button*> allButtons;
	int buttonindex;
	int totalbuttons;
};

#endif // !SCENE_LEVELSELECT

