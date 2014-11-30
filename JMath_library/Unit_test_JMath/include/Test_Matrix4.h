#ifndef _TEST_MATRIX_4_H_
#define _TEST_MATRIX_4_H_
/*
header file defines public API for Google test, needs to be included for any test program that uses it.
*/
#include "gtest/gtest.h"

#include "..\..\JMath_static\include\TheMath.h"

TEST(matrix4, constructorDefault)
{
	Matrix4 m;

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			EXPECT_FLOAT_EQ(0, m.matrix[row][col]);
		}
	}
}

TEST(matrix4, constructor)
{
	Matrix4 m(
		10, 11, 12, 13,
		20, 21, 22, 23,
		30, 31, 32, 33,
		40, 41, 42, 43);

	EXPECT_FLOAT_EQ(10, m.matrix[0][0]);
	EXPECT_FLOAT_EQ(11, m.matrix[0][1]);
	EXPECT_FLOAT_EQ(12, m.matrix[0][2]);
	EXPECT_FLOAT_EQ(13, m.matrix[0][3]);
	EXPECT_FLOAT_EQ(20, m.matrix[1][0]);
	EXPECT_FLOAT_EQ(21, m.matrix[1][1]);
	EXPECT_FLOAT_EQ(22, m.matrix[1][2]);
	EXPECT_FLOAT_EQ(23, m.matrix[1][3]);
	EXPECT_FLOAT_EQ(30, m.matrix[2][0]);
	EXPECT_FLOAT_EQ(31, m.matrix[2][1]);
	EXPECT_FLOAT_EQ(32, m.matrix[2][2]);
	EXPECT_FLOAT_EQ(33, m.matrix[2][3]);
	EXPECT_FLOAT_EQ(40, m.matrix[3][0]);
	EXPECT_FLOAT_EQ(41, m.matrix[3][1]);
	EXPECT_FLOAT_EQ(42, m.matrix[3][2]);
	EXPECT_FLOAT_EQ(43, m.matrix[3][3]);

}

TEST(matrix4, copyConstructor)
{
	Matrix4 m(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16);

	Matrix4 m2(m);

	EXPECT_TRUE(m2 == m);
	//verify copy not same object
	EXPECT_FALSE(&m2 == &m) << "expect: " << &m2 << "result: " << &m;
}

TEST(matrix4, get)
{
	Matrix4 m(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16);

	float m2[16]{
			1, 5, 9, 13,
			2, 6, 10, 14,
			3, 7, 11, 15,
			4, 8, 12, 16
	};

	float m3[16];
	m.Get(m3);

	for (int i = 0; i < 16; i++)
	{
		EXPECT_FLOAT_EQ(m2[i], m3[i]);
	}


}

TEST(matrix4, equality)
{
	Matrix4 m1(
		2, 3, 4, 5,
		2, 3, 4, 5,
		2, 3, 4, 5,
		2, 3, 4, 5);

	Matrix4 m2(
		2, 3, 4, 5,
		2, 3, 4, 5,
		2, 3, 4, 5,
		2, 3, 4, 5);

	Matrix4 m3(
		2, 3, 4, 5,
		2, 3, 4, 5,
		2, 3, 4, 5,
		2, 3, 4, 0);

	EXPECT_TRUE(m1 == m2);
	EXPECT_TRUE(m1 == m1);
	EXPECT_FALSE(m1 == m3);

}

TEST(matrix4, inEquality)
{
	Matrix4 m1(
		2, 3, 4, 5,
		2, 3, 4, 5,
		2, 3, 4, 5,
		2, 3, 4, 5);

	Matrix4 m2(
		2, 3, 4, 5,
		2, 3, 4, 5,
		2, 3, 4, 5,
		2, 3, 4, 5);

	Matrix4 m3(
		2, 3, 4, 5,
		2, 3, 4, 5,
		2, 3, 4, 5,
		2, 3, 4, 0);

	EXPECT_TRUE(m1 != m3);
	EXPECT_TRUE(m2 != m3);
	EXPECT_FALSE(m1 != m2);

}

