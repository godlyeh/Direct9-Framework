/*

	File: VectorMain

	Used for vector math

*/
#include "..\..\Core.h"

void VectorMath::AngleVectors(float *flAngles, float *flForward, float *flRight, float *flUp)
{
	float v16 = sin(flAngles[0] * (M_PI / 180));
	float v15 = cos(flAngles[0] * (M_PI / 180));

	float v12 = sin(flAngles[1] * (M_PI / 180));
	float v13 = cos(flAngles[1] * (M_PI / 180));

	float v11 = sin(flAngles[2] * (M_PI / 180));
	float v14 = cos(flAngles[2] * (M_PI / 180));

	if (flForward)
	{
		flForward[0] = v15 * v13;
		flForward[1] = v15 * v12;
		flForward[2] = -v16;
	}
	if (flRight)
	{
		float v8 = v11 * v16;
		flRight[0] = v14 * v12 - v8 * v13;
		flRight[1] = (v8 * v12 + v14 * v13) * -1.0f;
		flRight[2] = v11 * v15 * -1.0f;
	}
	if (flUp)
	{
		float v10 = v14 * v16;
		flUp[0] = v10 * v13 + v11 * v12;
		flUp[1] = v10 * v12 - v11 * v13;
		flUp[2] = v14 * v15;
	}
}