#include "SceneStart.h"



SceneStart::SceneStart()
{
	size = 1;
	decreaseSize = false;
	increaseSize = true;
}

SceneStart::~SceneStart()
{
}


void SceneStart::InitDerived()
{
	//CUBE.Init(MeshBuilder::GenerateCube(Color(1, 0, 1)), "", Vector3(0, 20, 0));
	Play.Init(MeshBuilder::GenerateCube(Color(1, 0, 1)), "", Vector3(5, 5, 0),  Vector3(0, 0, 0), Vector3(size, size, size));
	//CUBE.Init("OBJ//toilet.obj", "Image//toilet.tga", Vector3(0, -20, 0));
	Play.SetMaterial(shiny);


	LevelSelect.Init(MeshBuilder::GenerateCube(Color(1, 0, 1)), "", Vector3(0, 15, 0));
	LevelSelect.SetMaterial(shiny);
}

void SceneStart::RenderDerived()
{
	RenderObjectOnScreen(&Play, false);
	RenderObject(&LevelSelect);
}

void SceneStart::UpdateDerived(double dt)
{ 
	//CUBE.IncrementScale(Vector3(dt, dt, dt));

	if (Play.GetScale().x >= 3)
	{
		decreaseSize = true;
	}

	else if (Play.GetScale().x <= 1.1)
	{
		decreaseSize = false;
	}

	if(decreaseSize)
		Play.IncrementScale(Vector3(-dt, -dt, -dt)*1.5);
	
	else if(!decreaseSize)
		Play.IncrementScale(Vector3(dt, dt, dt)*1.5);

	
}

void SceneStart::UpdateDerivedBounced(double dt)
{
	//CUBE.IncrementRotate(Vector3(0, 10, 0));
	if (Application::IsKeyPressed(VK_LCONTROL))
	{
		RequestChangeScene(2);
	}
}

