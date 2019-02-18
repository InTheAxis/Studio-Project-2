#include "LoadSceneButton.h"

LoadSceneButton::LoadSceneButton()
{
}

LoadSceneButton::~LoadSceneButton()
{
}


void LoadSceneButton::DoAction()
{
	this->onClick = true;
}

void LoadSceneButton::AnimateButton()
{
	if (hover)
	{
		SetScale(Vector3(8, 2, 0));
	}

	else
	{
		SetScale(Vector3(5,1,1));
	}
}
