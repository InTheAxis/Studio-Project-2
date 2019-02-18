#include "Paint.h"



Paint::Paint()
{
	this->paintColor = Color(1, 1, 1);
	this->percentageOnLevel = 0.0f;
}

Paint::Paint(Color paintColor)
{
	this->paintColor = paintColor;
}

Color Paint::GetPaintColor()
{
	return paintColor;
}

void Paint::SetPaintColor(Color c)
{
	this->paintColor = c;
}

float Paint::GetPercentage()
{
	return percentageOnLevel;
}

void Paint::SetPercentage(float p)
{
	this->percentageOnLevel = p;
}


Paint::~Paint()
{
}
