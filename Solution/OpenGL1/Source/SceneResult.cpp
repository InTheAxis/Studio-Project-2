#include "SceneResult.h"

SceneResult::SceneResult()
{

}

void SceneResult::InitDerived()
{
	//getting the persistent gameobjects
	floor = GetDontDestroyGameObject("floor");
	paintLayer = reinterpret_cast<Paintable*>(GetDontDestroyGameObject("paintLayer"));
	car = reinterpret_cast<Vehicle*>(GetDontDestroyGameObject("car"));
	//ai = reinterpret_cast<Vehicle*>(GetDontDestroyGameObject("ai"));
	
	//setting camera
	camera[FIXED_TOP_DOWN]->Init(Vector3(0, 30, 0), Vector3(0, 0, 0), Vector3(0, 0, 1));
	currentCam = FIXED_TOP_DOWN;

	//reading paint
	std::cout << "Calculating Coverage...\n";
	std::vector<Color> colors = ReadFromFBO(m_frameBufferID);
	Paintable::CalculateCoverage(colors, car->GetPaint(), car->GetPaint());
	std::cout << "Done Calculating Coverage\n";

	//temp, for testing
	std::cout << car->GetPaint()->GetPercentage() << ":P%\n";
	//std::cout << ai->GetPaint()->GetPercentage() << ":AI\n";
	WriteFromFBO(m_frameBufferID, "Screenshots//test.tga");
}
void SceneResult::RenderDerived()
{
	//ensure to check if nullptr
	if (floor)
		RenderObject(floor);
	if (paintLayer)
		RenderObject(paintLayer);
}

void SceneResult::UpdateDerived(double dt)
{

}

void SceneResult::UpdateDerivedBounced(double dt)
{

}

SceneResult::~SceneResult()
{

}