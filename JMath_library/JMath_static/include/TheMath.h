
#pragma once
#ifndef _THE_MATH_H_
#define _THE_MATH_H_

#include <math.h>
#include <ostream>

#define PI 3.14159

class JMath
{
public:
	/*
	returns the given angle in degrees converted to radians
	*/
	static float DegreeToRadians(float angleInDegrees)
	{
		return angleInDegrees * (PI / 180);
	}

	/*
	returns given angle in radians converted to degrees
	*/
	static float RadiansToDegrees(float angleInRadians)
	{
		return angleInRadians * (180 / PI);
	}

	/*
	returns true if given result is within delta of expected result using
	formula: (fabs(result - expected) < delta)
	*/
	static bool FloatEquals(const float& result, const float& expected, const float delta)
	{
		return (fabs(result - expected) < delta);
	}

	/*
	return float representing linear interpolation of given percentage between 2 given scalar values.
	NOTE: expect given percent to be value between 0 and 1;
	*/
	static float LERP(float begin, float end, float percent)
	{
		return (begin + (end - begin) * percent);
	}

	/*
	return true if given unsigned integer is a power of two else returns false
	*/
	static bool IsPowerOfTwo(const unsigned int num)
	{
		unsigned int n = num;
		//shift bits to right (divide by two) until get a set bit that is most significant or not
		while (((n & 1) == 0) && n > 1) //while num is even and greater than 1;
		{
			n >>= 1; //shift bits to the right one space
		}
		//if found a bit set to 1 and it's not most significant (i.e. n > 1) then return false
		//else return true;
		return (n == 1);
	}

	/*
	Return the next highest power of 2 of the given 32-bit value if the value is not a power of 2.  Otherwise, will return the value.
	*/
	static unsigned int GetNextPowerOfTwo(const unsigned int value)
	{
		unsigned int v = value;
		//check edge case of 0
		if (value == 0)
			return 0;
		/*copy the most significant bit to all lower bits, then add 1 which results in carry that
		sets all lower bits to 0 and one bit beyond to 1.  If the original number was a power of 2
		then the decrement will reduce it by one less, so then round up to original value.
		*/
		v--;
		v |= v >> 1;
		v |= v >> 2;
		v |= v >> 4;
		v |= v >> 8;
		v |= v >> 16;
		v++;

		return v;
	}
};

class Vector2
{
public:
	Vector2();
	Vector2(float a_x, float a_y);
	Vector2(Vector2& other);

	~Vector2();

	float x, y;

	//operator overloads
	Vector2& operator=(const Vector2& rhs);

	Vector2 operator+(const Vector2& other);
	Vector2& operator+=(const Vector2& rhs);

	Vector2 operator-(const Vector2& other);
	Vector2& operator-=(const Vector2& other);

	Vector2 operator-();

	Vector2 operator*(const float scalar);
	void operator*=(const float scalar);

	/*
	returns true if given other Vector2 is either the same object as this or x and y are equal, else returns false
	*/
	bool operator==(const Vector2& other);

	friend bool operator==(const Vector2& lhs, const Vector2& rhs);

	/*
	returns false if given other Vector2 is either the same object as this or x and y are equal, else returns true
	*/
	bool operator!=(const Vector2& other);

	friend bool operator!=(const Vector2& lhs, const Vector2& rhs);

	friend std::ostream& operator<<(std::ostream& out, const Vector2& v);

	//vector math functions
	/*
	returns magnitude of this vector
	*/
	float Magnitude();

	/*
	normalize this Vector2
	*/
	void Normalize();

	/*
	return normalized Vector2 from values of this one. This vector is not changed.
	*/
	Vector2 GetNormal();

	/*
	return dot product of this vector and given other vector
	*/
	float DotProduct(const Vector2& other);

	//return Vector2 perpendicular to this one
	Vector2 GetPerp();

	/*
	Returns new vector linear interpolated the given percent of the given vectors
	i.e. (start + percent * (end - start))
	*/
	Vector2 GetLERP(const Vector2& end, float const percent);

	/*
	Returns new vector linear interpolated the given percent of the given vectors
	i.e. (start + percent * (end - start))
	*/
	static Vector2 LERP(const Vector2& start, const Vector2& end, float percent);

};

enum MATRIX_MAJOR
{
	ROW,
	COL
};

//need to declare because of GetVector3() static function's use of Matrix3
class Matrix3;

class Vector3
{
public:
	Vector3();
	Vector3(float a_x, float a_y, float a_z);

	~Vector3();

	float x, y, z;

	//operator overloads
	Vector3& operator=(const Vector3& other);

	Vector3 operator+(const Vector3& other);
	Vector3& operator+=(const Vector3& other);

	Vector3 operator-(const Vector3& other);
	Vector3& operator-=(const Vector3& other);

	Vector3 operator*(const float scalar);
	void operator*=(const float scalar);

	Vector3 operator-();

	/*
	returns true if Vector not zero (Vector4 (0,0,0,0)) else returns false;
	*/
	bool operator!();
	/*
	returns true if given other Vector3 is either the same object as this or x and y are equal, else returns false
	*/
	bool operator==(const Vector3& other);

	friend bool operator==(const Vector3& lhs, const Vector3& rhs);

	/*
	returns false if given other Vector3 is either the same object as this or x and y are equal, else returns true
	*/
	bool operator!=(const Vector3& other);
	
	friend bool operator!=(const Vector3& lhs, const Vector3& rhs);

