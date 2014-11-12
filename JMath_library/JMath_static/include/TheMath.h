
#pragma once
#ifndef _THE_MATH_H_
#define _THE_MATH_H_

#include <math.h>
#include <iostream>

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
};

class Vector2
{
public:
	Vector2();
	Vector2(float a_x, float a_y);

	~Vector2();

	float x, y;

	//operator overloads
	Vector2& operator=(const Vector2& rhs);

	Vector2 operator+(const Vector2& other);
	Vector2& operator+=(const Vector2& rhs);

	Vector2 operator-(const Vector2& other);
	Vector2& operator-=(const Vector2& other);

	Vector2 operator*(const float scalar);
	void operator*=(const float scalar);

	/*
	returns true if given other Vector2 is either the same object as this or x and y are equal, else returns false
	*/
	bool operator==(const Vector2& other);

	/*
	returns false if given other Vector2 is either the same object as this or x and y are equal, else returns true
	*/
	bool operator!=(const Vector2& other);

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

	/*
	returns true if given other Vector3 is either the same object as this or x and y are equal, else returns false
	*/
	bool operator==(const Vector3& other);

	/*
	returns false if given other Vector3 is either the same object as this or x and y are equal, else returns true
	*/
	bool operator!=(const Vector3& other);

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

	/*this static function returns a Vector3 representing the given index (zero based) row or column of the given matrix parameter depending
	on the given MATRIX_MAJOR enum type.
	(e.g.
	Matrix3 MyVector(
	1, 2, 3,
	4, 5, 6,
	7, 8, 9);
	Vector3::GetVector3(ROW, 1, MyMatrix); returns a Vector3 representing the second row of MyMatrix => (4, 5, 6)
	Vector3::GetVector3(COL, 0, MyMatrix); returns a Vector3 representing the first column of MyMatrix => (1, 4, 7))
	*/
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

	const bool operator==(const Matrix3& rhs);
	const bool operator!=(const Matrix3& rhs);

	friend std::ostream& operator<<(std::ostream& out, const Matrix3& m);

	float matrix[3][3];
};

#endif
