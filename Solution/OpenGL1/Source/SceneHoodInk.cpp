#include "SceneHoodInk.h"

SceneHoodInk::SceneHoodInk()
{

}

void SceneHoodInk::InitDerived()
{
	Taxi.Init("Taxi", "OBJ//Taxi.obj", "Image//red.tga", Vector3(0, 0, 0));
	Taxi.CreateRigidBody(Vector3(0, 0, 10), 1200, 0.1f, 0.09f);
	TaxiHood.Init("TaxiHood", "OBJ//TaxiHood.obj", "Image//Blue.tga", Vector3(0, 0, 0));
	TaxiWheels.Init("Taxi", "OBJ//TaxiWheels.obj", "Image//red.tga", Vector3(0, 0, 0));

	Truck.Init("Taxi", "OBJ//Taxi.obj", "Image//red.tga", Vector3(0, 0, 0));
	Truck.CreateRigidBody(Vector3(0, 0, 10), 1200, 0.1f, 0.09f);
	TruckHood.Init("TaxiHood", "OBJ//TaxiHood.obj", "Image//Blue.tga", Vector3(0, 0, 0));
	TruckWheels.Init("Taxi", "OBJ//TaxiWheels.obj", "Image//red.tga", Vector3(0, 0, 0));
	
	Floor.Init("floor", "OBJ//ground-low-flat.obj", "Image//color2.tga");
	PaintLayer.Init("paintLayer", "OBJ//ground-high.obj", "", Vector3(0, 0.25f, 0));

	Taxi.SetMaterial(shiny);
	Floor.SetMaterial(dull);
	PaintLayer.SetMaterial(dull);

	std::cout << "Generating grid for level\n";
	Level.GenerateGrid(PaintLayer.GetVBO());
	std::cout << "Done!\n";
}

void SceneHoodInk::RenderDerived()
{
	RenderObject(&Floor);
	RenderObject(&PaintLayer);
	//RenderObject(&Taxi); RenderObject(&TaxiHood); RenderObject(&TaxiWheels);    // Taxi
	RenderObject(&Truck); RenderObject(&TruckHood); RenderObject(&TruckWheels); // Truck
}

void SceneHoodInk::UpdateDerived(double dt)
{

}

void SceneHoodInk::UpdateDerivedBounced(double dt)
{

}

SceneHoodInk::~SceneHoodInk()
{
}