TEST(matrix4, assignmentOperator)
{
	Matrix4 m1(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16);
	Matrix4 m2;
	Matrix4 m3;
	m3 = m2 = m1;

	EXPECT_TRUE(m1 == m2);
	EXPECT_TRUE(m1 == m3);
	EXPECT_FALSE(&m1 == &m2);

}

TEST(matrix4, additionAssignemntOperator)
{
	Matrix4 m1(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16);
	Matrix4 m2(
		16, 15, 14, 13,
		12, 11, 10, 9,
		8, 7, 6, 5,
		4, 3, 2, 1);
	Matrix4 expect(
		17, 17, 17, 17,
		17, 17, 17, 17,
		17, 17, 17, 17,
		17, 17, 17, 17);
	EXPECT_TRUE(expect == (m1 += m2));
	EXPECT_TRUE(m2 ==
		Matrix4(
		16, 15, 14, 13,
		12, 11, 10, 9,
		8, 7, 6, 5,
		4, 3, 2, 1));
}

TEST(matrix4, subtractAssignemntOperator)
{
	Matrix4 m1(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16);
	Matrix4 m2(
		16, 15, 14, 13,
		12, 11, 10, 9,
		8, 7, 6, 5,
		4, 3, 2, 1);
	Matrix4 expect(
		-15, -13, -11, -9,
		-7, -5, -3, -1,
		1, 3, 5, 7,
		9, 11, 13, 15);
	EXPECT_TRUE(expect == (m1 -= m2));
	EXPECT_TRUE(m2 ==
		Matrix4(
		16, 15, 14, 13,
		12, 11, 10, 9,
		8, 7, 6, 5,
		4, 3, 2, 1));
}

TEST(matrix4, getVector4FromMatrix)
{
	Matrix4 mRow(
		0, 1, 2, 3,
		4, 5, 6, 7,
		8, 9, 10, 11,
		12, 13, 14, 15);

	Matrix4 mCol(
		0, 4, 8, 12,
		1, 5, 9, 13,
		2, 6, 10, 14,
		3, 7, 11, 15);

	MATRIX_MAJOR majorType = ROW;

	Vector4 result = Matrix4::GetVector4(majorType, 0, mRow);
	EXPECT_TRUE(result == Vector4(0, 1, 2, 3));

	result = Matrix4::GetVector4(majorType, 1, mRow);
	EXPECT_TRUE(result == Vector4(4, 5, 6, 7));

	result = Matrix4::GetVector4(majorType, 2, mRow);
	EXPECT_TRUE(result == Vector4(8, 9, 10, 11));

	majorType = COL;
	result = Matrix4::GetVector4(majorType, 0, mCol);
	EXPECT_TRUE(result == Vector4(0, 1, 2, 3));

	result = Matrix4::GetVector4(majorType, 1, mCol);
	EXPECT_TRUE(result == Vector4(4, 5, 6, 7));

	result = Matrix4::GetVector4(majorType, 2, mCol);
	EXPECT_TRUE(result == Vector4(8, 9, 10, 11));


}

