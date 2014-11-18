#include "TheMath.h"

Vector4::Vector4()
{
	x = y = z = w = 0.0f;
}

Vector4::Vector4(const float a_x, const float a_y, const float a_z, const float a_w)
{
	x = a_x;
	y = a_y;
	z = a_z;
	w = a_w;
}

/*
construct and return Vector4 as a copy of given Vector4. Note given Vector4 is unchanged during operation.
*/
Vector4::Vector4(const Vector4& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
}

Vector4& Vector4::operator=(const Vector4& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	w = rhs.w;
	return *this;
}

bool Vector4::operator==(const Vector4& rhs)
{
	if (this == &rhs)
	{
		//same object
		return true;
	}
	if (x == rhs.x &&
		y == rhs.y &&
		z == rhs.z &&
		w == rhs.w)
	{
		return true;
	}
	return false;
}

bool Vector4::operator!=(const Vector4& rhs)
{
	return !(*this == rhs);
}