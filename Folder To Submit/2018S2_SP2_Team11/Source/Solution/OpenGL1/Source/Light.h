#ifndef LIGHT_H
#define LIGHT_H
#include "Vertex.h"
#include "GL\glew.h"

class Light
{
public:
	enum LIGHT_TYPE
	{
		LIGHT_POINT = 0,
		LIGHT_DIRECTIONAL,
		LIGHT_SPOT,
	}; 

	Light();
	~Light();

	LIGHT_TYPE type;
	Vector3 spotDirection;
	float cosCutoff;
	float cosInner;
	float exponent;

	Position position;
	Position defaultPos;
	Color color;
	float power;
	float kC, kL, kQ;


	bool enabled;
};

#endif 