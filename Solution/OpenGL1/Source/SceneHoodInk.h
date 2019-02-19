#ifndef SCENE_HOOD_INK
#define SCENE_HOOD_INK

#include "Scene.h"
#include "Car.h"
#include "Grid.h"
#include "Paintable.h"

class SceneHoodInk : public Scene
{
public:
	SceneHoodInk();
	~SceneHoodInk();

protected:
	Grid Level;
	Paintable PaintLayer;
	GameObject Floor;

	Car Taxi;
	GameObject TaxiHood;
	GameObject TaxiWheels;

	Car Truck;
	GameObject TruckHood;
	GameObject TruckWheels;

	//Car F1
	//GameObject F1Hood;
	//GameObject F1Wheels;

	virtual void InitDerived();
	virtual void RenderDerived();
	virtual void UpdateDerived(double dt);
	virtual void UpdateDerivedBounced(double dt);
};

#endif 
