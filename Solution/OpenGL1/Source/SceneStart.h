#ifndef SCENE_START
#define SCENE_START

#include "Scene.h"
#include "LoadSceneButton.h"
#include "Cursor.h"
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
	LoadSceneButton play, garage, exit;
	GameObject background,title,playText, garageText, exitText,car;


	Cursor mouse;

	std::vector<Button*> allButtons;
	int buttonindex, totalbuttons;

	Vector3 prevCursorXY, currentCursorXY;
	Vector3 deltaPosCursor; 
	const float MOUSE_SENS = 0.1f;

};

#endif // !SCENE_START
