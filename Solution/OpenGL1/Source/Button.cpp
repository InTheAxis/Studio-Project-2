#include "Button.h"

Button::Button()
{
	onClick = hover = false;
}

bool Button::GetOnClickEvent()
{
	return onClick;
}

void Button::SetOnClickEvent(bool b)
{
	onClick = false;	//reset after button is pressed
}

Button::~Button()
{
}




