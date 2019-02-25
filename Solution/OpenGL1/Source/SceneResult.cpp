#include "SceneResult.h"

SceneResult::SceneResult()
{

}

void SceneResult::InitDerived()
{
	floor = GetDontDestroyGameObject("floor");
	paintLayer = reinterpret_cast<Paintable*>(GetDontDestroyGameObject("paint"));
	car = reinterpret_cast<Vehicle*>(GetDontDestroyGameObject("car"));
	//ai = reinterpret_cast<Vehicle*>(GetDontDestroyGameObject("ai"));
	currentCam = FIXED_TOP_DOWN;

	std::vector<Color> colors = ReadFromFBO(m_frameBufferID);
	//Paintable::CalculateCoverage(colors, car->GetPaint(), ai->GetPaint());

	std::cout << car->GetPaint()->GetPercentage() << ":P%\n";
	//std::cout << ai->GetPaint()->GetPercentage() << ":AI\n";

	WriteFromFBO(m_frameBufferID, "Screenshots//test.tga");
}
void SceneResult::RenderDerived()
{
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