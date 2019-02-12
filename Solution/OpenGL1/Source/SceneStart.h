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

	//float MoveSelector(float x, float y, float distance, GameObject selector);

	std::vector<Button*> allButtons;
	int buttonindex;
	int totalbuttons;
	/*const std::vector<float> optionposY =
	{
		10, 7.5f, 5
	};*/
};

#endif // !SCENE_START
