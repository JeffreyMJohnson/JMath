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

#endif //_TEST_VECTOR_4_H_
