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

Vector2 operator*(const Vector2& lhs, const float scalar)
{
	Vector2 r = lhs;
	r.x *= scalar;
	r.y *= scalar;
	return r;
}

Vector2 operator*(const float scalar, const Vector2& rhs)
{
	return rhs * scalar;
}

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

/*
Returns true if both x and y values of called Vector2 and given Vector2's are within delta of value else returns false.
(i.e. return abs(this.x - rhs.x) <= delta && abs(this.y - rhs.y) <= delta);
*/
bool Vector2::Equals(const Vector2& rhs, const float delta)
{
	return ((abs(this->x - rhs.x) <= delta) && (abs(this->y - rhs.y) <= delta));
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
Vector2 Vector2::GetLERP(const Vector2& end, const float percent)
{
	Vector2 start = *this;
	Vector2 norm = end - start;

	return (*this + (end - *this) * percent);
}

Vector2 Vector2::GetQuadBezier(Vector2& mid, Vector2& end, float percent)
{
	Vector2 mid1 = Vector2::LERP(*this, mid, percent);
	Vector2 mid2 = Vector2::LERP(mid, end, percent);

	return Vector2::LERP(mid1, mid2, percent);
}

/*
Returns new vector linear interpolated the given percent of the given vectors
i.e. (start + percent * (end - start))
*/
Vector2 Vector2::LERP(const Vector2& start, const Vector2& end, float percent)
{
	return (start + (end - start) * percent);
}

Vector2 Vector2::QuadBezier(const Vector2& a, const Vector2& b, const Vector2& c, float t)
{
	Vector2 mid1 = Vector2::LERP(a, b, t);
	Vector2 mid2 = Vector2::LERP(b, c, t);

	return Vector2::LERP(mid1, mid2, t);
}

Vector2 Vector2::CubicBezier(const Vector2& p0, const Vector2& p1, Vector2& p2, Vector2& p3, float t)
{
	Vector2 mid0 = Vector2::LERP(p0, p1, t);
	Vector2 mid1 = Vector2::LERP(p1, p2, t);
	Vector2 mid2 = Vector2::LERP(p2, p3, t);

	Vector2 mid3 = Vector2::LERP(mid0, mid1, t);
	Vector2 mid4 = Vector2::LERP(mid1, mid2, t);

	return Vector2::LERP(mid3, mid4, t);
}

Vector2 Vector2::HermiteSpline(const Vector2& point0, const Vector2& point1, const Vector2& tangent0, const Vector2& tangent1, const float t)
{
	float tsq = t * t;
	float tcub = tsq * t;

	float h00 = 2 * tcub - 3 * tsq + 1;
	float h01 = -2 * tcub + 3 * tsq;
	float h10 = tcub - 2 * tsq + t;
	float h11 = tcub - tsq;

	Vector2 r = h00 * point0 + h10 * tangent0 + h01 * point1 + h11 * tangent1;
	return r;
}
