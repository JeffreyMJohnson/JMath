#ifndef _TEST_VECTOR_3_H_
#define _TEST_VECTOR_3_H_

/*
header file defines public API for Google test, needs to be included for any test program that uses it.
*/
#include "gtest/gtest.h"

#include "..\..\JMath_static\include\TheMath.h"

TEST(vector3, constructorDefault)
{
	Vector3 v;
	EXPECT_FLOAT_EQ(0, v.x);
	EXPECT_FLOAT_EQ(0, v.y);
	EXPECT_FLOAT_EQ(0, v.z);
}

TEST(vector3, constructor)
{
	Vector3 v(1, 2, 3);
	EXPECT_FLOAT_EQ(1, v.x);
	EXPECT_FLOAT_EQ(2, v.y);
	EXPECT_FLOAT_EQ(3, v.z);
}

TEST(vector3, getVector3FromMatrix)
{
	Matrix3 mRow(
		0, 1, 2,
		3, 4, 5,
		6, 7, 8);

	Matrix3 mCol(
		0, 3, 6,
		1, 4, 7,
		2, 5, 8);

	MATRIX_MAJOR majorType = ROW;

	Vector3 result = Matrix3::GetVector3(majorType, 0, mRow);
	EXPECT_TRUE(result == Vector3(0, 1, 2));

	result = Matrix3::GetVector3(majorType, 1, mRow);
	EXPECT_TRUE(result == Vector3(3, 4, 5));

	result = Matrix3::GetVector3(majorType, 2, mRow);
	EXPECT_TRUE(result == Vector3(6, 7, 8));

	majorType = COL;
	result = Matrix3::GetVector3(majorType, 0, mCol);
	EXPECT_TRUE(result == Vector3(0, 1, 2));

	result = Matrix3::GetVector3(majorType, 1, mCol);
	EXPECT_TRUE(result == Vector3(3, 4, 5));

	result = Matrix3::GetVector3(majorType, 2, mCol);
	EXPECT_TRUE(result == Vector3(6, 7, 8));


}

//test equality operator so can use to verify future tests
TEST(vector3, equalityOperator)
{
	Vector3 v1(1, 2, 3);
	Vector3 v2(3, 2, 1);
	Vector3 v3(1, 2, 3);

	EXPECT_TRUE(v1 == v1);
	EXPECT_TRUE(v1 == v3);
	EXPECT_FALSE(v1 == v2);

}

TEST(vector3, inEqualityOperator)
{
	Vector3 v1(1, 2, 3);
	Vector3 v2(3, 2, 1);
	Vector3 v3(1, 2, 3);

	EXPECT_FALSE(v1 != v1);
	EXPECT_FALSE(v1 != v3);
	EXPECT_TRUE(v1 != v2);

}

TEST(vector3, assignmentOperator)
{
	Vector3 v1(5, 10, 15);
	Vector3 v2 = v1;
	EXPECT_TRUE(v2 == v1);

	//change v1 and verify v2 did not change
	v1.x = 10;
	EXPECT_TRUE(v1 == Vector3(10, 10, 15));
	EXPECT_TRUE(v2 == Vector3(5, 10, 15));

	//chaining
	v1 = v2 = Vector3();
	EXPECT_TRUE(Vector3() == v1) << v1;
	EXPECT_TRUE(Vector3() == v2) << v2;
}

TEST(vector3, additionOperator)
{

	Vector3 v1(10, 10, 10);
	Vector3 v2(5, 5, 5);
	Vector3 v3 = v1 + v2;

	EXPECT_TRUE(v1 == Vector3(10, 10, 10)) << "verify unchanged";
	EXPECT_TRUE(v2 == Vector3(5, 5, 5)) << "verify unchanged";
	EXPECT_TRUE(v3 == Vector3(15, 15, 15)) << "verify addition returned";

	//verify chaining
	v3 = v1 + v2 + v3;
	EXPECT_TRUE(v3 == Vector3(30, 30, 30));
	EXPECT_TRUE(v1 == Vector3(10, 10, 10)) << "verify unchanged";
	EXPECT_TRUE(v2 == Vector3(5, 5, 5)) << "verify unchanged";
}

TEST(vector3, additionAssignmentOperator)
{
	Vector3 v1(5, 5, 5);
	Vector3 v2(10, 10, 10);
	v1 += v2;

	EXPECT_TRUE(v1 == Vector3(15, 15, 15)) << "verify addition applied";
	EXPECT_TRUE(v2 == Vector3(10, 10, 10)) << "verify unchanged";

	//chaining
	v1 += v2 += Vector3(-10, -10, -10);
	EXPECT_TRUE(Vector3(15, 15, 15) == v1) << v1;
	EXPECT_TRUE(Vector3() == v2) << v2;
}

TEST(vector3, subtractOperator)
{

	Vector3 v1(10, 10, 10);
	Vector3 v2(5, 5, 5);
	Vector3 v3 = v1 - v2;

	EXPECT_TRUE(v1 == Vector3(10, 10, 10)) << v1 << "verify unchanged";
	EXPECT_TRUE(v2 == Vector3(5, 5, 5)) << v2 << "verify unchanged";
	EXPECT_TRUE(v3 == Vector3(5, 5, 5)) << v3 << "verify subtract returned";

	//chaining 
	v3 = v1 - v2 - v2;
	EXPECT_TRUE(v1 == Vector3(10, 10, 10)) << v1 << "verify unchanged";
	EXPECT_TRUE(v2 == Vector3(5, 5, 5)) << v2 << "verify unchanged";
	EXPECT_TRUE(v3 == Vector3(0,0,0)) << v3 << "verify subtract returned";

}

