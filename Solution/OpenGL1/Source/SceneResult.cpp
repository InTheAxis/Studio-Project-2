#include "SceneResult.h"

SceneResult::SceneResult()
{

}

void SceneResult::InitDerived()
{
	//exit button and cursor
	exitButton.Init("exit", "OBJ//LevelsButton.obj", "Image//levels1.tga", Vector3(50, 5, 1), Vector3(0, 0, 0), Vector3(1, 1, 0));
	exitText.Init("level3text", "OBJ//LevelsButton.obj", "Image//exitText.tga", Vector3(50, 5, 2), Vector3(0, 0, 0), Vector3(20, 20, 0));
	mouse.Init("mouse", MeshBuilder::GenerateCube(Color(1, 0, 0)), "", Vector3(orthSize.x * 0.5f, orthSize.y * 0.5f, 10), Vector3(0, 0, 0), Vector3(1, 1, 0));

	allButtons.push_back(&exitButton);
	//passing window range and buttons for cursor
	mouse.SetOrthSize(orthSize);
	mouse.SetAllButton(allButtons);

	//getting the persistent gameobjects
	floor = GetDontDestroyGameObject("floor");
	paintLayer = static_cast<Paintable*>(GetDontDestroyGameObject("paintLayer"));
	car = static_cast<Vehicle*>(GetDontDestroyGameObject("car"));
	ai = static_cast<Vehicle*>(GetDontDestroyGameObject("ai"));

	//generate objs for other gameobjects
	resultBarL.Init("leftbar", MeshBuilder::GenerateQuad(car->GetPaint()->GetPaintColor()), "", Vector3(10, 0, 0));
	resultBarR.Init("rightbar", MeshBuilder::GenerateQuad(ai->GetPaint()->GetPaintColor()), "", Vector3(20, 0 , 0));

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

	RenderObjectOnScreen(&mouse, false);

	RenderObjectOnScreen(&exitButton, false);
	RenderObjectOnScreen(&exitText, false);

	RenderObjectOnScreen(&resultBarL, false);
	RenderObjectOnScreen(&resultBarR, false);

	if (exitButton.GetOnClickEvent())
	{
		RemoveDontDestroyGameObject(floor);
		RemoveDontDestroyGameObject(static_cast<GameObject*>(car));
		RemoveDontDestroyGameObject(static_cast<GameObject*>(ai));
		RemoveDontDestroyGameObject(static_cast<GameObject*>(paintLayer));
	}
}

void SceneResult::UpdateDerived(double dt)
{
	mouse.Move(dt);
	mouse.CheckHover();

	if (Application::IsKeyPressed('A'))
	{
		//reading paint
		std::cout << "Calculating Coverage...\n";
		std::vector<Color> colors = ReadFromFBO(m_frameBufferID);
		Paintable::CalculateCoverage(colors, car->GetPaint(), ai->GetPaint());
		std::cout << "Done Calculating Coverage\n";

		//scale the resul bars
		resultBarL.SetScale(Vector3(1, car->GetPaint()->GetPercentage(), 1));
		resultBarR.SetScale(Vector3(1, ai->GetPaint()->GetPercentage(), 1));

		//temp, for testing
		std::cout << car->GetPaint()->GetPercentage() << ":P%\n";
		std::cout << ai->GetPaint()->GetPercentage() << ":AI\n";
		//WriteFromFBO(m_frameBufferID, "Screenshots//test.tga");
	}

	for (Button* b : allButtons)	//for each button in the vector carryout the function
	{
		b->AnimateButton();
	}

	if (exitButton.GetOnClickEvent())
	{
		allButtons[0]->SetHover(false);
		exitButton.SetOnClickEvent(false);
		mouse.ResetMousePos();
		RequestChangeScene(1);//test
	}

	if (Application::leftMouseClick)
	{
		for (unsigned int i = 0; i < allButtons.size(); ++i)
		{
			if (allButtons[i]->GetHover())
			{
				allButtons[i]->DoAction();
				break;
			}

			else
			{
			}
		}
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