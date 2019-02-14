#ifndef SCENE_EXAMPLE_CAR_H
#define SCENE_EXAMPLE_CAR_H

#include "Scene.h"
#include "Car.h"
#include "Grid.h"
#include "Paintable.h"

class SceneExampleCar : public Scene
{
public:
	SceneExampleCar();
	~SceneExampleCar();
protected:
	Grid level;
	Paintable paintLayer;
	GameObject floor;
	Car car;

	virtual void InitDerived();
	virtual void RenderDerived();
	virtual void UpdateDerived(double dt);
	virtual void UpdateDerivedBounced(double dt);
};

#endif //! SCENE_EXAMPLE_CAR_H