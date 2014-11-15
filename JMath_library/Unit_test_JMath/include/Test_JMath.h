#ifndef _TEST_UTILITY_H_
#define _TEST_UTILITY_H_

/*
header file defines public API for Google test, needs to be included for any test program that uses it.
*/
#include "gtest/gtest.h"

//code under test
#include "..\..\JMath_static\include\TheMath.h"

TEST(jmath, DegToRad)
{
	//45 degrees .7853975 rads
	EXPECT_NEAR(.7853975, JMath::DegreeToRadians(45), .001);

}

TEST(jmath, radToDeg)
{
	//45 degrees .7853975 rads
	EXPECT_NEAR(45.0f, JMath::RadiansToDegrees(.7853975), .001);

}

TEST(jmath, staticLerp)
{
	float start = 0;
	float end = 10;

	float r = JMath::LERP(start, end, 0);
	EXPECT_FLOAT_EQ(0, r);

	r = JMath::LERP(start, end, 1);
	EXPECT_FLOAT_EQ(10, r);

	r = JMath::LERP(start, end, .5);
	EXPECT_FLOAT_EQ(5, r);

}

TEST(jmath, isPowOfTwo)
{
	unsigned int i = 10;
	EXPECT_FALSE(JMath::IsPowerOfTwo(i));
	
	i = 128;
	EXPECT_TRUE(JMath::IsPowerOfTwo(i));

	i = 0;
	EXPECT_FALSE(JMath::IsPowerOfTwo(i));

	i = 1;
	EXPECT_TRUE(JMath::IsPowerOfTwo(i));

	i = 127;
	EXPECT_FALSE(JMath::IsPowerOfTwo(i));
}

#endif