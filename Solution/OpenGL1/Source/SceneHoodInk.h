#ifndef SCENE_HOOD_INK
#define SCENE_HOOD_INK

#include "Scene.h"
#include "Car.h"
#include "Grid.h"
#include "Paintable.h"
#include "GameObject.h"
#include "Camera.h"
#include "Cursor.h"

class SceneHoodInk : public Scene
{
public:
	SceneHoodInk();
	~SceneHoodInk();

	enum Colour
	{
		C_RED = 0,
		C_GREEN,
		C_BLUE,
		C_YELLOW,
		C_PURPLE,

		C_TOTAL
	};
protected:
	Cursor mouse;

	Grid level;
	Paintable paintLayer;
	GameObject floor, Quad, TEXT;

	Car Taxi;
	GameObject TaxiHood, TaxiWheels;

	Car Truck;
	GameObject TruckHood, TruckWheels;

	Car F1;
	GameObject F1Hood, F1Wheels;

	Paint purple, yellow;

	int CurrentColor;
	int MouseX;
	int MouseY;
	int Test1;
	int Test2;

	float R, G, B;

	//std::string Instructions = "Hold 'F' to paint";
	//std::string Screenshot = "Press 'Enter' to save design";
	//std::string ArrowKeys = "Use the Left and Right arrow keys to change color";

	virtual void InitDerived();
	virtual void RenderFrameBuffer();
	virtual void RenderDerived();
	virtual void UpdateDerived(double dt);
	virtual void UpdateDerivedBounced(double dt);
};

#endif 
