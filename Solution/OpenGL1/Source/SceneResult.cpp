#include "SceneResult.h"

SceneResult::SceneResult()
{

}

void SceneResult::InitDerived()
{
	//getting the persistent gameobjects
	floor = GetDontDestroyGameObject("floor");
	paintLayer = static_cast<Paintable*>(GetDontDestroyGameObject("paintLayer"));
	car = static_cast<Vehicle*>(GetDontDestroyGameObject("car"));
	//ai = reinterpret_cast<Vehicle*>(GetDontDestroyGameObject("ai"));
	
	//generate objs for other gameobjects
	resultBarL.Init("leftbar", MeshBuilder::GenerateQuad(Color(1,0,0)));
	resultBarR.Init("rightbar", MeshBuilder::GenerateQuad(Color(0,1,0)));

	//setting camera
	camera[FIXED_TOP_DOWN]->Init(Vector3(0, 150, 0), Vector3(0, 0, 0), Vector3(0, 0, 1));
	currentCam = FIXED_TOP_DOWN;
}
void SceneResult::RenderDerived()
{
	//ensure to check if nullptr
	if (floor)
		RenderObject(floor);
	if (paintLayer)
		RenderObject(paintLayer);

	RenderObjectOnScreen(&resultBarL, false);
	//RenderObjectOnScreen(&resultBarR, false);
}

void SceneResult::UpdateDerived(double dt)
{
	if (Application::IsKeyPressed('A'))
	{
		Paint test;
		test.SetPaintColor(Color(1, 0, 0));
		//reading paint
		std::cout << "Calculating Coverage...\n";
		std::vector<Color> colors = ReadFromFBO(m_frameBufferID);
		Paintable::CalculateCoverage(colors, car->GetPaint(), &test);
		std::cout << "Done Calculating Coverage\n";

		//temp, for testing
		std::cout << car->GetPaint()->GetPercentage() << ":P%\n";
		//std::cout << ai->GetPaint()->GetPercentage() << ":AI\n";
		WriteFromFBO(m_frameBufferID, "Screenshots//test.tga");
	}
}

void SceneResult::UpdateDerivedBounced(double dt)
{

}

void SceneResult::RenderFrameBuffer()
{
	if (paintLayer)
		RenderObject(paintLayer, false);
}

SceneResult::~SceneResult()
{

}