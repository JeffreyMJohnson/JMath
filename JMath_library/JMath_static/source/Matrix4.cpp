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

/*
Returns identity matrix
e.g.
**********
1  0  0  0
0  1  0  0
0  0  1  0
0  0  0  1
**********
*/
Matrix4 Matrix4::Identity()
{
	Matrix4 m;
	m.matrix[0][0] = 1;
	m.matrix[0][1] = 0;
	m.matrix[0][2] = 0;
	m.matrix[0][3] = 0;

	m.matrix[1][0] = 0;
	m.matrix[1][1] = 1;
	m.matrix[1][2] = 0;
	m.matrix[1][3] = 0;

	m.matrix[2][0] = 0;
	m.matrix[2][1] = 0;
	m.matrix[2][2] = 1;
	m.matrix[2][3] = 0;

	m.matrix[3][0] = 0;
	m.matrix[3][1] = 0;
	m.matrix[3][2] = 0;
	m.matrix[3][3] = 1;

	return m;
}

/*
Returns 4X4 orthographic projection matrix
*/
Matrix4 Matrix4::OrthographicProjection()
{
	Matrix4 r = Matrix4::Identity();
	r.matrix[2][2] = 0;
	return r;
}

/*
returns new rotation matrix from given angle in radians around the given AXIS.   This assumes the use of a right-handed Cartesian coordinate system
therefore an angle value greater than 0 rotates counterclockwise, and an angle less than 0 rotates clockwise.
*/
Matrix4 Matrix4::SetupRotation(AXIS axis, float radians)
{
	Matrix4 r = Matrix4::Identity();
	switch (axis)
	{
	case X:
		r.matrix[1][1] = cos(radians);
		r.matrix[1][2] = -sin(radians);
		r.matrix[2][1] = sin(radians);
		r.matrix[2][2] = cos(radians);
		return r;
	case Y:
		r.matrix[0][0] = cos(radians);
		r.matrix[0][2] = sin(radians);
		r.matrix[2][0] = -sin(radians);
		r.matrix[2][2] = cos(radians);
		return r;
	case Z:
		r.matrix[0][0] = cos(radians);
		r.matrix[0][1] = -sin(radians);
		r.matrix[1][0] = sin(radians);
		r.matrix[1][1] = cos(radians);
		return r;
	}
}

/*
returns new rotation matrix consisting of products of rotation matrix of given angle around each
axis x,y and z.
*/
Matrix4 Matrix4::SetupRotation(float radians)
{
	Matrix4 result;
	result =
		Matrix4::SetupRotation(X, radians) *
		Matrix4::SetupRotation(Y, radians) *
		Matrix4::SetupRotation(Z, radians);
	return result;
}

/*
returns new rotation matrix from Vector3 of angles to rotate around each axis
*/
Matrix4 Matrix4::SetupRotation(const Vector3& angles)
{
	Matrix4 result;
	result =
		Matrix4::SetupRotation(X, angles.x) *
		Matrix4::SetupRotation(Y, angles.y) *
		Matrix4::SetupRotation(Z, angles.z);
	return result;
}

/*
returns new scale matrix
*/
Matrix4 Matrix4::SetupScale(const Vector3& scale)
{
	Matrix4 r = Matrix4::Identity();
	r.matrix[0][0] = scale.x;
	r.matrix[1][1] = scale.y;
	r.matrix[2][2] = scale.z;
	return r;
}

/*
return new translation matrix
*/
Matrix4 Matrix4::SetupTranslation(Vector3& translation)
{
	Matrix4 r = Matrix4::Identity();
	r.matrix[0][3] = translation.x;
	r.matrix[1][3] = translation.y;
	r.matrix[2][3] = translation.z;
	return r;
}

/*
Transforms the given Vector3 with this Matrix4 returning the Vector3 result.
NOTE:this converts the given Vector3 to a Vector4 with the w parameter set to one to
do the matrix math and then returns a Vector3 with the calculated x,y,z values.
*/
Vector3 Matrix4::Transform(const Vector3& v)
{
	Vector3 result;
	//create implicit Vector4 to do the math
	Vector4 r(v.x, v.y, v.z, 1);

	Vector4 row = Matrix4::GetVector4(ROW, 0, *this);
	result.x = row.DotProduct(r);
	row = Matrix4::GetVector4(ROW, 1, *this);
	result.y = row.DotProduct(r);
	row = Matrix4::GetVector4(ROW, 2, *this);
	result.z = row.DotProduct(r);
	//don't use the fourth row anyway so don't bother calculating
	return result;
}

/*
transposes this matrix
returns reference to this object to allow for operation chaining
*/
Matrix4& Matrix4::Transpose()
{
	Matrix4 m;
	for (int row = 0; row < 4; row++)
	{
		//get the row'th col from this Matrix
		Vector4 v = Matrix4::GetVector4(COL, row, *this);
		//set temp matrix row'th row to the vector's values
		m.matrix[row][0] = v.x;
		m.matrix[row][1] = v.y;
		m.matrix[row][2] = v.z;
		m.matrix[row][3] = v.w;
	}
	*this = m;
	//return reference to this so can chain operations
	return *this;

}

//returns a Matrix4 the transpose of this. This matrix does not change
Matrix4 Matrix4::GetTranspose()
{
	Matrix4 m;
	for (int row = 0; row < 4; row++)
	{
		//get the row'th col from this Matrix
		Vector4 v = Matrix4::GetVector4(COL, row, *this);
		//set temp matrix row'th row to the vector's values
		m.matrix[row][0] = v.x;
		m.matrix[row][1] = v.y;
		m.matrix[row][2] = v.z;
		m.matrix[row][3] = v.w;
	}

	return m;
}

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
bool operator==(const Matrix4& lhs, const Matrix4& rhs)
{
	if (&lhs == &rhs)
		return true;

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			if (lhs.matrix[row][col] != rhs.matrix[row][col])
				return false;
		}
	}
	return true;
}

bool operator!=(const Matrix4& lhs, const Matrix4& rhs)
{
	return !(lhs == rhs);
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

Matrix4 operator+(const Matrix4& lhs, const Matrix4& rhs)
{
	Matrix4 r;
	r = lhs;
	r += rhs;
	return r;
}

Matrix4 operator-(const Matrix4& lhs, const Matrix4& rhs)
{
	Matrix4 r;
	r = lhs;
	r -= rhs;
	return r;
}

Matrix4 operator*(const Matrix4& lhs, const Matrix4& rhs)
{
	Matrix4 r;
	r = lhs;
	r *= rhs;
	return r;
}

Vector4 operator*(const Matrix4& lhs, const Vector4& rhs)
{
	Vector4 result;
	Vector4 row = Matrix4::GetVector4(ROW, 0, lhs);
	result.x = row.DotProduct(rhs);
	row = Matrix4::GetVector4(ROW, 1, lhs);
	result.y = row.DotProduct(rhs);
	row = Matrix4::GetVector4(ROW, 2, lhs);
	result.z = row.DotProduct(rhs);
	row = Matrix4::GetVector4(ROW, 3, lhs);
	result.w = row.DotProduct(rhs);
	return result;
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
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			Vector4 rowVector = Matrix4::GetVector4(ROW, row, *this);
			Vector4 colVector = Matrix4::GetVector4(COL, col, rhs);
			result.matrix[row][col] = rowVector.DotProduct(colVector);
		}
	}
	return *this = result;
}

float* Matrix4::operator[](int index)
{
	return matrix[index];
}