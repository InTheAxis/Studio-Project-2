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
		SetScale(Vector3(12, 4, 0));
	}

	else
	{
		SetScale(Vector3(10,4,1));
	}
}
