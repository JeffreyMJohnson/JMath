#ifndef _TEST_MATRIX_3_H_
#define _TEST_MATRIX_3_H_
/*
header file defines public API for Google test, needs to be included for any test program that uses it.
*/
#include "gtest/gtest.h"

#include "..\..\JMath_static\include\TheMath.h"

TEST(matrix3, constructorDefault)
{
	Matrix3 m;

	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			EXPECT_FLOAT_EQ(0, m.matrix[row][col]);
		}
	}
}

TEST(matrix3, constructor)
{
	Matrix3 m(
		10, 11, 12,
		20, 21, 22,
		30, 31, 32);

	EXPECT_FLOAT_EQ(10, m.matrix[0][0]);
	EXPECT_FLOAT_EQ(11, m.matrix[0][1]);
	EXPECT_FLOAT_EQ(12, m.matrix[0][2]);
	EXPECT_FLOAT_EQ(20, m.matrix[1][0]);
	EXPECT_FLOAT_EQ(21, m.matrix[1][1]);
	EXPECT_FLOAT_EQ(22, m.matrix[1][2]);
	EXPECT_FLOAT_EQ(30, m.matrix[2][0]);
	EXPECT_FLOAT_EQ(31, m.matrix[2][1]);
	EXPECT_FLOAT_EQ(32, m.matrix[2][2]);

}

TEST(matrix3, copyConstructor)
{
	Matrix3 m(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);

	Matrix3 m2(m);

	EXPECT_TRUE(m2 == m);
	//verify copy not same object
	EXPECT_FALSE(&m2 == &m) << "expect: " << &m2 << "result: " << &m;
}

TEST(matrix3, transpose)
{
	Matrix3 m(
		1, 5, 6,
		2, 7, 8,
		2, 7, 5);
	Matrix3 expected(
		1, 2, 2,
		5, 7, 7,
		6, 8, 5);
	m.Transpose();
	EXPECT_TRUE(expected == m) << m;

	m = Matrix3(
		6, 4, 8,
		3, 1, 2,
		3, 9, 5);
	expected = Matrix3(
		6, 3, 3,
		4, 1, 9,
		8, 2, 5);
	m.Transpose();

	//EXPECT_FLOAT_EQ(6, m.matrix[0][0]);
	//EXPECT_FLOAT_EQ(3, m.matrix[0][1]);
	//EXPECT_FLOAT_EQ(3, m.matrix[0][2]);
	//EXPECT_FLOAT_EQ(4, m.matrix[1][0]);
	//EXPECT_FLOAT_EQ(1, m.matrix[1][1]);
	//EXPECT_FLOAT_EQ(9, m.matrix[1][2]);
	//EXPECT_FLOAT_EQ(8, m.matrix[2][0]);
	//EXPECT_FLOAT_EQ(2, m.matrix[2][1]);
	//EXPECT_FLOAT_EQ(5, m.matrix[2][2]);

	EXPECT_TRUE(expected == m);
}

TEST(matrix3, bracketOperator)
{
	Matrix3 m(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);
	float v = *m[0];

	EXPECT_TRUE(1 == v) << v;
}

TEST(matrix3, doubleBracketOperator)
{
	Matrix3 m(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);
	
	EXPECT_FLOAT_EQ(5, m[1][1]);
	EXPECT_FLOAT_EQ(3, m[0][2]);

	EXPECT_FLOAT_EQ(9, m[2][2]);
}

TEST(matrix3, getTranspose)
{
	Matrix3 m(
		12, 44, 55,
		31, 64, 77,
		-12, 66, 987);
	Matrix3 result = m.GetTranspose();
	Matrix3 expected(
		12, 31, -12,
		44, 64, 66,
		55, 77, 987);
	EXPECT_TRUE(expected == result);
	EXPECT_TRUE(m == Matrix3(
		12, 44, 55,
		31, 64, 77,
		-12, 66, 987));

	m = Matrix3(
		-120, 3.45, 23.9,
		-43.5, 20, 130,
		965, -287, 44);
	result = m.GetTranspose();
	expected = Matrix3(
		-120, -43.5, 965,
		3.45, 20, -287,
		23.9, 130, 44);

	EXPECT_TRUE(expected == result);
	EXPECT_TRUE(m == Matrix3(
		-120, 3.45, 23.9,
		-43.5, 20, 130,
		965, -287, 44));
}

TEST(matrix3, equality)
{
	Matrix3 m1(
		2, 3, 4,
		2, 3, 4,
		2, 3, 4);

	Matrix3 m2(
		2, 3, 4,
		2, 3, 4,
		2, 3, 4);

	Matrix3 m3(
		1, 3, 4,
		2, 3, 4,
		2, 3, 4);

	EXPECT_TRUE(m1 == m2);
	EXPECT_TRUE(m1 == m1);
	EXPECT_FALSE(m1 == m3);

}

