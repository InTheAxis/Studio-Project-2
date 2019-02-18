#ifndef SCENE_EXAMPLE_CAR_INK_H
#define SCENE_EXAMPLE_CAR_INK_H

#include "Scene.h"
#include "Car.h"
#include "Grid.h"
#include "Paintable.h"

class SceneExampleCarInk : public Scene
{
public:
	SceneExampleCarInk();
	~SceneExampleCarInk();
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

#endif //! SCENE_EXAMPLE_CAR_INK_H