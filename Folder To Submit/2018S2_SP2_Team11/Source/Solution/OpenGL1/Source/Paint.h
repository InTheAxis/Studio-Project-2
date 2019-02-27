#ifndef PAINT_H
#define PAINT_H

#include "Vertex.h"

class Paint
{
public:
	Paint();
	Paint(Color paintColor);

	//getter setters
	Color GetPaintColor();
	void SetPaintColor(Color);
	float GetPercentage();
	void SetPercentage(float);

	~Paint();
private:
	Color paintColor;
	float percentageOnLevel;
};

#endif //! PAINT_H