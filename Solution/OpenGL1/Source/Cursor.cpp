#include "Cursor.h"

Cursor::Cursor()
{
}

Cursor::~Cursor()
{
}

void Cursor::SetOrthSize(Vector3 orthSize)
{
	this->orthSize = orthSize;
}

void Cursor::Move(double dt)
{
	//get currentCursorXY
	currentCursorXY = Vector3(Application::cursorX, Application::cursorY, 0);

	//compare the change in position (delta position)
	//delta position is current cursor-prevcursor, basically the offset.
	deltaPosCursor = (currentCursorXY - prevCursorXY) * MOUSE_SENS;
	deltaPosCursor.y *= -1;

	//add deltaPos to mouse's translate
	this->translate += deltaPosCursor;

	//if mousepos is outside orth...
	if (this->translate.x > orthSize.x)
		translate.x = orthSize.x;
	else if (this->translate.x < 0)
		translate.x = 0;
	if (this->translate.y > orthSize.y)
		translate.y = orthSize.y;
	else if (this->translate.y < 0)
		translate.y = 0;

	std::cout << GetTranslate().x << ", " << GetTranslate().y << std::endl;


	//update prevCursorXY
	prevCursorXY = currentCursorXY;
}

void Cursor::CheckHover()
{
	bool Xwithin;
	bool Ywithin;

	
		for (int i = 0; i < allButtons.size(); i++)
		{
			Xwithin = false;
			Ywithin = false;

			if ((translate.x > ((allButtons[i]->GetTranslate().x) - button_Xrange))
				&& (translate.x < ((allButtons[i]->GetTranslate().x) + button_Xrange)))
				Xwithin = !Xwithin;

			if ((translate.y > ((allButtons[i]->GetTranslate().y) - button_Yrange))
				&& (translate.y < ((allButtons[i]->GetTranslate().y) + button_Yrange)))
				Ywithin = !Ywithin;

			if (Xwithin&&Ywithin)
				allButtons[i]->SetHover(true);
			else
				allButtons[i]->SetHover(false);
		}
		
}

void Cursor::SetAllButton(std::vector<Button*> allButtons)
{
	this->allButtons = allButtons;
}

Button * Cursor::GetButton(int index)
{
	return allButtons[index];
}

void Cursor::ResetMousePos()
{
	prevCursorXY = currentCursorXY = (Vector3(Application::cursorX, Application::cursorY, 0));
}


