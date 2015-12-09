/*

File: VectorMain

Used for vector math

*/

#include "Vector3.h"

class VectorMath
{
public:
	void AngleVectors(float *flAngles, float *flForward, float *flRight, float *flUp);
};

#define POW(x)					((x) * (x))
#define M_PI					3.14159265358979323846f
#define M_E						2.71828182845904523536f
#define DotProduct(x,y)			((x)[0] * (y)[0] + (x)[1] * (y)[1] + (x)[2] * (y)[2])
#define VectorSubtract(a,b,c)	{ ((c)[0] = (a)[0] - (b)[0], (c)[1] = (a)[1] - (b)[1], (c)[2] = (a)[2] - (b)[2]) }
#define VectorAdd(a,b,c)		{ ((c)[0] = (a)[0] + (b)[0], (c)[1] = (a)[1] + (b)[1], (c)[2] = (a)[2] + (b)[2]) }
#define VectorCopy(a,b)			{ ((b)[0] = (a)[0], (b)[1] = (a)[1], (b)[2] = (a)[2]) }
#define	VectorScale(v, s, o)	{ ((o)[0] = (v)[0] * (s), (o)[1] = (v)[1] * (s), (o)[2] = (v)[2] * (s)) }
#define VectorDistance(a,b)		sqrt(POW(a[0] - b[0]) + POW(a[1] - b[1]) + POW(a[2] - b[2]))
#define	VectorMA(v, s, b, o)	{ ((o)[0] = (v)[0] + (b)[0] * (s), (o)[1] = (v)[1] + (b)[1] * (s), (o)[2] = (v)[2] + (b)[2] * (s)) }
#define VectorCmp(a,b)			(((a)[0] == (b)[0]) && ((a)[1] == (b)[1]) && ((a)[2] == (b)[2]))
#define VectorTransform(a,b,c)	{ (c)[0] = DotProduct((a), (b)[0]) + (b)[0][3]; (c)[1] = DotProduct((a), (b)[1]) + (b)[1][3]; (c)[2] = DotProduct((a), (b)[2]) + (b)[2][3]; }
#define VectorClear(a)			{ (a)[0] = 0.0f; (a)[1] = 0.0f; (a)[2] = 0.0f; }