TEST(matrix4, productAssignemntOperator)
{

	Matrix4 m1(
		0, 1, 2, 0,
		4, 5, 6, 0,
		8, 9, 10, 0,
		0, 0, 0, 1);
	Matrix4 m2(
		0, 1, 2, 0,
		4, 5, 6, 0,
		8, 9, 10, 0,
		0, 0, 0, 1);
	m1 *= m2;
	Matrix4 expect(
		20, 23, 26, 0,
		68, 83, 98, 0,
		116, 143, 170, 0,
		0, 0, 0, 1);

	//EXPECT_FLOAT_EQ(15, m1.matrix[0][0]);
	//EXPECT_FLOAT_EQ(18, m1.matrix[0][1]);
	//EXPECT_FLOAT_EQ(21, m1.matrix[0][2]);
	//EXPECT_FLOAT_EQ(42, m1.matrix[1][0]);
	//EXPECT_FLOAT_EQ(54, m1.matrix[1][1]);
	//EXPECT_FLOAT_EQ(66, m1.matrix[1][2]);
	//EXPECT_FLOAT_EQ(69, m1.matrix[2][0]);
	//EXPECT_FLOAT_EQ(90, m1.matrix[2][1]);
	//EXPECT_FLOAT_EQ(111, m1.matrix[2][2]);

	EXPECT_EQ(expect, m1);
	EXPECT_EQ(Matrix4(
		0, 1, 2, 0,
		4, 5, 6, 0,
		8, 9, 10, 0,
		0, 0, 0, 1), m2);

	m1 = Matrix4(
		320, -8, 58, 0,
		45, 26, -369, 0,
		65, 14, -65, 0,
		0, 0, 0, 1);

	m2 = Matrix4(
		12, -25, -98, 0,
		45, 369, 7, 0,
		98, -5, 180, 0,
		0, 0, 0, 1);
	m1 *= m2;
	expect = Matrix4(
		9164, -11242, -20976, 0,
		-34452, 10314, -70648, 0,
		-4960, 3866, -17972, 0,
		0, 0, 0, 1);

	EXPECT_EQ(expect, m1);
	EXPECT_EQ(Matrix4(
		12, -25, -98, 0,
		45, 369, 7, 0,
		98, -5, 180, 0,
		0, 0, 0, 1), m2);

	//rotate 90,
	m1 = Matrix4(
		1, 0, 0, 0,
		0, 0, -1, 0,
		0, 1, 0, 0,
		0, 0, 0, 1);
	//translate 1,2,3
	m2 = Matrix4(
		1, 0, 0, 1,
		0, 1, 0, 2,
		0, 0, 1, 3,
		0, 0, 0, 1);
	m1 *= m2;
	expect = Matrix4(
		1, 0, 0, 1,
		0, 0, -1, -3,
		0, 1, 0, 2,
		0, 0, 0, 1);
	//scale

	EXPECT_EQ(expect, m1);

	//EXPECT_FLOAT_EQ(54, m1.matrix[0][0]);
	//EXPECT_FLOAT_EQ(72, m1.matrix[0][1]);
	//EXPECT_FLOAT_EQ(90, m1.matrix[0][2]);
	//EXPECT_FLOAT_EQ(42, m1.matrix[1][0]);
	//EXPECT_FLOAT_EQ(57, m1.matrix[1][1]);
	//EXPECT_FLOAT_EQ(72, m1.matrix[1][2]);
	//EXPECT_FLOAT_EQ(30, m1.matrix[2][0]);
	//EXPECT_FLOAT_EQ(42, m1.matrix[2][1]);
	//EXPECT_FLOAT_EQ(54, m1.matrix[2][2]);

	//verify multiply identity equals same matrix
	EXPECT_TRUE(m2 == (m2 *= Matrix4::Identity()));
}

