#include "SceneResult.h"

SceneResult::SceneResult()
{

}

void SceneResult::InitDerived()
{
	//exit button and cursor
	exitButton.Init("exit", "OBJ//LevelsButton.obj", "Image//levels1.tga", Vector3(orthSize.x * 0.5f, 4, 1), Vector3(0, 0, 0), Vector3(0.05f, 0.05f, 0));
	exitText.Init("level3text", "OBJ//LevelsButton.obj", "Image//exitText.tga", Vector3(orthSize.x * 0.5f, 4, 2), Vector3(0, 0, 0), Vector3(10, 10, 0));
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
	resultBarL.Init("leftbar", MeshBuilder::GenerateQuad(car->GetPaint()->GetPaintColor()));
	resultBarR.Init("rightbar", MeshBuilder::GenerateQuad(ai->GetPaint()->GetPaintColor()));

	//setting camera
	camera[FIXED_TOP_DOWN]->Init(Vector3(0, 150, 0), Vector3(0, 0, 0), Vector3(0, 0, 1));
	currentCam = FIXED_TOP_DOWN;

	elapsed = 0;
}
void SceneResult::RenderDerived()
{
	//ensure to check if nullptr
	if (floor)
	{
		floor->ChangeTexture(0); //change to normal texture
		RenderObject(floor, false);
	}
	if (paintLayer)
		RenderObject(paintLayer);

	RenderObjectOnScreen(&mouse, false);

	RenderObjectOnScreen(&exitButton, false);
	RenderObjectOnScreen(&exitText, false);

	if (elapsed < 0)
	{
		RenderObjectOnScreen(&resultBarL, false);
		RenderObjectOnScreen(&resultBarR, false);
	}

	if (exitButton.GetOnClickEvent())
	{
		RemoveDontDestroyGameObject(floor);
		RemoveDontDestroyGameObject(static_cast<GameObject*>(ai));
		RemoveDontDestroyGameObject(static_cast<GameObject*>(paintLayer));
	}
}

void SceneResult::UpdateDerived(double dt)
{
	mouse.Move(dt);
	mouse.CheckHover();
	if (elapsed >= 0)
		elapsed += dt;
	if (elapsed > 1.f)
	{
		//reading paint
		std::cout << "Calculating Coverage...\n";
		std::vector<Color> colors = ReadFromFBO(m_frameBufferID);
		Paintable::CalculateCoverage(colors, car->GetPaint(), ai->GetPaint());
		std::cout << "Done Calculating Coverage\n";

		//scale the result bars
		resultBarL.SetScale(Vector3(3, car->GetPaint()->GetPercentage() * 10, 1));
		resultBarR.SetScale(Vector3(3, ai->GetPaint()->GetPercentage() * 10, 1));
		resultBarL.SetTranslate(Vector3(5, car->GetPaint()->GetPercentage() * 10 + 5, 0));
		resultBarR.SetTranslate(Vector3(orthSize.x - 5, ai->GetPaint()->GetPercentage() * 10 + 5, 0));

		std::cout << car->GetPaint()->GetPercentage() << ":P%\n";
		std::cout << ai->GetPaint()->GetPercentage() << ":AI\n";

		elapsed = -999;
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
		RequestChangeScene(1);
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
	if (floor)
	{
		floor->ChangeTexture(1); //change to plain texture
		RenderObject(floor, false);
	}
}

SceneResult::~SceneResult()
{
}