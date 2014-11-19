#ifndef _TEST_VECTOR_4_H_
#define _TEST_VECTOR_4_H_

/*
header file defines public API for Google test, needs to be included for any test program that uses it.
*/
#include "gtest/gtest.h"

//code under test
#include "TheMath.h"

TEST(vector4, constructorDefault)
{
	Vector4 v;
	EXPECT_FLOAT_EQ(0, v.x);
	EXPECT_FLOAT_EQ(0, v.y);
	EXPECT_FLOAT_EQ(0, v.z);
	EXPECT_FLOAT_EQ(0, v.w);
}

TEST(vector4, constructorFloats)
{
	Vector4 v(1.3f, 2.5f, -5.0f, -3.14159f);
	EXPECT_FLOAT_EQ(1.3f, v.x);
	EXPECT_FLOAT_EQ(2.5f, v.y);
	EXPECT_FLOAT_EQ(-5.0f, v.z);
	EXPECT_FLOAT_EQ(-3.14159f, v.w);
}

TEST(vector4, constructorCopy)
{
	Vector4 v(1, 2, 3, 4);
	Vector4 v2(v);
	EXPECT_FLOAT_EQ(1, v.x);
	EXPECT_FLOAT_EQ(2, v.y);
	EXPECT_FLOAT_EQ(3, v.z);
	EXPECT_FLOAT_EQ(4, v.w);

	//verify param still same
	EXPECT_TRUE(&v != &v2);
	EXPECT_TRUE(v == v2);
}

TEST(vector4, assignment)
{
	Vector4 v(1, 2, 3, 4);
	Vector4 v2(4, 3, 2, 1);

	v = v2 = v2;
	EXPECT_TRUE(v == v2);
	EXPECT_TRUE(v2 == Vector4(4, 3, 2, 1));
}

TEST(vector4, equality)
{
	Vector4 v1(1, 2, 3, 4);
	Vector4 v2(1, 2, 3, 4);
	Vector4 v3(1, 2, 3, 5);

	EXPECT_TRUE(v1 == v1);
	EXPECT_TRUE(v1 == v2);
	EXPECT_FALSE(v1 == v3);
}

TEST(vector4, inEquality)
{
	Vector4 v1(1, 2, 3, 4);
	Vector4 v2(1, 2, 3, 4);
	Vector4 v3(1, 2, 3, 5);

	EXPECT_FALSE(v1 != v1);
	EXPECT_FALSE(v1 != v2);
	EXPECT_TRUE(v1 != v3);
}

TEST(vector4, additionAssignment)
{
	Vector4 v1(1, 2, 3, 4);
	Vector4 v2(5, 4, 3, 2);
	v1 += v2;

	EXPECT_TRUE(Vector4(6, 6, 6, 6) == v1);
	EXPECT_TRUE(Vector4(5, 4, 3, 2) == v2);

	//verify chaining
	v1 = Vector4(1, 2, 3, 4);
	v1 += v2 += v2;

	EXPECT_TRUE(Vector4(11, 10, 9, 8) == v1) << v1;
	EXPECT_TRUE(Vector4(10, 8, 6, 4) == v2) << v2;
}

TEST(vector4, addition)
{
	Vector4 v1(1, 2, 3, 4);
	Vector4 v2(5, 4, 3, 2);
	v1 += v2;

	EXPECT_TRUE(Vector4(6, 6, 6, 6) == v1);
	EXPECT_TRUE(Vector4(5, 4, 3, 2) == v2);
}

TEST(vector4, subtractAssignment)
{
	Vector4 v1(10, 10, 10, 10);
	Vector4 v2(5, 5, 5, 5);
	v1 -= v2;

	EXPECT_TRUE(Vector4(5,5,5,5) == v1);
	EXPECT_TRUE(Vector4(5, 5,5,5) == v2);

	//verify chaining
	v1 = Vector4(10,10,10,10);
	v1 -= v2 -= v2;

	EXPECT_TRUE(Vector4(10,10,10,10) == v1) << v1;
	EXPECT_TRUE(Vector4(0,0,0,0) == v2) << v2;
}

TEST(vector4, negativeUnary)
{
	Vector4 v(1, 2, 3, 4);
	EXPECT_TRUE(Vector4(-1, -2, -3, -4) == -v) << v;
	EXPECT_TRUE(Vector4(1, 2, 3, 4) == v) << v;
}

TEST(vector4, bangOperator)
{
	Vector4 v(1, 2, 3, 4);
	Vector4 v2;

	EXPECT_FALSE(!v) << v;
	EXPECT_TRUE(!v2) << v;
}

TEST(vector4, multiplyOperator)
{
	Vector4 v1(10, 10, 10, 10);

	float scalar = 5.0f;
	Vector4 v2 = v1 * scalar;

	EXPECT_TRUE(v1 == Vector4(10, 10, 10, 10)) << "verify unchanged";
	EXPECT_FLOAT_EQ(5.0f, scalar) << "verify unchanged";
	EXPECT_TRUE(v2 == Vector4(50, 50, 50, 50)) << "verify product returned";
}

TEST(vector4, multiplyAssignmentOperator)
{
	Vector4 v1(5, 5, 5, 5);
	float scalar = 10.0f;
	v1 *= scalar;

	EXPECT_TRUE(v1 == Vector4(50, 50, 50, 50)) << "verify product applied";
	EXPECT_FLOAT_EQ(10.0f, scalar) << "verify unchanged";
}

TEST(vector4, bracketOperator)
{
	Vector4 v(1, 2, 3, 4);
	float r = v[2];

	EXPECT_FLOAT_EQ(3, r);
}

TEST(vector4, magnitude)
{
	Vector4 v1;
	//check zero

	EXPECT_FLOAT_EQ(0, v1.Magnitude());
	
	v1 = Vector4(1, 5, 8, 9);
	EXPECT_FLOAT_EQ(13.076696830622020656710945951579, v1.Magnitude()) << v1;
	EXPECT_TRUE(v1 == Vector4(1, 5, 8, 9));

}

TEST(vector4, normalize)
{
	Vector4 v(30, 40, 50, 60);
	v.Normalize();
	//magnitude = sqrt(5000)
	EXPECT_FLOAT_EQ(0.32349831961031524718080521188338, v.x);
	EXPECT_FLOAT_EQ(0.43133109281375366290774028251117, v.y);
	EXPECT_FLOAT_EQ(0.53916386601719207863467535313896, v.z);
	EXPECT_FLOAT_EQ(0.64699663922063049436161042376676, v.w);

	Vector4 v2;
	v2.Normalize();
	//divide by zero check
	EXPECT_TRUE(v2 == Vector4()) << v2;
}

#endif //_TEST_VECTOR_4_H_
