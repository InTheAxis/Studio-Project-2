#ifndef SCENE_EXAMPLE_COLL_H
#define SCENE_EXAMPLE_COLL_H

#include "Scene.h"
#include "Car.h"
#include "CollisionHandler.h"

class SceneExampleColl : public Scene
{
public:
	SceneExampleColl();
	~SceneExampleColl();
protected:
	GameObject floor;
	GameObject ramp;
	Car car;
	Collidable test, test2;

	bool collide;

	virtual void InitDerived();
	virtual void RenderDerived();
	virtual void UpdateDerived(double dt);
	virtual void UpdateDerivedBounced(double dt);
};

#endif //! SCENE_EXAMPLE_CAR_H