TEST(vector3, subtractAssignmentOperator)
{
	Vector3 v1(5, 5, 5);
	Vector3 v2(10, 10, 10);
	v1 -= v2;

	EXPECT_TRUE(v1 == Vector3(-5, -5, -5)) << "verify subtract applied";
	EXPECT_TRUE(v2 == Vector3(10, 10, 10)) << "verify unchanged";

	//chaining
	v1 -= v2 -= Vector3(10, 10, 10);
	EXPECT_TRUE(Vector3(-5, -5, -5) == v1) << v1;
	EXPECT_TRUE(Vector3() == v2) << v2;
}

TEST(vector3, multiplyOperator)
{

	Vector3 v1(10, 10, 10);

	float scalar = 5.0f;
	Vector3 v2 = v1 * scalar;

	EXPECT_TRUE(v1 == Vector3(10, 10, 10)) << "verify unchanged";
	EXPECT_FLOAT_EQ(5.0f, scalar) << "verify unchanged";
	EXPECT_TRUE(v2 == Vector3(50, 50, 50)) << "verify product returned";
}

TEST(vector3, multiplyAssignmentOperator)
{
	Vector3 v1(5, 5, 5);
	float scalar = 10.0f;
	v1 *= scalar;

	EXPECT_TRUE(v1 == Vector3(50, 50, 50)) << "verify product applied";
	EXPECT_FLOAT_EQ(10.0f, scalar) << "verify unchanged";
}

TEST(vector3, bracketOperator)
{
	Vector3 v(1, 2, 3);
	float r = v[1];
	EXPECT_FLOAT_EQ(2, r);
}

TEST(vector3, negativeUnary)
{
	Vector3 v(1, 2, 3);

	EXPECT_TRUE(Vector3(-1, -2, -3) == -v) << v;
	EXPECT_TRUE(Vector3(1, 2, 3) == v) << v;
}

TEST(vector3, bangOperator)
{
	Vector3 v(1, 2, 3);
	Vector3 v2;

	EXPECT_FALSE(!v) << v;
	EXPECT_TRUE(!v2) << v;
}

TEST(vector3, magnitude)
{
	Vector3 v1(3, 4, 5);
	//expect sqrt(50)
	EXPECT_FLOAT_EQ(7.0710678118654752440084436210485, v1.Magnitude());
	EXPECT_TRUE(v1 == Vector3(3, 4, 5)) << "verify unchanged";

	v1 *= 3;
	EXPECT_EQ(sqrtf(450), v1.Magnitude());
}

TEST(vector3, normalize)
{
	Vector3 v(30, 40, 50);
	v.Normalize();
	//magnitude = sqrt(5000)
	EXPECT_FLOAT_EQ(0.42426406871192851464050661726291, v.x);
	EXPECT_FLOAT_EQ(0.56568542494923801952067548968388, v.y);
	EXPECT_FLOAT_EQ(0.70710678118654752440084436210485, v.z);

	Vector3 v2;
	v2.Normalize();
	//divide by zero check
	EXPECT_TRUE(v2 == Vector3()) << v2;
}

TEST(vector3, getNormal)
{
	Vector3 v(30, 40, 50);
	Vector3 v2 = v.GetNormal();

	//magnitude = sqrt(5000)
	EXPECT_FLOAT_EQ(0.42426406871192851464050661726291, v2.x);
	EXPECT_FLOAT_EQ(0.56568542494923801952067548968388, v2.y);
	EXPECT_FLOAT_EQ(0.70710678118654752440084436210485, v2.z);
	EXPECT_TRUE(v == Vector3(30, 40, 50)) << "verify unchanged";

	//divide by zero check
	v = Vector3();
	v2 = v.GetNormal() = Vector3();
	EXPECT_TRUE(Vector3() == v2) << v2;
}

TEST(vector3, dotProduct)
{
	Vector3 v1(5, 2, 15);
	Vector3 v2(-10, 4, -100);
	EXPECT_FLOAT_EQ(-1542, v1.DotProduct(v2));
	EXPECT_TRUE(v1 == Vector3(5, 2, 15));
	EXPECT_TRUE(v2 == Vector3(-10, 4, -100));
}

TEST(vector3, crossProduct)
{
	Vector3 v1(3, 4, 5);
	Vector3 v2(6, 7, 8);

	Vector3 xProd = v1.CrossProduct(v2);

	EXPECT_TRUE(xProd == Vector3(-3, 6, -3));

	v1 = Vector3(10, 0, 0);
	v2 = Vector3(0, 10, 0);
	xProd = v1.CrossProduct(v2);

	EXPECT_TRUE(xProd == Vector3(0, 0, 100));
}

TEST(vector3, getLERP)
{
	float percent = 0;
	Vector3 start(0, 0, 0);
	Vector3 end(5, 5, 5);
	Vector3 result = start.GetLERP(end, percent);

	EXPECT_TRUE(start == result);
	percent = 1;
	result = start.GetLERP(end, percent);
	EXPECT_TRUE(end == result);
	percent = .5;
	result = start.GetLERP(end, percent);
	EXPECT_TRUE(Vector3(2.5, 2.5, 2.5) == result);
}

TEST(vector3, lerp_static)
{
	float percent = 0;
	Vector3 start(0, 0, 0);
	Vector3 end(5, 5, 5);
	Vector3 result = Vector3::LERP(start, end, percent);

	EXPECT_TRUE(start == result);
	percent = 1;
	result = Vector3::LERP(start, end, percent);
	EXPECT_TRUE(end == result);
	percent = .5;
	result = Vector3::LERP(start, end, percent);
	EXPECT_TRUE(Vector3(2.5, 2.5, 2.5) == result);
}
#endif