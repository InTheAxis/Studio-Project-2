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
	void MoveMouse(double dt);

	LoadSceneButton play, customisation, exit;
	bool decreaseSize;

	GameObject cursor;

	std::vector<Button*> allButtons;
	int buttonindex, totalbuttons;

	Vector3 prevCursorXY, currentCursorXY;
	Vector3 deltaPosCursor; 
	const float MOUSE_SENS = 0.1f;

};

#endif // !SCENE_START
