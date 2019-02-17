#ifndef MY_MATH_EXTEND_H
#define MY_MATH_EXTEND_H

namespace MathExtended
{

	inline float Lerpf(float value, float tragetValue, float weight) //weight must be between 0 to 1
	{
		return value + weight * (tragetValue - value);
	}
}

#endif