TEST(matrix3, inEquality)
{
	Matrix3 m1(
		2, 3, 4,
		2, 3, 4,
		2, 3, 4);

	Matrix3 m2(
		2, 3, 4,
		2, 3, 4,
		2, 3, 4);

	Matrix3 m3(
		1, 3, 4,
		2, 3, 4,
		2, 3, 4);

	EXPECT_TRUE(m1 != m3);
	EXPECT_TRUE(m2 != m3);
	EXPECT_FALSE(m1 != m2);

}

TEST(matrix3, assignmentOperator)
{
	Matrix3 m1(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);
	Matrix3 m2;
	Matrix3 m3;
	m3 = m2 = m1;

	EXPECT_TRUE(m1 == m2);
	EXPECT_TRUE(m1 == m3);

}

TEST(matrix3, identity)
{
	Matrix3 expect(
		1, 0, 0,
		0, 1, 0,
		0, 0, 1);
	EXPECT_TRUE(expect == Matrix3::Identity());
}

TEST(matrix3, setupRotation)
{
	Matrix3 m = Matrix3::SetupRotation(JMath::DegreeToRadians(0));
	Matrix3 expected(
		1, 0, 0,
		0, 1, 0,
		0, 0, 1);
	EXPECT_TRUE(expected == m) << "result:\n" << m << "\nexpected:\n" << expected;

	float rads = JMath::DegreeToRadians(90);
	m = Matrix3::SetupRotation(rads);
	expected = Matrix3(
		cos(rads), -sin(rads), 0,
		sin(rads), cos(rads), 0,
		0, 0, 1);
	EXPECT_TRUE(expected == m) << "result:\n" << m << "\nexpected:\n" << expected;

	rads = JMath::DegreeToRadians(-90);
	m = Matrix3::SetupRotation(rads);
	expected = Matrix3(
		cos(rads), -sin(rads), 0,
		sin(rads), cos(rads), 0,
		0, 0, 1);
	EXPECT_TRUE(expected == m) << "result:\n" << m << "\nexpected:\n" << expected;

}

TEST(matrix3, setupScale)
{
	Matrix3 m = Matrix3::SetupScale(Vector2(5, 10));
	Matrix3 expect(
		5, 0, 0,
		0, 10, 0,
		0, 0, 1);
	EXPECT_TRUE(m == expect);

	m = Matrix3::SetupScale(Vector2(.25, .5));
	expect = Matrix3(
		.25, 0, 0,
		0, .50, 0,
		0, 0, 1);
	EXPECT_TRUE(m == expect);
}

TEST(matrix3, setupTranslation)
{
	Matrix3 m = Matrix3::SetupTranslation(Vector2(2, 5));
	Matrix3 expect(
		1, 0, 2,
		0, 1, 5,
		0, 0, 1);
	EXPECT_TRUE(expect == m) << "result:\n" << m << "\nexpected:\n" << expect;

	m = Matrix3::SetupTranslation(Vector2(5, -1));
	expect = Matrix3(
		1, 0, 5,
		0, 1, -1,
		0, 0, 1);
	EXPECT_TRUE(expect == m) << "result:\n" << m << "\nexpected:\n" << expect;
}

TEST(matrix3, additionOperator)
{
	Matrix3 m1(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);
	Matrix3 m2(
		9, 8, 7,
		6, 5, 4,
		3, 2, 1);

	Matrix3 result = m2 + m1;

	Matrix3 expect(
		10, 10, 10,
		10, 10, 10,
		10, 10, 10);

	EXPECT_TRUE(expect == result);
	EXPECT_TRUE(m1 == Matrix3(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9));
	EXPECT_TRUE(m2 == Matrix3(
		9, 8, 7,
		6, 5, 4,
		3, 2, 1));

	//verify chaining 
	result = m1 + m2 + result;
	expect = Matrix3(
		20, 20, 20,
		20, 20, 20,
		20, 20, 20);

	EXPECT_TRUE(expect == result);
	EXPECT_TRUE(m1 == Matrix3(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9));
	EXPECT_TRUE(m2 == Matrix3(
		9, 8, 7,
		6, 5, 4,
		3, 2, 1));
}

