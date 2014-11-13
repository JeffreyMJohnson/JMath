#ifndef _TEST_VECTOR_2_H_
#define _TEST_VECTOR_2_H_

/*
header file defines public API for Google test, needs to be included for any test program that uses it.
*/
#include "gtest/gtest.h"

#include "..\..\JMath_static\include\TheMath.h"

TEST(vector2, constructorDefault)
{
	Vector2 v;
	EXPECT_FLOAT_EQ(0, v.x);
	EXPECT_FLOAT_EQ(0, v.y);
}

TEST(vector2, constructor)
{
	Vector2 v(1, 2);
	EXPECT_FLOAT_EQ(1, v.x);
	EXPECT_FLOAT_EQ(2, v.y);
}

//test equality operator so can use to verify future tests
TEST(vector2, equalityOperator)
{
	Vector2 v1(1, 2);
	Vector2 v2(3, 2);
	Vector2 v3(1, 2);

	EXPECT_TRUE(v1 == v1);
	EXPECT_TRUE(v1 == v3);
	EXPECT_FALSE(v1 == v2);

}

TEST(vector2, inEqualityOperator)
{
	Vector2 v1(1, 2);
	Vector2 v2(3, 2);
	Vector2 v3(1, 2);

	EXPECT_FALSE(v1 != v1);
	EXPECT_FALSE(v1 != v3);
	EXPECT_TRUE(v1 != v2);

}

TEST(vector2, assignmentOperator)
{
	Vector2 v1(5, 10);
	Vector2 v2 = v1;
	EXPECT_TRUE(v2 == v1);

	//change v1 and verify v2 did not change
	v1.x = 10;
	EXPECT_TRUE(v1 == Vector2(10, 10));
	EXPECT_TRUE(v2 == Vector2(5, 10));

	//verify chaining is possible a=b=c
	Vector2 v3 = v2 = v1;

	EXPECT_TRUE(v1 == Vector2(10, 10));
	EXPECT_TRUE(v2 == Vector2(10, 10));
	EXPECT_TRUE(v3 == Vector2(10, 10));
}

TEST(vector2, additionOperator)
{

	Vector2 v1(10, 10);
	Vector2 v2(5, 5);
	Vector2 v3 = v1 + v2;

	EXPECT_TRUE(v1 == Vector2(10, 10)) << "verify unchanged";
	EXPECT_TRUE(v2 == Vector2(5, 5)) << "verify unchanged";
	EXPECT_TRUE(v3 == Vector2(15, 15)) << "verify addition returned";

	//chaining
	v3 = v1 + v1 + v2;
	EXPECT_TRUE(v1 == Vector2(10, 10)) << "verify unchanged";
	EXPECT_TRUE(v2 == Vector2(5, 5)) << "verify unchanged";
	EXPECT_TRUE(v3 == Vector2(25,25)) << "verify addition returned";
}

TEST(vector2, additionAssignmentOperator)
{
	Vector2 v1(5, 5);
	Vector2 v2(10, 10);
	v1 += v2;

	EXPECT_TRUE(v1 == Vector2(15, 15)) << "verify addition applied";
	EXPECT_TRUE(v2 == Vector2(10, 10)) << "verify unchanged";

	//verify chaining is doable for crazy people
	(v2 += Vector2(1, 1)) += Vector2(4, 4);

	EXPECT_TRUE(v2 == Vector2(15, 15));
}

TEST(vector2, subtractOperator)
{

	Vector2 v1(10, 10);
	Vector2 v2(5, 5);
	Vector2 v3 = v1 - v2;

	EXPECT_TRUE(v1 == Vector2(10, 10)) << "verify unchanged";
	EXPECT_TRUE(v2 == Vector2(5, 5)) << "verify unchanged";
	EXPECT_TRUE(v3 == Vector2(5, 5)) << "verify subtract returned";

	//chaining
	v3 = v1 - v2 - v2;
	EXPECT_TRUE(v1 == Vector2(10, 10)) << v1 << "verify unchanged";
	EXPECT_TRUE(v2 == Vector2(5, 5)) << v2 << "verify unchanged";
	EXPECT_TRUE(v3 == Vector2(0,0)) << v3 << "verify subtract returned";

}

