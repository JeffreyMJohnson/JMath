#include "TheMath.h"

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(float a_x, float a_y)
{
	x = a_x;
	y = a_y;
}

Vector2::Vector2(const Vector2& other)
{
	x = other.x;
	y = other.y;
}

Vector2::~Vector2()
{
}

Vector2& Vector2::operator=(const Vector2& rhs)
{
	//check for self assignment
	if (this != &rhs)
	{
		x = rhs.x;
		y = rhs.y;
	}
	return *this;

}

Vector2 Vector2::operator+(const Vector2& other)
{
	return Vector2(x + other.x, y + other.y);
}

Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
{
	return (Vector2(lhs.x + rhs.x, lhs.y + rhs.y));
}

Vector2& Vector2::operator+=(const Vector2& rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Vector2 Vector2::operator-(const Vector2& other)
{
	return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator-()
{
	Vector2 v(*this);
	v *= -1;
	return v;
}

/*
returns true if Vector not zero (Vector2 (0,0)) else returns false;
*/
bool Vector2::operator!()
{
	return *this == Vector2();
}

Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
}

Vector2& Vector2::operator-=(const Vector2& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

Vector2 Vector2::operator*(const float scalar)
{
	return Vector2(x * scalar, y * scalar);
}

//Vector2 operator*(const float scalar, const Vector2& vector)
//{
//	return scalar * vector;
//}

void Vector2::operator*=(const float scalar)
{
	x *= scalar;
	y *= scalar;
}

/*
returns true if given other Vector2 is either the same object as this or x and y are equal, else returns false
*/
bool Vector2::operator==(const Vector2& other)
{
	if (this == &other)
		return true;
	if (x == other.x && y == other.y)
		return true;
	return false;
}

/*
returns true if given other Vector2 is either the same object as this or x and y are equal, else returns false
*/
bool operator==(const Vector2& lhs, const Vector2& rhs)
{
	if (&lhs == &rhs)
		return true;
if (lhs.x == rhs.x && lhs.y == rhs.y)
		return true;
	return false;
}

/*
returns false if given other Vector2 is either the same object as this or x and y are equal, else returns true
*/
bool Vector2::operator!=(const Vector2& other)
{
	return !(*this == other);
}

bool operator!=(const Vector2& lhs, const Vector2& rhs)
{
	if (&lhs == &rhs)
		return false;
	if (lhs.x == rhs.x && lhs.y == rhs.y)
		return false;
	return true;
}



std::ostream& operator<<(std::ostream& out, const Vector2& v)
{
	out << "Vector2 [x: " << v.x << " y: " << v.y << "]";
	return out;
}

//vector math functions
/*
returns magnitude of this vector
*/
float Vector2::Magnitude()
{
	return sqrt((x * x) + (y * y));
}

/*
normalize this Vector2
*/
void Vector2::Normalize()
{
	float magnitude = Magnitude();
	//check if divide by zero
	if (magnitude)
	{
		//multiply by inverse for perf refactor
		*this *= 1 / magnitude;
	}
}

/*
return normalized Vector2 from values of this one. This vector is not changed.
*/
Vector2 Vector2::GetNormal()
{
	Vector2 v = *this;
	v.Normalize();
	return v;
}

/*
return dot product of this vector and given other vector
*/
float Vector2::DotProduct(const Vector2& other)
{
	return (x * other.x) + (y * other.y);
}

//return Vector2 perpendicular to this one
Vector2 Vector2::GetPerp()
{
	return Vector2(this->y, -this->x);
}

/*
Returns new vector linear interpolated the given percent of the given vectors
i.e. (start + percent * (end - start))
*/
Vector2 Vector2::GetLERP(const Vector2& end, float const percent)
{
	Vector2 start = *this;
	Vector2 norm = end - start;

	return (*this + (end - *this) * percent);
}

/*
Returns new vector linear interpolated the given percent of the given vectors
i.e. (start + percent * (end - start))
*/
Vector2 Vector2::LERP(const Vector2& start, const Vector2& end, float percent)
{
	return (start + (end - start) * percent);
}
