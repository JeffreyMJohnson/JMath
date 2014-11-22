#include "TheMath.h"

/*
Constructs a matrix filled with zeros.
*/
Matrix4::Matrix4()
{
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			matrix[row][col] = 0;
		}
	}
}

/*
The data parameters assume a column major matrix starting in the upper left-hand corner
and going left to right, top to bottom.
E.g.
*************
1   2   3   4
5   6   7   8
9  10  11  12
13 14  15  16
*************
Matrix4(1,2,3,4,5,6,7,8,9,10,11,12, 13, 14, 15, 16);
*/
Matrix4::Matrix4(
	const float m00,
	const float m01,
	const float m02,
	const float m03,
	const float m10,
	const float m11,
	const float m12,
	const float m13,
	const float m20,
	const float m21,
	const float m22,
	const float m23,
	const float m30,
	const float m31,
	const float m32,
	const float m33)
{
	matrix[0][0] = m00;
	matrix[0][1] = m01;
	matrix[0][2] = m02;
	matrix[0][3] = m03;
	matrix[1][0] = m10;
	matrix[1][1] = m11;
	matrix[1][2] = m12;
	matrix[1][3] = m13;
	matrix[2][0] = m20;
	matrix[2][1] = m21;
	matrix[2][2] = m22;
	matrix[2][3] = m23;
	matrix[3][0] = m30;
	matrix[3][1] = m31;
	matrix[3][2] = m32;
	matrix[3][3] = m33;
}

Matrix4::Matrix4(Matrix4& rhs)
{
	*this = rhs;
}

Matrix4::~Matrix4(){}

/*this static function returns a Vector3 representing the given index (zero based) row or column of the given matrix parameter depending
on the given MATRIX_MAJOR enum type.
(e.g.
Matrix4 MyVector(
1, 2, 3, 4,
5, 6, 7, 8,
9, 10, 11, 12,
13, 14, 15, 16);
Matrix4::GetVector4(ROW, 1, MyMatrix); returns a Vector4 representing the second row of MyMatrix => (5, 6, 7, 8)
Matrix4::GetVector4(COL, 0, MyMatrix); returns a Vector4 representing the first column of MyMatrix => (1, 5, 9, 13)
*/
Vector4 Matrix4::GetVector4(MATRIX_MAJOR type, int index, const Matrix4& matrix)
{
	float x, y, z, w;
	if (type == ROW)
	{
		x = matrix.matrix[index][0];
		y = matrix.matrix[index][1];
		z = matrix.matrix[index][2];
		w = matrix.matrix[index][3];
	}
	else
	{
		x = matrix.matrix[0][index];
		y = matrix.matrix[1][index];
		z = matrix.matrix[2][index];
		w = matrix.matrix[3][index];
	}
	return Vector4(x, y, z, w);
}

Matrix4& Matrix4::operator=(const Matrix4& rhs)
{
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			matrix[row][col] = rhs.matrix[row][col];
		}
	}
	return *this;
}

/*
Returns true if every element is equal to the element in the same position in the given matrix, else return false.
*/
bool Matrix4::operator==(const Matrix4& rhs)
{
	if (this == &rhs)
		return true;

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			if (matrix[row][col] != rhs.matrix[row][col])
				return false;
		}
	}
	return true;
}

bool Matrix4::operator!=(const Matrix4& rhs)
{
	return !(*this == rhs);
}

std::ostream& operator<<(std::ostream& out, const Matrix4& m)
{
	out << "Matrix4\n*********************\n";
	out << "** " << m.matrix[0][0] << "\t" << m.matrix[0][1] << "\t" << m.matrix[0][2] << "\t" << m.matrix[0][3] << "  **\n";
	out << "** " << m.matrix[1][0] << "\t" << m.matrix[1][1] << "\t" << m.matrix[1][2] << "\t" << m.matrix[1][3] << "  **\n";
	out << "** " << m.matrix[2][0] << "\t" << m.matrix[2][1] << "\t" << m.matrix[2][2] << "\t" << m.matrix[2][3] << "  **\n";
	out << "** " << m.matrix[3][0] << "\t" << m.matrix[3][1] << "\t" << m.matrix[3][2] << "\t" << m.matrix[3][3] << "  **\n";
	out << "*********************\n";
	return out;
}

Matrix4& Matrix4::operator+=(const Matrix4& rhs)
{
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			matrix[row][col] += rhs.matrix[row][col];
		}
	}
	return *this;
}

Matrix4& Matrix4::operator-=(const Matrix4& rhs)
{
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			matrix[row][col] -= rhs.matrix[row][col];
		}
	}
	return *this;
}

Matrix4& Matrix4::operator*=(const Matrix4& rhs)
{
	//need to use a temp because use the object during the process and can't modify during.
	Matrix4 result;
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			Vector4 rowVector = Matrix4::GetVector4(ROW, row, *this);
			Vector4 colVector = Matrix4::GetVector4(COL, col, rhs);
			result.matrix[row][col] = rowVector.DotProduct(colVector);
		}
	}
	return *this = result;
}