/*
	
	Vector3

	3D Vector handling

*/

class Vec3
{
public:
	inline Vec3(void)									{ }
	inline Vec3(float X, float Y, float Z)				{ x = X; y = Y; z = Z; }
	inline Vec3(double X, double Y, double Z)			{ x = (float)X; y = (float)Y; z = (float)Z; }
	inline Vec3(int X, int Y, int Z)					{ x = (float)X; y = (float)Y; z = (float)Z; }
	inline Vec3(const Vec3& v)							{ x = v.x; y = v.y; z = v.z; }
	inline Vec3(float rgfl[3])							{ x = rgfl[0]; y = rgfl[1]; z = rgfl[2]; }

public:
	inline Vec3 operator -	(const Vec3& v) const		{ return Vec3(x - v.x, y - v.y, z - v.z); }
	inline Vec3 operator -	(double d) const			{ return Vec3(x - (float)d, y - (float)d, z - (float)d); }
	inline Vec3 operator -	(float fl) const			{ return Vec3(x - fl, y - fl, z - fl); }
	inline Vec3 operator -	(int n) const				{ return Vec3(x - (float)n, y - (float)n, z - (float)n); }
	inline Vec3	operator -	(void) const				{ return Vec3(-x, -y, -z); }
	inline int	operator == (const Vec3& v) const		{ return x == v.x && y == v.y && z == v.z; }
	inline int	operator != (const Vec3& v) const		{ return !(*this == v); }
	inline Vec3 operator +	(const Vec3& v) const		{ return Vec3(x + v.x, y + v.y, z + v.z); }
	inline Vec3 operator +	(double d) const			{ return Vec3(x + (float)d, y + (float)d, z + (float)d); }
	inline Vec3 operator +	(float fl) const			{ return Vec3(x + fl, y + fl, z + fl); }
	inline Vec3 operator +	(int n) const				{ return Vec3(x + (float)n, y + (float)n, z + (float)n); }
	inline Vec3 operator *	(const Vec3& v) const		{ return Vec3(x * v.x, y * v.y, z * v.z); }
	inline Vec3 operator *	(double d) const			{ return Vec3(x * (float)d, y * (float)d, z * (float)d); }
	inline Vec3 operator *	(float fl) const			{ return Vec3(x * fl, y * fl, z * fl); }
	inline Vec3 operator *	(int n) const				{ return Vec3(x * (float)n, y * (float)n, z * (float)n); }
	inline Vec3 operator /	(const Vec3& v) const		{ return Vec3(x / v.x, y / v.y, z / v.z); }
	inline Vec3 operator /	(double d) const			{ return Vec3(x / (float)d, y / (float)d, z / (float)d); }
	inline Vec3 operator /	(float fl) const			{ return Vec3(x / fl, y / fl, z / fl); }
	inline Vec3 operator /	(int n) const				{ return Vec3(x / (float)n, y / (float)n, z / (float)n); }

public:
	inline Vec3 Add(float rgfl[3])						{ return Vec3(x + rgfl[0], y + rgfl[1], z + rgfl[2]); }

public:
	operator float *()								{ return &x; } // Vectors will now automatically convert to float * when needed
	operator const float *() const					{ return &x; } // Vectors will now automatically convert to float * when needed

public:
	float x, y, z;
};