	/*
	returns value of vector subelement at position of given int
	i.e. myVector3[0] = will return x element, myVector[1] will return y and myVector[2] will return z
	EXPECT given int to be greater than or equal to zero AND less than 3.
	*/
	float operator[](int rhs);
	
	friend std::ostream& operator<<(std::ostream& out, const Vector3& v);

	//vector math functions
	/*
	returns magnitude of this vector
	*/
	float Magnitude();

	/*
	normalize this Vector3
	*/
	void Normalize();

	/*
	return normalized Vector3 from values of this one. This vector is not changed.
	*/
	Vector3 GetNormal();

	/*
	return dot product of this vector and given other vector
	*/
	float DotProduct(const Vector3& other);

	/*
	return Vector3 cross product
	neither this or the given other vector are changed
	*/
	Vector3 CrossProduct(const Vector3& other);

	/*
	Returns new vector linear interpolated the given percent of the given vectors
	i.e. (start + percent * (end - start))
	*/
	Vector3 GetLERP(const Vector3& end, float const percent);

	/*
	Returns new vector linear interpolated the given percent of the given vectors
	i.e. (start + percent * (end - start))
	*/
	static Vector3 LERP(const Vector3& start, const Vector3& end, float percent);

};

class Vector4
{
public:
	Vector4();

	Vector4(const float a_x, const float a_y, const float a_z, const float a_w);
	
	/*
	construct and return a Vector4 from given hex number with values x for the red value, y for the
	green value, z for the blue value and W for the alpha value.  The values will be from 0 to 255.
	assume hex number is from 0x00000000 to 0xFFFFFFFF
	*/
	Vector4(const unsigned int a_hex);

	/*
	construct and return Vector4 as a copy of given Vector4. Note given Vector4 is unchanged during operation.
	*/
	Vector4(const Vector4& other);

	/*
	construct and return a Vector4 from given hex number with values x for the red value, y for the
	green value, z for the blue value and W for the alpha value.  The values will be from 0 to 255.
	assume hex number is from 0x00000000 to 0xFFFFFFFF
	*/
	static Vector4 ConstructFromHex(const unsigned int a_hex);

	Vector4& operator= (const Vector4& rhs);

	Vector4& operator+=(const Vector4& rhs);
	Vector4 operator+(const Vector4& rhs);
	
	Vector4& operator-=(const Vector4& rhs);
	Vector4 operator-(const Vector4& rhs);
	Vector4 operator-();

	/*
	returns ths value of element pointed by given index. 
	i.e. myVector4[0] returns myVector.x, myVector[0] returns myVector.y etc.
	EXPECT: given value must be -1 < index < 4
	*/
	float operator[](const int index);
	
	/*
	returns true if Vector not zero (Vector4 (0,0,0,0)) else returns false;
	*/
	bool operator!();

	Vector4 operator*(const float scalar);
	void operator*=(const float scalar);

	bool operator==(const Vector4& rhs);
	friend bool operator==(const Vector4& lhs, const Vector4& rhs);
	bool operator!=(const Vector4& rhs);
	friend bool operator!=(const Vector4& lhs, const Vector4& rhs);

	/*
	returns the magnitude of this Vector4
	*/
	float Magnitude();

	/*
	return a new Vector4 of this Vectr4 normalized
	*/
	Vector4 GetNormalized();

	/*
	returns true if this Vector4 able to be normalized, and will normalize this object else returns false and leaves this unchanged (i.e. magnitude of this vector
	is zero)
	*/
	bool Normalize();

	friend std::ostream& operator<<(std::ostream& out, const Vector4& rhs);

	float x, y, z, w;
};

/*
Representation of a 3X3 matrix
NOTE: All operations assume column major layout
*/
class Matrix3
{
public:

	Matrix3();
	Matrix3(
		const float m00,
		const float m01,
		const float m02,
		const float m10,
		const float m11,
		const float m12,
		const float m20,
		const float m21,
		const float m22);
	Matrix3(Matrix3& rhs);
	~Matrix3();

	//builds and returns a new identity matrix 
	static Matrix3 Identity();

	/*
	returns new rotation matrix
	*/
	static Matrix3 SetupRotation(float radians);

	/*
	returns new scale matrix
	*/
	static Matrix3 SetupScale(const Vector2& scale);

	/*
	return new translation matrix
	*/
	static Matrix3 SetupTranslation(Vector2& translation);

	static const Vector3 GetVector3(MATRIX_MAJOR type, int index, const Matrix3& matrix);

	//transposes this matrix
	Matrix3& Transpose();

	//returns a matrix3 the transpose of this. This matrix does not change
	Matrix3 GetTranspose();

	/*
	returns new vector the result of transforming the given vector with this matrix. 
	Both the given vector and this matrix remain unchanged.
	*/
	//Vector3 Transform(Vector3 v);

	Matrix3& operator=(const Matrix3& rhs);

	Matrix3 operator+(const Matrix3& rhs);
	Matrix3 operator-(const Matrix3& rhs);
	Matrix3 operator*(const Matrix3& rhs);
	Vector3 operator*(const Vector3& rhs);

	Matrix3& operator+=(const Matrix3& rhs);
	Matrix3& operator-=(const Matrix3& rhs);
	Matrix3& operator*=(const Matrix3& rhs);
	float* operator[](int rhs);

	const bool operator==(const Matrix3& rhs);
	const bool operator!=(const Matrix3& rhs);

	friend std::ostream& operator<<(std::ostream& out, const Matrix3& m);

	float matrix[3][3];
};

#endif
