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
		scale.x = MathExtended::Lerpf(scale.x, 17, 0.7);
		scale.y = MathExtended::Lerpf(scale.y, 17, 0.7);
		scale.z = 1;
		//SetScale(Vector3(13, 13, 13));
	}

	else
	{
		scale.x = -MathExtended::Lerpf(-scale.x, -10, 0.7);
		scale.y = -MathExtended::Lerpf(-scale.y, -10, 0.7);
		scale.z = 1;
		/*SetScale(Vector3(10,10,10));*/
	}
}
