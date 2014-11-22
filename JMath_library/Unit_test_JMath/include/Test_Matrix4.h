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
		0, 1, 2, 3,
		4, 5, 6, 7,
		8, 9, 10, 11,
		12, 13, 14, 15);
	Matrix4 m2(
		0, 1, 2, 3,
		4, 5, 6, 7,
		8, 9, 10, 11,
		12, 13, 14, 15);
	m1 *= m2;
	Matrix4 expect(
		15, 18, 21,
		42, 54, 66,
		69, 90, 111);

	//EXPECT_FLOAT_EQ(15, m1.matrix[0][0]);
	//EXPECT_FLOAT_EQ(18, m1.matrix[0][1]);
	//EXPECT_FLOAT_EQ(21, m1.matrix[0][2]);
	//EXPECT_FLOAT_EQ(42, m1.matrix[1][0]);
	//EXPECT_FLOAT_EQ(54, m1.matrix[1][1]);
	//EXPECT_FLOAT_EQ(66, m1.matrix[1][2]);
	//EXPECT_FLOAT_EQ(69, m1.matrix[2][0]);
	//EXPECT_FLOAT_EQ(90, m1.matrix[2][1]);
	//EXPECT_FLOAT_EQ(111, m1.matrix[2][2]);

	EXPECT_TRUE(expect == m1);
	EXPECT_TRUE(m2 == Matrix4(
		0, 1, 2,
		3, 4, 5,
		6, 7, 8));

	m1 = Matrix4(
		9, 6, 3,
		8, 5, 2,
		7, 4, 1);
	m2 = Matrix4(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);
	m1 *= m2;
	expect = Matrix4(
		54, 72, 90,
		42, 57, 72,
		30, 42, 54);

	//EXPECT_FLOAT_EQ(54, m1.matrix[0][0]);
	//EXPECT_FLOAT_EQ(72, m1.matrix[0][1]);
	//EXPECT_FLOAT_EQ(90, m1.matrix[0][2]);
	//EXPECT_FLOAT_EQ(42, m1.matrix[1][0]);
	//EXPECT_FLOAT_EQ(57, m1.matrix[1][1]);
	//EXPECT_FLOAT_EQ(72, m1.matrix[1][2]);
	//EXPECT_FLOAT_EQ(30, m1.matrix[2][0]);
	//EXPECT_FLOAT_EQ(42, m1.matrix[2][1]);
	//EXPECT_FLOAT_EQ(54, m1.matrix[2][2]);

	EXPECT_TRUE(expect == m1);
	EXPECT_TRUE(m2 == Matrix4(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9));

	//verify multiply identity equals same matrix
	//EXPECT_TRUE(m2 == (m2 *= Matrix4::Identity()));
}

#endif