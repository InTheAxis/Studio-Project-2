#ifndef SCENE_CUSTOMISATION
#define SCENE_CUSTOMISATION

#include "Scene.h"
#include "Paintable.h"


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
		C_RED = 0,
		C_GREEN,
		C_BLUE,
		C_YELLOW,
		C_PURPLE,
		C_AQUA,

		C_TOTAL
	};
	enum TextColor
	{
		S_RED = 0,
		S_GREEN, 
		S_BLUE, 
		S_YELLOW,
		S_PURPLE,
		S_AQUA,

		S_TOTAL
	};
	enum ArrowColor
	{
		A_RED = 0,
		A_GREEN,
		A_BLUE,
		A_YELLOW,
		A_PURPLE,
		A_AQUA,

		A_TOTAL
	};

protected:
	GameObject TAXI;
	GameObject TRUCK;
	GameObject F1;
	GameObject ARROW;

	GameObject ToiletTest; //Placeholder

	GameObject BACKGROUND;
	GameObject TEXT;

	std::string SColor;
	std::string SVehicle;

	virtual void InitDerived();
	virtual void RenderDerived();
	virtual void UpdateDerived(double dt);
	virtual void UpdateDerivedBounced(double dt);

	int CurrentVehicle;
	int CurrentColor;

	bool Selected;
	int CurrentColorText;
	int CurrentColorArrow;
};

#endif 