#ifndef _MATRIX_3_H
#define _MATRIX_3_H
#include "TheMath.h"

Matrix3::Matrix3()
{
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			matrix[row][col] = 0;
		}
	}
}

Matrix3::Matrix3(
	const float m00,
	const float m01,
	const float m02,
	const float m10,
	const float m11,
	const float m12,
	const float m20,
	const float m21,
	const float m22)
{
	matrix[0][0] = m00;
	matrix[0][1] = m01;
	matrix[0][2] = m02;
	matrix[1][0] = m10;
	matrix[1][1] = m11;
	matrix[1][2] = m12;
	matrix[2][0] = m20;
	matrix[2][1] = m21;
	matrix[2][2] = m22;
}

Matrix3::Matrix3(Matrix3& rhs)
{
	*this = rhs;
}


Matrix3::~Matrix3()
{
}

float* Matrix3::operator[](int rhs)
{
	float t[]{
		matrix[rhs][0],
			matrix[rhs][1],
			matrix[rhs][2]};

	return matrix[rhs];
}

Matrix3 Matrix3::Identity()
{
	Matrix3 m;
	m.matrix[0][0] = 1;
	m.matrix[0][1] = 0;
	m.matrix[0][2] = 0;

	m.matrix[1][0] = 0;
	m.matrix[1][1] = 1;
	m.matrix[1][2] = 0;

	m.matrix[2][0] = 0;
	m.matrix[2][1] = 0;
	m.matrix[2][2] = 1;

	return m;
}

/*
returns new rotation matrix from given angle in radians
*/
Matrix3 Matrix3::SetupRotation(float radians)
{
	Matrix3 m = Matrix3::Identity();
	m.matrix[0][0] = cos(radians);
	m.matrix[0][1] = -sin(radians);

	m.matrix[1][0] = sin(radians);
	m.matrix[1][1] = cos(radians);
	return m;
}

/*
returns new scale matrix
*/
Matrix3 Matrix3::SetupScale(const Vector2& scale)
{
	Matrix3 m = Matrix3::Identity();

	m.matrix[0][0] = scale.x;
	m.matrix[1][1] = scale.y;
	return m;
}

/*
return new translation matrix
*/
Matrix3 Matrix3::SetupTranslation(Vector2& translation)
{
	Matrix3 m = Matrix3::Identity();
	m.matrix[0][2] = translation.x;
	m.matrix[1][2] = translation.y;
	return m;
}

/*this static function returns a Vector3 representing the given index (zero based) row or column of the given matrix parameter depending
on the given MATRIX_MAJOR enum type.
(e.g.
Matrix3 MyVector(
1, 2, 3,
4, 5, 6,
7, 8, 9);
Matrix3::GetVector3(ROW, 1, MyMatrix); returns a Vector3 representing the second row of MyMatrix => (4, 5, 6)
Matrix3::GetVector3(COL, 0, MyMatrix); returns a Vector3 representing the first column of MyMatrix => (1, 4, 7))
*/
const Vector3 Matrix3::GetVector3(MATRIX_MAJOR type, int index, const Matrix3& matrix)
{
	float x, y, z;
	if (type == ROW)
	{
		x = matrix.matrix[index][0];
		y = matrix.matrix[index][1];
		z = matrix.matrix[index][2];
	}
	else
	{
		x = matrix.matrix[0][index];
		y = matrix.matrix[1][index];
		z = matrix.matrix[2][index];
	}
	return Vector3(x, y, z);
}

//transposes this matrix
Matrix3& Matrix3::Transpose()
{
	Matrix3 result;
	for (int row = 0; row < 3; row++)
	{
		//get the row'th column from this object
		Vector3 v = Matrix3::GetVector3(COL, row, *this);
		//set the temp matrix's row'th row to the vector's values
		result.matrix[row][0] = v.x;
		result.matrix[row][1] = v.y;
		result.matrix[row][2] = v.z;
	}
	*this = result;
	return *this;
}

//returns a matrix3 the transpose of this. This matrix does not change
Matrix3 Matrix3::GetTranspose()
{
	Matrix3 result = *this;
	result.Transpose();
	return result;
}

Matrix3& Matrix3::operator=(const Matrix3& rhs)
{
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			matrix[row][col] = rhs.matrix[row][col];
		}
	}
	return *this;
}

Matrix3 Matrix3::operator+(const Matrix3& rhs)
{
	Matrix3 result = *this;
	result += rhs;
	return result;
}

Matrix3 Matrix3::operator-(const Matrix3& rhs)
{
	Matrix3 result = *this;
	result -= rhs;
	return result;
}

Matrix3 Matrix3::operator*(const Matrix3& rhs)
{
	Matrix3 result = *this;
	result *= rhs;
	return result;
}

Vector3 Matrix3::operator*(const Vector3& rhs)
{
	Vector3 result;
	Vector3 row = Matrix3::GetVector3(ROW, 0, *this);
	result.x = row.DotProduct(rhs);
	row = Matrix3::GetVector3(ROW, 1, *this);
	result.y = row.DotProduct(rhs);
	row = Matrix3::GetVector3(ROW, 2, *this);
	result.z = row.DotProduct(rhs);
	return result;
}

Matrix3& Matrix3::operator+=(const Matrix3& rhs)
{
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			matrix[row][col] += rhs.matrix[row][col];
		}
	}
	return *this;
}

Matrix3& Matrix3::operator-=(const Matrix3& rhs)
{
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			matrix[row][col] -= rhs.matrix[row][col];
		}
	}
	return *this;
}

Matrix3& Matrix3::operator*=(const Matrix3& rhs)
{
	//need to use a temp because use the object during the process and can't modify during.
	Matrix3 result;
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			Vector3 rowVector = Matrix3::GetVector3(ROW, row, *this);
			Vector3 colVector = Matrix3::GetVector3(COL, col, rhs);
			result.matrix[row][col] = rowVector.DotProduct(colVector);
		}
	}
	return *this = result;
}

const bool Matrix3::operator==(const Matrix3& rhs)
{
	if (this == &rhs)
		return true;

	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			if (matrix[row][col] != rhs.matrix[row][col])
				return false;
		}
	}
	return true;
}

const bool Matrix3::operator!=(const Matrix3& rhs)
{
	return !(*this == rhs);
}

std::ostream& operator<<(std::ostream& out, const Matrix3& m)
{
	out << "Matrix3\n******************\n";
	out << "** " << m.matrix[0][0] << "\t" << m.matrix[0][1] << "\t" << m.matrix[0][2] << "  **\n";
	out << "** " << m.matrix[1][0] << "\t" << m.matrix[1][1] << "\t" << m.matrix[1][2] << "  **\n";
	out << "** " << m.matrix[2][0] << "\t" << m.matrix[2][1] << "\t" << m.matrix[2][2] << "  **\n";
	out << "******************\n";
	return out;
}

#endif