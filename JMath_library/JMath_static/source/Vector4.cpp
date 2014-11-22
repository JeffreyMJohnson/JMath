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
construct and return a Vector4 from given hex number with values x for the red value, y for the
green value, z for the blue value and W for the alpha value.  The values will be from 0 to 255.
assume hex number is from 0x00000000 to 0xFFFFFFFF
*/
Vector4::Vector4(const unsigned int a_hex)
{
	unsigned int mask = 0x000000FF;
	unsigned int color = a_hex;

	//least significant 8 bits is the element
	w = color & mask;
	color = color >> 8;
	z = color & mask;
	color = color >> 8;
	y = color & mask;
	color = color >> 8;
	x = color & mask;
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

/*
construct and return a Vector4 from given hex number with values x for the red value, y for the
green value, z for the blue value and W for the alpha value.  The values will be from 0 to 255.
assume hex number is from 0x00000000 to 0xFFFFFFFF
*/
Vector4 Vector4::ConstructFromHex(const unsigned int a_hex)
{
	Vector4 result;
	unsigned int mask = 0x000000FF;
	unsigned int color = a_hex;

	//least significant 8 bits is the element
	result.w = color & mask;
	color = color >> 8;
	result.z = color & mask;
	color = color >> 8;
	result.y = color & mask;
	color = color >> 8;
	result.x = color & mask;
	return result;
}

Vector4& Vector4::operator=(const Vector4& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	w = rhs.w;
	return *this;
}

Vector4& Vector4::operator+= (const Vector4& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	w += rhs.w;
	return *this;
}

Vector4 Vector4::operator+(const Vector4& rhs)
{
	Vector4 v = *this;
	v += rhs;
	return v;
}

Vector4& Vector4::operator-=(const Vector4& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	w -= rhs.w;
	return *this;
}

Vector4 Vector4::operator-(const Vector4& rhs)
{
	Vector4 v = *this;
	v -= rhs;
	return v;
}

Vector4 Vector4::operator-()
{
	Vector4 v(*this);
	v *= -1;
	return v;
}

/*
returns ths value of element pointed by given index.
i.e. myVector4[0] returns myVector.x, myVector[0] returns myVector.y etc.
EXPECT: given value must be -1 < index < 4
*/
float Vector4::operator[](const int index)
{
	switch (index)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	case 3:
		return w;
	}
}

/* 
returns true if Vector not zero (Vector4 (0,0,0,0)) else returns false;
*/
bool Vector4::operator!()
{
	return *this == Vector4();
}

Vector4 Vector4::operator*(const float scalar)
{
	return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
}

void Vector4::operator*=(const float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;
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
		return true;}
	return false;
}

bool operator==(const Vector4& lhs, const Vector4& rhs)
{
	if (&lhs == &rhs)
		return true;
	if (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w)
		return true;
	return false;
}

bool Vector4::operator!=(const Vector4& rhs)
{
	return !(*this == rhs);
}

bool operator!=(const Vector4& lhs, const Vector4& rhs)
{
	if (&lhs == &rhs)
		return false;
	if (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w)
		return false;
	return true;
}

/*
returns the magnitude of this Vector4
*/
float Vector4::Magnitude()
{
	return sqrt((x * x) + (y * y) + (z * z) + (w * w));
}

/*
returns true if this Vector4 able to be normalized, and will normalize this object else returns false and leaves this unchanged (i.e. magnitude of this vector
is zero)
*/
bool Vector4::Normalize()
{
	float magnitude = Magnitude();
	//divide by zero check
	if (magnitude)
	{
		//multiply by inverse, performance refactor
		*this *= 1 / magnitude;
		return true;
	}
	return false;
}

/*
return a new Vector4 of this Vectr4 normalized
*/
Vector4 Vector4::GetNormalized()
{
	Vector4 v = *this;
	v.Normalize();
	return v;
}

/*
return dot product of this vector and given other vector
*/
float Vector4::DotProduct(const Vector4& other)
{
	return (x * other.x) + (y * other.y) + (z * other.z) + (w * other.w);
}

std::ostream& operator<<(std::ostream& out, const Vector4& rhs)
{
	out << "Vector4 [x:";
	out << rhs.x << ", y:";
	out << rhs.y << ", z:";
	out << rhs.z << ", w:";
	out << rhs.w << "]";
	return out;
}