TEST(matrix3, subtractOperator)
{
	Matrix3 m1(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);
	Matrix3 m2(
		9, 8, 7,
		6, 5, 4,
		3, 2, 1);

	Matrix3 result = m2 - m1;

	Matrix3 expect(
		8, 6, 4,
		2, 0, -2,
		-4, -6, -8);
	EXPECT_TRUE(expect == result);
	EXPECT_TRUE(m1 == Matrix3(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9));
	EXPECT_TRUE(m2 == Matrix3(
		9, 8, 7,
		6, 5, 4,
		3, 2, 1));

	//verify chaining 
	result = m2 - m1 - m1;
	expect = Matrix3(
		7, 4, 1,
		-2, -5, -8,
		-11, -14, -17);

	EXPECT_TRUE(expect == result);
	EXPECT_TRUE(m1 == Matrix3(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9));
	EXPECT_TRUE(m2 == Matrix3(
		9, 8, 7,
		6, 5, 4,
		3, 2, 1));
}

TEST(matrix3, productOperator)
{
	Matrix3 m1(
		0, 1, 2,
		3, 4, 5,
		6, 7, 8);
	Matrix3 m2(
		0, 1, 2,
		3, 4, 5,
		6, 7, 8);
	Matrix3 m3 = m1 * m2;

	Matrix3 expect(
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

	EXPECT_TRUE(expect == m3);
	EXPECT_TRUE(m1 == Matrix3(
		0, 1, 2,
		3, 4, 5,
		6, 7, 8));
	EXPECT_TRUE(m2 == Matrix3(
		0, 1, 2,
		3, 4, 5,
		6, 7, 8));

	m1 = Matrix3(
		9, 6, 3,
		8, 5, 2,
		7, 4, 1);
	m2 = Matrix3(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);
	m3 = m1 * m2;

	expect = Matrix3(
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

	EXPECT_TRUE(expect == m3);
	EXPECT_TRUE(m1 == Matrix3(
		9, 6, 3,
		8, 5, 2,
		7, 4, 1));
	EXPECT_TRUE(m2 == Matrix3(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9));

	//verify multiply identity equals same matrix
	EXPECT_TRUE(m3 == (m3 = m3 * Matrix3::Identity()));

	//verify chaining
	expect = Matrix3(
		54, 72, 90,
		42, 57, 72,
		30, 42, 54);
	m3 = m1 * m2 * Matrix3::Identity();
	EXPECT_TRUE(expect == m3)<< "expected\n" << expect << "\nresult:\n" << m3;
	EXPECT_TRUE(m1 == Matrix3(
		9, 6, 3,
		8, 5, 2,
		7, 4, 1));
	EXPECT_TRUE(m2 == Matrix3(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9));
}

TEST(matrix3, productOperatorVector3)
{
	Matrix3 m(
		3, 12, 6,
		7, 10, 4,
		5, 2, 9);
	Vector3 v(
		8,
		7,
		2);
	Vector3 result = m * v;
	Vector3 expected(
		120,
		134,
		72);

	EXPECT_TRUE(expected == result);
	EXPECT_TRUE(v == Vector3(8, 7, 2));
	EXPECT_TRUE(m == Matrix3(
		3, 12, 6,
		7, 10, 4,
		5, 2, 9));

	EXPECT_TRUE(v == (Matrix3::Identity() * v));
}

TEST(matrix3, additionAssignemntOperator)
{
	Matrix3 m1(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);
	Matrix3 m2(
		9, 8, 7,
		6, 5, 4,
		3, 2, 1);
	Matrix3 expect(
		10, 10, 10,
		10, 10, 10,
		10, 10, 10);
	EXPECT_TRUE(expect == (m1 += m2));
	EXPECT_TRUE(m2 ==
		Matrix3(
		9, 8, 7,
		6, 5, 4,
		3, 2, 1));
}

TEST(matrix3, subtractAssignemntOperator)
{
	Matrix3 m1(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);
	Matrix3 m2(
		9, 8, 7,
		6, 5, 4,
		3, 2, 1);
	Matrix3 expect(
		-8, -6, -4,
		-2, 0, 2,
		4, 6, 8);
	EXPECT_TRUE(expect == (m1 -= m2));
	EXPECT_TRUE(m2 ==
		Matrix3(
		9, 8, 7,
		6, 5, 4,
		3, 2, 1));
}

TEST(matrix3, productAssignemntOperator)
{
	Matrix3 m1(
		0, 1, 2,
		3, 4, 5,
		6, 7, 8);
	Matrix3 m2(
		0, 1, 2,
		3, 4, 5,
		6, 7, 8);
	m1 *= m2;
	Matrix3 expect(
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
	EXPECT_TRUE(m2 == Matrix3(
		0, 1, 2,
		3, 4, 5,
		6, 7, 8));

	m1 = Matrix3(
		9, 6, 3,
		8, 5, 2,
		7, 4, 1);
	m2 = Matrix3(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);
	m1 *= m2;
	expect = Matrix3(
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
	EXPECT_TRUE(m2 == Matrix3(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9));

	//verify multiply identity equals same matrix
	EXPECT_TRUE(m2 == (m2 *= Matrix3::Identity()));
}

#endif
