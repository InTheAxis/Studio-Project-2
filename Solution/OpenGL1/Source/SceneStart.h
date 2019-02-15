#ifndef SCENE_START
#define SCENE_START

#include "Scene.h"
#include "LoadSceneButton.h"
class SceneStart : public Scene
{
public:
	SceneStart();
	~SceneStart();
protected:
	virtual void InitDerived();
	virtual void RenderDerived();
	virtual void UpdateDerived(double dt);
	virtual void UpdateDerivedBounced(double dt);
private:
	LoadSceneButton play, levelSelect, exit;
	bool decreaseSize;

	GameObject mouse;

	std::vector<Button*> allButtons;
	int buttonindex;
	int totalbuttons;

};

#endif // !SCENE_START
