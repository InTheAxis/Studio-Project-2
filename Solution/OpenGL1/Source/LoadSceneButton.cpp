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
		scale.x = MathExtended::Lerpf(scale.x, 25, 0.7);
		scale.y = MathExtended::Lerpf(scale.y, 25, 0.7);
		scale.z = 1;
	}

	else
	{
		scale.x = -MathExtended::Lerpf(-scale.x, -20, 0.7);
		scale.y = -MathExtended::Lerpf(-scale.y, -20, 0.7);
		scale.z = 1;
	}
}
