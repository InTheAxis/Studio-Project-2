#ifndef SCENE_CUSTOMISATION
#define SCENE_CUSTOMISATION

#include "Scene.h"
#include "Paintable.h"
#include "LoadSceneButton.h"
#include "Car.h"
#include "Cursor.h"

class SceneGarage : public Scene
{
public:
	SceneGarage();
	~SceneGarage();

	enum Vehicle
	{
		V_TAXI,
		V_TRUCK,
		V_F1,

		V_TOTAL
	};
	enum Colour
	{
		C_GREEN = 0,
		C_RED,
		C_BLUE,
		C_YELLOW,
		C_PURPLE,
		C_AQUA,

		C_TOTAL
	};

protected:
	GameObject TAXI;
	GameObject TRUCK;
	GameObject F1;
	GameObject ARROW;
	GameObject BACKGROUND;

	Car* existingCar;

	Cursor mouse;
	LoadSceneButton hoodinkButton, exitButton;
	GameObject hoodinkText,exitText;
	std::vector<Button*> allButtons;

	virtual void InitDerived();
	virtual void RenderDerived();
	virtual void UpdateDerived(double dt);
	virtual void UpdateDerivedBounced(double dt);

	int currentVehicle;
	int currentColor;

	bool selected;
};

#endif 