#ifndef MY_MATH_EXTEND_H
#define MY_MATH_EXTEND_H

namespace MathExtended
{

	inline float Lerpf(float value, float targetValue, float weight) //weight must be between 0 to 1
	{
		if (weight > 1) weight = 1;
		else if (weight < 0) weight = 0;
		float ret = value + weight * (targetValue - value);
		if (ret + 0.05f > targetValue) ret = targetValue;
		return ret;
	}
}

#endif