TEST(matrix4, identity)
{
	Matrix4 expect(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
	EXPECT_EQ(expect, Matrix4::Identity());
}

TEST(matrix4, orthographicProjection)
{
	Matrix4 result = Matrix4::GetOrthographicProjection(0, 100, 100, 0, -10, 100);

	EXPECT_FLOAT_EQ(.02, result.matrix[0][0]);
	EXPECT_FLOAT_EQ(0, result.matrix[0][1]);
	EXPECT_FLOAT_EQ(0, result.matrix[0][2]);
	EXPECT_FLOAT_EQ(-1, result.matrix[0][3]);
	EXPECT_FLOAT_EQ(0, result.matrix[1][0]);
	EXPECT_FLOAT_EQ(.02, result.matrix[1][1]);
	EXPECT_FLOAT_EQ(0, result.matrix[1][2]);
	EXPECT_FLOAT_EQ(-1, result.matrix[1][3]);
	EXPECT_FLOAT_EQ(0, result.matrix[2][0]);
	EXPECT_FLOAT_EQ(0, result.matrix[2][1]);
	EXPECT_FLOAT_EQ(-2.0f / 110, result.matrix[2][2]);
	EXPECT_FLOAT_EQ(-90.0f / 110.0f, result.matrix[2][3]);
	EXPECT_FLOAT_EQ(0, result.matrix[3][0]);
	EXPECT_FLOAT_EQ(0, result.matrix[3][1]);
	EXPECT_FLOAT_EQ(0, result.matrix[3][2]);
	EXPECT_FLOAT_EQ(1, result.matrix[3][3]);
}

TEST(matrix4, transform)
{
	Matrix4 m(
		3, 12, 6, 0,
		7, 10, 4, 0,
		5, 2, 9, 0,
		0, 0, 0, 1);
	Vector3 v(
		8,
		7,
		2);
	Vector3 result = m.Transform(v);
	Vector3 expected(
		120,
		134,
		72);

	EXPECT_TRUE(expected == result);
	EXPECT_TRUE(v == Vector3(8, 7, 2));
	EXPECT_TRUE(m == Matrix4(
		3, 12, 6, 0,
		7, 10, 4, 0,
		5, 2, 9, 0,
		0, 0, 0, 1));

	EXPECT_TRUE(v == (Matrix4::Identity().Transform(v)));
}

TEST(matrix4, productOperatorVector4)
{
	Matrix4 m(
		3, 12, 6, 2,
		7, 10, 4, -3,
		5, 2, 9, 3,
		0, 0, 0, 1);
	Vector4 v(
		8,
		7,
		2,
		1);
	Vector4 result = m * v;
	Vector4 expected(
		122,
		131,
		75,
		1);

	EXPECT_EQ(expected, result);
	EXPECT_EQ(v, Vector4(8, 7, 2, 1));
	EXPECT_EQ(m, Matrix4(
		3, 12, 6, 2,
		7, 10, 4, -3,
		5, 2, 9, 3,
		0, 0, 0, 1));

	EXPECT_TRUE(v == (Matrix4::Identity() * v));
}

TEST(matrix4, productOperator)
{

	Matrix4 m1(
		0, 1, 2, 0,
		4, 5, 6, 0,
		8, 9, 10, 0,
		0, 0, 0, 1);
	Matrix4 m2(
		0, 1, 2, 0,
		4, 5, 6, 0,
		8, 9, 10, 0,
		0, 0, 0, 1);
	Matrix4 r;
	r = m1 * m2;
	Matrix4 expect(
		20, 23, 26, 0,
		68, 83, 98, 0,
		116, 143, 170, 0,
		0, 0, 0, 1);

	EXPECT_EQ(expect, r);
	EXPECT_EQ(Matrix4(
		0, 1, 2, 0,
		4, 5, 6, 0,
		8, 9, 10, 0,
		0, 0, 0, 1), m1);
	EXPECT_EQ(Matrix4(
		0, 1, 2, 0,
		4, 5, 6, 0,
		8, 9, 10, 0,
		0, 0, 0, 1), m2);

	m1 = Matrix4(
		320, -8, 58, 0,
		45, 26, -369, 0,
		65, 14, -65, 0,
		0, 0, 0, 1);

	m2 = Matrix4(
		12, -25, -98, 0,
		45, 369, 7, 0,
		98, -5, 180, 0,
		0, 0, 0, 1);

	r = m1 * m2;

	expect = Matrix4(
		9164, -11242, -20976, 0,
		-34452, 10314, -70648, 0,
		-4960, 3866, -17972, 0,
		0, 0, 0, 1);

	EXPECT_EQ(expect, r);
	EXPECT_EQ(Matrix4(
		320, -8, 58, 0,
		45, 26, -369, 0,
		65, 14, -65, 0,
		0, 0, 0, 1), m1);
	EXPECT_EQ(Matrix4(
		12, -25, -98, 0,
		45, 369, 7, 0,
		98, -5, 180, 0,
		0, 0, 0, 1), m2);

	//rotate 90,
	m1 = Matrix4(
		1, 0, 0, 0,
		0, 0, -1, 0,
		0, 1, 0, 0,
		0, 0, 0, 1);
	//translate 1,2,3
	m2 = Matrix4(
		1, 0, 0, 1,
		0, 1, 0, 2,
		0, 0, 1, 3,
		0, 0, 0, 1);

	r = m1 * m2;

	expect = Matrix4(
		1, 0, 0, 1,
		0, 0, -1, -3,
		0, 1, 0, 2,
		0, 0, 0, 1);
	//scale

	EXPECT_EQ(expect, r);

	m1 = Matrix4(
		1, 2, 1, 2,
		2, 1, 1, 2,
		3, 2, 1, 3,
		4, 2, 1, 2);
	m2 = Matrix4(
		3, 2, 4, 1,
		3, 1, 2, 1,
		0, -2, 1, 2,
		-3, 2, 1, 4);
	expect = Matrix4(
		3, 6, 11, 13,
		3, 7, 13, 13,
		6, 12, 20, 19,
		12, 12, 23, 16);
	r = m1 * m2;

	EXPECT_EQ(expect, r);

	//verify multiply identity equals same matrix
	EXPECT_TRUE(r == (r = m2 * Matrix4::Identity()));
}

TEST(matrix4, subtractOperator)
{
	Matrix4 m1(
		1, 2, 3, 4,
		4, 5, 6, 3,
		7, 8, 9, 2,
		1, 2, 3, 4);
	Matrix4 m2(
		9, 8, 7, 2,
		6, 5, 4, 3,
		3, 2, 1, -3,
		0, 0, 2, 1);

	Matrix4 result = m2 - m1;

	Matrix4 expect(
		8, 6, 4, -2,
		2, 0, -2, 0,
		-4, -6, -8, -5,
		-1, -2, -1, -3);
	EXPECT_EQ(expect, result);
	EXPECT_EQ(m1, Matrix4(
		1, 2, 3, 4,
		4, 5, 6, 3,
		7, 8, 9, 2,
		1, 2, 3, 4));
	EXPECT_EQ(m2, Matrix4(
		9, 8, 7, 2,
		6, 5, 4, 3,
		3, 2, 1, -3,
		0, 0, 2, 1));

	//verify chaining 
	result = m2 - m1 - m1;
	expect = Matrix4(
		7, 4, 1, -6,
		-2, -5, -8, -3,
		-11, -14, -17, -7,
		-2, -4, -4, -7);

	EXPECT_EQ(expect, result);
	EXPECT_EQ(m1, Matrix4(
		1, 2, 3, 4,
		4, 5, 6, 3,
		7, 8, 9, 2,
		1, 2, 3, 4));
	EXPECT_EQ(m2, Matrix4(
		9, 8, 7, 2,
		6, 5, 4, 3,
		3, 2, 1, -3,
		0, 0, 2, 1));
}

TEST(matrix4, additionOperator)
{
	Matrix4 m1(
		1, 2, 3, 4,
		4, 5, 6, 3,
		7, 8, 9, 2,
		1, 2, 3, 4);
	Matrix4 m2(
		9, 8, 7, 2,
		6, 5, 4, 3,
		3, 2, 1, -3,
		0, 0, 2, 1);

	Matrix4 result = m2 + m1;

	Matrix4 expect(
		10, 10, 10, 6,
		10, 10, 10, 6,
		10, 10, 10, -1,
		1, 2, 5, 5);

	EXPECT_EQ(expect, result);
	EXPECT_EQ(m1, Matrix4(
		1, 2, 3, 4,
		4, 5, 6, 3,
		7, 8, 9, 2,
		1, 2, 3, 4));
	EXPECT_EQ(m2, Matrix4(
		9, 8, 7, 2,
		6, 5, 4, 3,
		3, 2, 1, -3,
		0, 0, 2, 1));

	//verify chaining 
	result = m1 + m2 + result;
	expect = Matrix4(
		20, 20, 20, 12,
		20, 20, 20, 12,
		20, 20, 20, -2,
		2, 4, 10, 10);

	EXPECT_EQ(expect, result);
	EXPECT_EQ(m1, Matrix4(
		1, 2, 3, 4,
		4, 5, 6, 3,
		7, 8, 9, 2,
		1, 2, 3, 4));
	EXPECT_EQ(m2, Matrix4(
		9, 8, 7, 2,
		6, 5, 4, 3,
		3, 2, 1, -3,
		0, 0, 2, 1));
}

TEST(matrix4, setupRotationIndividualAxis)
{
	Matrix4 m = Matrix4::SetupRotation(X, JMath::DegreeToRadians(0));
	Matrix4 expected(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	EXPECT_EQ(expected, m);

	m = Matrix4::SetupRotation(Y, JMath::DegreeToRadians(0));
	expected = Matrix4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	EXPECT_EQ(expected, m);

	m = Matrix4::SetupRotation(Z, JMath::DegreeToRadians(0));
	expected = Matrix4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	EXPECT_EQ(expected, m);

	float rads = JMath::DegreeToRadians(90);
	m = Matrix4::SetupRotation(X, rads);
	expected = Matrix4(
		1, 0, 0, 0,
		0, cos(rads), -sin(rads), 0,
		0, sin(rads), cos(rads), 0,
		0, 0, 0, 1);
	EXPECT_EQ(expected, m);

	m = Matrix4::SetupRotation(Y, rads);
	expected = Matrix4(
		cos(rads), 0, sin(rads), 0,
		0, 1, 0, 0,
		-sin(rads), 0, cos(rads), 0,
		0, 0, 0, 1);
	EXPECT_EQ(expected, m);

	m = Matrix4::SetupRotation(Z, rads);
	expected = Matrix4(
		cos(rads), -sin(rads), 0, 0,
		sin(rads), cos(rads), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
	EXPECT_EQ(expected, m);

	rads = JMath::DegreeToRadians(-90);
	m = Matrix4::SetupRotation(X, rads);
	expected = Matrix4(
		1, 0, 0, 0,
		0, cos(rads), -sin(rads), 0,
		0, sin(rads), cos(rads), 0,
		0, 0, 0, 1);
	EXPECT_EQ(expected, m);
}

TEST(matrix4, setupRotationCombinesAxisSingleValue)
{
	Matrix4 m = Matrix4::SetupRotation(JMath::DegreeToRadians(0));
	Matrix4 expected(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	EXPECT_EQ(expected, m);

	float rads = JMath::DegreeToRadians(90);
	m = Matrix4::SetupRotation(rads);
	expected = Matrix4(
		0, 0, 1, 0,
		0, -1, 0, 0,
		1, 0, 0, 0,
		0, 0, 0, 1);
	float delta = .00001;
	EXPECT_NEAR(0, m[0][0], delta);
	EXPECT_NEAR(0, m[0][1], delta);
	EXPECT_NEAR(1, m[0][2], delta);
	EXPECT_NEAR(0, m[0][3], delta);
	EXPECT_NEAR(0, m[1][0], delta);
	EXPECT_NEAR(-1, m[1][1], delta);
	EXPECT_NEAR(0, m[1][2], delta);
	EXPECT_NEAR(0, m[1][3], delta);
	EXPECT_NEAR(1, m[2][0], delta);
	EXPECT_NEAR(0, m[2][1], delta);
	EXPECT_NEAR(0, m[2][2], delta);
	EXPECT_NEAR(0, m[2][3], delta);
	EXPECT_NEAR(0, m[3][0], delta);
	EXPECT_NEAR(0, m[3][1], delta);
	EXPECT_NEAR(0, m[3][2], delta);
	EXPECT_NEAR(1, m[3][3], delta);

}
TEST(matrix4, setupRotationCombinesAxisVector3)
{
	Matrix4 m = Matrix4::SetupRotation(JMath::DegreeToRadians(0));
	Matrix4 expected(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	EXPECT_EQ(expected, m);

	float rads = JMath::DegreeToRadians(90);
	Vector3 angles(rads, rads, rads);
	m = Matrix4::SetupRotation(angles);
	expected = Matrix4(
		0, 0, 1, 0,
		0, -1, 0, 0,
		1, 0, 0, 0,
		0, 0, 0, 1);
	float delta = .00001;
	EXPECT_NEAR(0, m[0][0], delta);
	EXPECT_NEAR(0, m[0][1], delta);
	EXPECT_NEAR(1, m[0][2], delta);
	EXPECT_NEAR(0, m[0][3], delta);
	EXPECT_NEAR(0, m[1][0], delta);
	EXPECT_NEAR(-1, m[1][1], delta);
	EXPECT_NEAR(0, m[1][2], delta);
	EXPECT_NEAR(0, m[1][3], delta);
	EXPECT_NEAR(1, m[2][0], delta);
	EXPECT_NEAR(0, m[2][1], delta);
	EXPECT_NEAR(0, m[2][2], delta);
	EXPECT_NEAR(0, m[2][3], delta);
	EXPECT_NEAR(0, m[3][0], delta);
	EXPECT_NEAR(0, m[3][1], delta);
	EXPECT_NEAR(0, m[3][2], delta);
	EXPECT_NEAR(1, m[3][3], delta);

	rads = JMath::DegreeToRadians(-90);
	angles.y = angles.z = 0;
	angles.x = rads;
	m = Matrix4::SetupRotation(angles);
	expected = Matrix4(
		1, 0, 0, 0,
		0, cos(rads), -sin(rads), 0,
		0, sin(rads), cos(rads), 0,
		0, 0, 0, 1);
	EXPECT_EQ(expected, m);

}

TEST(matrix4, setupScale)
{
	Matrix4 m = Matrix4::SetupScale(Vector3(5, 10, 2));
	Matrix4 expect(
		5, 0, 0, 0,
		0, 10, 0, 0,
		0, 0, 2, 0,
		0, 0, 0, 1);
	EXPECT_EQ(expect, m);

	m = Matrix4::SetupScale(Vector3(.25, .5, .2));
	expect = Matrix4(
		.25, 0, 0, 0,
		0, .50, 0, 0,
		0, 0, .2, 0,
		0, 0, 0, 1);
	EXPECT_EQ(expect, m);
}

TEST(matrix4, setupTranslation)
{
	Matrix4 m = Matrix4::SetupTranslation(Vector3(2, 5, -2));
	Matrix4 expect(
		1, 0, 0, 2,
		0, 1, 0, 5,
		0, 0, 1, -2,
		0, 0, 0, 1);
	EXPECT_EQ(expect, m);

	m = Matrix4::SetupTranslation(Vector3(5, -1, 43));
	expect = Matrix4(
		1, 0, 0, 5,
		0, 1, 0, -1,
		0, 0, 1, 43,
		0, 0, 0, 1);
	EXPECT_EQ(expect, m);
}

TEST(matrix4, bracketOperator)
{
	Matrix4 m(
		1, 2, 3, 4,
		4, 5, 6, 5,
		7, 8, 9, 6,
		7, 8, 9, 10);

	float* v = m[2];
	float f = v[2];

	EXPECT_EQ(9, f);

	f = m[3][2];
	EXPECT_EQ(9, f);
}

TEST(matrix4, transpose)
{
	Matrix4 m(
		1, 5, 6, 7,
		2, 7, 8, 6,
		2, 7, 5, -2,
		23, 4, 3, 65);
	Matrix4 expected(
		1, 2, 2, 23,
		5, 7, 7, 4,
		6, 8, 5, 3,
		7, 6, -2, 65);
	m.Transpose();
	EXPECT_EQ(expected, m);

	m = Matrix4(
		6, 4, 8, 12,
		3, 1, 2, 21,
		3, 9, 5, -76,
		87, 7, 4, 0);
	expected = Matrix4(
		6, 3, 3, 87,
		4, 1, 9, 7,
		8, 2, 5, 4,
		12, 21, -76, 0);
	m.Transpose();

	EXPECT_EQ(expected, m);
}

TEST(matrix4, getTranspose)
{
	Matrix4 m(
		1, 5, 6, 7,
		2, 7, 8, 6,
		2, 7, 5, -2,
		23, 4, 3, 65);
	Matrix4 expected(
		1, 2, 2, 23,
		5, 7, 7, 4,
		6, 8, 5, 3,
		7, 6, -2, 65);
	Matrix4 r = m.GetTranspose();
	EXPECT_EQ(expected, r);
	EXPECT_EQ(Matrix4(
		1, 5, 6, 7,
		2, 7, 8, 6,
		2, 7, 5, -2,
		23, 4, 3, 65), m);

	m = Matrix4(
		6, 4, 8, 12,
		3, 1, 2, 21,
		3, 9, 5, -76,
		87, 7, 4, 0);
	expected = Matrix4(
		6, 3, 3, 87,
		4, 1, 9, 7,
		8, 2, 5, 4,
		12, 21, -76, 0);
	r = m.GetTranspose();

	EXPECT_EQ(expected, r);
	EXPECT_EQ(Matrix4(
		6, 4, 8, 12,
		3, 1, 2, 21,
		3, 9, 5, -76,
		87, 7, 4, 0), m);
}

#endif