TEST(vector2, subtractAssignmentOperator)
{
	Vector2 v1(5, 5);
	Vector2 v2(10, 10);
	v1 -= v2;

	EXPECT_TRUE(v1 == Vector2(-5, -5)) << "verify subtract applied";
	EXPECT_TRUE(v2 == Vector2(10, 10)) << "verify unchanged";

	//chaining
	v1 = Vector2(5, 5);
	v1 -= v2 -= v2;
	EXPECT_TRUE(Vector2(5, 5) == v1) << v1;
	EXPECT_TRUE(Vector2() == v2) << v2;
}

TEST(vector2, multiplyOperator)
{

	Vector2 v1(10, 10);

	float scalar = 5.0f;
	Vector2 v2 = v1 * scalar;

	EXPECT_TRUE(v1 == Vector2(10, 10)) << "verify unchanged";
	EXPECT_FLOAT_EQ(5.0f, scalar) << "verify unchanged";
	EXPECT_TRUE(v2 == Vector2(50, 50)) << "verify product returned";
}

TEST(vector2, multiplyAssignmentOperator)
{
	Vector2 v1(5, 5);
	float scalar = 10.0f;
	v1 *= scalar;

	EXPECT_TRUE(v1 == Vector2(50, 50)) << "verify product applied";
}

TEST(vector2, magnitude)
{
	Vector2 v1(3, 4);
	EXPECT_FLOAT_EQ(5.0f, v1.Magnitude());
	EXPECT_TRUE(v1 == Vector2(3, 4)) << "verify unchanged";

	v1 *= 3;
	EXPECT_EQ(15.0f, v1.Magnitude());
}

TEST(vector2, normalize)
{
	Vector2 v(30, 40);
	v.Normalize();
	EXPECT_FLOAT_EQ(.6, v.x);
	EXPECT_FLOAT_EQ(.8, v.y);

	//divide by zero check
	v = Vector2();
	v.Normalize();
	EXPECT_TRUE(Vector2() == v) << v;
}

TEST(vector2, getNormal)
{
	Vector2 v(30, 40);
	Vector2 v2 = v.GetNormal();

	EXPECT_FLOAT_EQ(.6, v2.x);
	EXPECT_FLOAT_EQ(.8, v2.y);
	EXPECT_TRUE(v == Vector2(30, 40));

	//divide by zero check
	v = Vector2();
	v2 = v.GetNormal() = Vector2();
	EXPECT_TRUE(Vector2() == v2) << v2;
}

TEST(vector2, dotProduct)
{
	Vector2 v1(5, 2);
	Vector2 v2(-10, 4);
	EXPECT_FLOAT_EQ(-42, v1.DotProduct(v2));
	EXPECT_TRUE(v1 == Vector2(5, 2));
	EXPECT_TRUE(v2 == Vector2(-10, 4));
}

TEST(vector2, getPerp)
{
	Vector2 v(10, 100);
	Vector2 perp = v.GetPerp();

	EXPECT_TRUE(v == Vector2(10, 100));
	EXPECT_TRUE(perp == Vector2(100, -10));

	v = Vector2(4, 6);
	perp = v.GetPerp();
	EXPECT_TRUE(v == Vector2(4, 6));
	EXPECT_TRUE(perp == Vector2(6, -4));

}

TEST(vector2, getLERP)
{
	float percent = 0;
	Vector2 start(0, 0);
	Vector2 end(5, 5);
	Vector2 result = start.GetLERP(end, percent);

	EXPECT_TRUE(start == result);
	percent = 1;
	result = start.GetLERP(end, percent);
	EXPECT_TRUE(end == result);
	percent = .5;
	result = start.GetLERP(end, percent);
	EXPECT_TRUE(Vector2(2.5, 2.5) == result);

}

TEST(vector2, lerp_static)
{
	float percent = 0;
	Vector2 start(0, 0);
	Vector2 end(5, 5);
	Vector2 result = Vector2::LERP(start, end, percent);

	EXPECT_TRUE(start == result) << "result " << result;
	percent = 1;

	result = Vector2::LERP(start, end, percent);
	EXPECT_TRUE(end == result) << "result " << result;

	percent = .5;
	result = Vector2::LERP(start, end, percent);
	EXPECT_TRUE(Vector2(2.5, 2.5) == result) << "result " << result;
}


#endif