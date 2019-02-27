#include "Light.h"

Light::Light()
{
	this->type = LIGHT_DIRECTIONAL;
	this->position.Set(0, 30, -20);
	this->defaultPos = position;
	this->color.Set(1, 1, 1);
	this->power = 1;
	this->kC = 1;
	this->kL = 0.01f;
	this->kQ = 0.001f;
	this->cosCutoff = cosf(Math::DegreeToRadian(45));
	this->cosInner = cosf(Math::DegreeToRadian(30));
	this->exponent = 3.0f;
	this->spotDirection.Set(0.0f, 1.0f, 0.0f);

	this->enabled = true;
}

Light::~Light()
{
}