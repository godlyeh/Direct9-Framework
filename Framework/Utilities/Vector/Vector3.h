/*
	
	Vector3

	3D Vector handling

*/

class Vec3
{
public:
	inline Vec3(void)									{ }
	inline Vec3(float X, float Y, float Z)				{ x = (double)X; y = (double)Y; z = (double)Z; }
	inline Vec3(double X, double Y, double Z)			{ x = X; y = Y; z = Z; }
	inline Vec3(int X, int Y, int Z)					{ x = (double)X; y = (double)Y; z = (double)Z; }
	inline Vec3(const Vec3& v)							{ x = v.x; y = v.y; z = v.z; }
	inline Vec3(float rgfl[3])							{ x = rgfl[0]; y = rgfl[1]; z = rgfl[2]; }

public:
	inline Vec3 operator -	(const Vec3& v) const		{ return Vec3(x - v.x, y - v.y, z - v.z); }
	inline Vec3 operator -	(double d) const			{ return Vec3(x - d, y - d, z - d); }
	inline Vec3 operator -	(float fl) const			{ return Vec3(x - (double)fl, y - (double)fl, z - (double)fl); }
	inline Vec3 operator -	(int n) const				{ return Vec3(x - (double)n, y - (double)n, z - (double)n); }
	inline Vec3	operator -	(void) const				{ return Vec3(-x, -y, -z); }
	inline int	operator == (const Vec3& v) const		{ return x == v.x && y == v.y && z == v.z; }
	inline int	operator != (const Vec3& v) const		{ return !(*this == v); }
	inline Vec3 operator +	(const Vec3& v) const		{ return Vec3(x + v.x, y + v.y, z + v.z); }
	inline Vec3 operator +	(double d) const			{ return Vec3(x + d, y + d, z + d); }
	inline Vec3 operator +	(float fl) const			{ return Vec3(x + (double)fl, y + (double)fl, z + (double)fl); }
	inline Vec3 operator +	(int n) const				{ return Vec3(x + (double)n, y + (double)n, z + (double)n); }
	inline Vec3 operator *	(const Vec3& v) const		{ return Vec3(x * v.x, y * v.y, z * v.z); }
	inline Vec3 operator *	(double d) const			{ return Vec3(x * d, y * d, z * d); }
	inline Vec3 operator *	(float fl) const			{ return Vec3(x * (double)fl, y * (double)fl, z * (double)fl); }
	inline Vec3 operator *	(int n) const				{ return Vec3(x * (double)n, y * (double)n, z * (double)n); }
	inline Vec3 operator /	(const Vec3& v) const		{ return Vec3(x / v.x, y / v.y, z / v.z); }
	inline Vec3 operator /	(double d) const			{ return Vec3(x / d, y / d, z / d); }
	inline Vec3 operator /	(float fl) const			{ return Vec3(x / (double)fl, y / (double)fl, z / (double)fl); }
	inline Vec3 operator /	(int n) const				{ return Vec3(x / (double)n, y / (double)n, z / (double)n); }

public:
	double x, y, z;
};