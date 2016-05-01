#include "CppUnitTest.h"
#include "TheMath.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_static
{
	TEST_CLASS(Test_Matrix3)
	{
	public:
		const double DELTA = .00001;
		TEST_METHOD(constructorDefault)
		{
			Matrix3 m;

			for (int row = 0; row < 3; row++)
			{
				for (int col = 0; col < 3; col++)
				{
					Assert::AreEqual(0, static_cast<double>(m.matrix[row][col]), DELTA);
				}
			}
		}

		TEST_METHOD(constructor)
		{
			Matrix3 m(
				10, 11, 12,
				20, 21, 22,
				30, 31, 32);

			Assert::AreEqual(10,static_cast<double>(m.matrix[0][0]), DELTA);
			Assert::AreEqual(11,static_cast<double>(m.matrix[0][1]), DELTA);
			Assert::AreEqual(12,static_cast<double>(m.matrix[0][2]), DELTA);
			Assert::AreEqual(20,static_cast<double>(m.matrix[1][0]), DELTA);
			Assert::AreEqual(21,static_cast<double>(m.matrix[1][1]), DELTA);
			Assert::AreEqual(22,static_cast<double>(m.matrix[1][2]), DELTA);
			Assert::AreEqual(30,static_cast<double>(m.matrix[2][0]), DELTA);
			Assert::AreEqual(31,static_cast<double>(m.matrix[2][1]), DELTA);
			Assert::AreEqual(32,static_cast<double>(m.matrix[2][2]), DELTA);
		}

		TEST_METHOD(copyConstructor)
		{
			Matrix3 m(
				1, 2, 3,
				4, 5, 6,
				7, 8, 9);

			Matrix3 m2(m);

			Assert::IsTrue(m2 == m);
			//verify copy not same object
			Assert::IsFalse(&m2 == &m);
		}

		TEST_METHOD(getVector3FromMatrix)
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
			Assert::IsTrue(result == Vector3(0, 1, 2));

			result = Matrix3::GetVector3(majorType, 1, mRow);
			Assert::IsTrue(result == Vector3(3, 4, 5));

			result = Matrix3::GetVector3(majorType, 2, mRow);
			Assert::IsTrue(result == Vector3(6, 7, 8));

			majorType = COL;
			result = Matrix3::GetVector3(majorType, 0, mCol);
			Assert::IsTrue(result == Vector3(0, 1, 2));

			result = Matrix3::GetVector3(majorType, 1, mCol);
			Assert::IsTrue(result == Vector3(3, 4, 5));

			result = Matrix3::GetVector3(majorType, 2, mCol);
			Assert::IsTrue(result == Vector3(6, 7, 8));
		}

		TEST_METHOD(transpose)
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
			Assert::IsTrue(expected == m);

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

			Assert::IsTrue(expected == m);
		}

		TEST_METHOD(bracketOperator)
		{
			Matrix3 m(
				1, 2, 3,
				4, 5, 6,
				7, 8, 9);
			float* v = m[0];
			float f = v[2];
			Assert::AreEqual(3, static_cast<double>(f), DELTA);

			f = m[1][1];
			Assert::AreEqual(5, static_cast<double>(f), DELTA);
		}

		TEST_METHOD(doubleBracketOperator)
		{
			Matrix3 m(
				1, 2, 3,
				4, 5, 6,
				7, 8, 9);

			Assert::AreEqual(5, static_cast<double>(m[1][1]), DELTA);
			Assert::AreEqual(3, static_cast<double>(m[0][2]), DELTA);
			Assert::AreEqual(9, static_cast<double>(m[2][2]), DELTA);
		}

		TEST_METHOD(getTranspose)
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
			Assert::IsTrue(expected == result);
			Assert::IsTrue(m == Matrix3(
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

			Assert::IsTrue(expected == result);
			Assert::IsTrue(m == Matrix3(
				-120, 3.45, 23.9,
				-43.5, 20, 130,
				965, -287, 44));
		}

		TEST_METHOD(equality)
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

			Assert::IsTrue(m1 == m2);
			Assert::IsTrue(m1 == m1);
			Assert::IsFalse(m1 == m3);

		}

		TEST_METHOD(inEquality)
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

			Assert::IsTrue(m1 != m3);
			Assert::IsTrue(m2 != m3);
			Assert::IsFalse(m1 != m2);

		}

		TEST_METHOD(assignmentOperator)
		{
			Matrix3 m1(
				1, 2, 3,
				4, 5, 6,
				7, 8, 9);
			Matrix3 m2;
			Matrix3 m3;
			m3 = m2 = m1;

			Assert::IsTrue(m1 == m2);
			Assert::IsTrue(m1 == m3);

		}

		TEST_METHOD(identity)
		{
			Matrix3 expect(
				1, 0, 0,
				0, 1, 0,
				0, 0, 1);
			Assert::IsTrue(expect == Matrix3::Identity());
		}

		TEST_METHOD(orthographicProjection)
		{
			Matrix3 expect(
				1, 0, 0,
				0, 1, 0,
				0, 0, 0);
			Matrix3 result = Matrix3::OrthographicProjection();
			Assert::IsTrue(expect == result);
		}

		TEST_METHOD(setupRotation)
		{
			Matrix3 m = Matrix3::SetupRotation(JMath::DegreeToRadians(0));
			Matrix3 expected(
				1, 0, 0,
				0, 1, 0,
				0, 0, 1);
			Assert::IsTrue(expected == m);

			float rads = JMath::DegreeToRadians(90);
			m = Matrix3::SetupRotation(rads);
			expected = Matrix3(
				cos(rads), -sin(rads), 0,
				sin(rads), cos(rads), 0,
				0, 0, 1);
			Assert::IsTrue(expected == m);

			rads = JMath::DegreeToRadians(-90);
			m = Matrix3::SetupRotation(rads);
			expected = Matrix3(
				cos(rads), -sin(rads), 0,
				sin(rads), cos(rads), 0,
				0, 0, 1);
			Assert::IsTrue(expected == m);
		}

		TEST_METHOD(setupScale)
		{
			Matrix3 m = Matrix3::SetupScale(Vector2(5, 10));
			Matrix3 expect(
				5, 0, 0,
				0, 10, 0,
				0, 0, 1);
			Assert::IsTrue(m == expect);

			m = Matrix3::SetupScale(Vector2(.25, .5));
			expect = Matrix3(
				.25, 0, 0,
				0, .50, 0,
				0, 0, 1);
			Assert::IsTrue(m == expect);
		}

		TEST_METHOD(setupTranslation)
		{
			Matrix3 m = Matrix3::SetupTranslation(Vector2(2, 5));
			Matrix3 expect(
				1, 0, 2,
				0, 1, 5,
				0, 0, 1);
			Assert::IsTrue(expect == m);

			m = Matrix3::SetupTranslation(Vector2(5, -1));
			expect = Matrix3(
				1, 0, 5,
				0, 1, -1,
				0, 0, 1);
			Assert::IsTrue(expect == m);
		}

		TEST_METHOD(additionOperator)
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

			Assert::IsTrue(expect == result);
			Assert::IsTrue(m1 == Matrix3(
				1, 2, 3,
				4, 5, 6,
				7, 8, 9));
			Assert::IsTrue(m2 == Matrix3(
				9, 8, 7,
				6, 5, 4,
				3, 2, 1));

			//verify chaining 
			result = m1 + m2 + result;
			expect = Matrix3(
				20, 20, 20,
				20, 20, 20,
				20, 20, 20);

			Assert::IsTrue(expect == result);
			Assert::IsTrue(m1 == Matrix3(
				1, 2, 3,
				4, 5, 6,
				7, 8, 9));
			Assert::IsTrue(m2 == Matrix3(
				9, 8, 7,
				6, 5, 4,
				3, 2, 1));
		}

		TEST_METHOD(subtractOperator)
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
			Assert::IsTrue(expect == result);
			Assert::IsTrue(m1 == Matrix3(
				1, 2, 3,
				4, 5, 6,
				7, 8, 9));
			Assert::IsTrue(m2 == Matrix3(
				9, 8, 7,
				6, 5, 4,
				3, 2, 1));

			//verify chaining 
			result = m2 - m1 - m1;
			expect = Matrix3(
				7, 4, 1,
				-2, -5, -8,
				-11, -14, -17);

			Assert::IsTrue(expect == result);
			Assert::IsTrue(m1 == Matrix3(
				1, 2, 3,
				4, 5, 6,
				7, 8, 9));
			Assert::IsTrue(m2 == Matrix3(
				9, 8, 7,
				6, 5, 4,
				3, 2, 1));
		}

		TEST_METHOD(productOperator)
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

			Assert::IsTrue(expect == m3);
			Assert::IsTrue(m1 == Matrix3(
				0, 1, 2,
				3, 4, 5,
				6, 7, 8));
			Assert::IsTrue(m2 == Matrix3(
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

			Assert::IsTrue(expect == m3);
			Assert::IsTrue(m1 == Matrix3(
				9, 6, 3,
				8, 5, 2,
				7, 4, 1));
			Assert::IsTrue(m2 == Matrix3(
				1, 2, 3,
				4, 5, 6,
				7, 8, 9));

			//verify multiply identity equals same matrix
			Assert::IsTrue(m3 == (m3 = m3 * Matrix3::Identity()));

			//verify chaining
			expect = Matrix3(
				54, 72, 90,
				42, 57, 72,
				30, 42, 54);
			m3 = m1 * m2 * Matrix3::Identity();
			Assert::IsTrue(expect == m3);
			Assert::IsTrue(m1 == Matrix3(
				9, 6, 3,
				8, 5, 2,
				7, 4, 1));
			Assert::IsTrue(m2 == Matrix3(
				1, 2, 3,
				4, 5, 6,
				7, 8, 9));
		}
		
		TEST_METHOD(transform)
		{
			Matrix3 m(
				3, 12, 3,
				7, 10, 4,
				0, 0, 1);
			Vector2 v(8, 7);
			Vector2 result = m.Transform(v);
			Vector2 expected(111, 130);

			Assert::IsTrue(expected == result);
			Assert::IsTrue(v == Vector2(8, 7));
			Assert::IsTrue(m == Matrix3(
				3, 12, 3,
				7, 10, 4,
				0, 0, 1));

			Assert::IsTrue(v == (Matrix3::Identity().Transform(v)));
		}

		TEST_METHOD(productOperatorVector3)
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

			Assert::IsTrue(expected == result);
			Assert::IsTrue(v == Vector3(8, 7, 2));
			Assert::IsTrue(m == Matrix3(
				3, 12, 6,
				7, 10, 4,
				5, 2, 9));

			Assert::IsTrue(v == (Matrix3::Identity() * v));
		}
		
		TEST_METHOD(productOperatorVector2)
		{
			Matrix3 m(
				3, 12, 6,
				7, 10, 4,
				5, 2, 9);
			Vector2 v(
				8,
				7);
			Vector2 result = m * v;
			Vector2 expected(
				114,
				130);

			Assert::IsTrue(expected == result);
			Assert::IsTrue(v == Vector2(8, 7));
			Assert::IsTrue(m == Matrix3(
				3, 12, 6,
				7, 10, 4,
				5, 2, 9));

			Assert::IsTrue(v == (Matrix3::Identity() * v));
		}
/**/
		
		TEST_METHOD(additionAssignemntOperator)
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
			Assert::IsTrue(expect == (m1 += m2));
			Assert::IsTrue(m2 ==
				Matrix3(
					9, 8, 7,
					6, 5, 4,
					3, 2, 1));
		}

		TEST_METHOD(subtractAssignemntOperator)
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
			Assert::IsTrue(expect == (m1 -= m2));
			Assert::IsTrue(m2 ==
				Matrix3(
					9, 8, 7,
					6, 5, 4,
					3, 2, 1));
		}

		TEST_METHOD(productAssignemntOperator)
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

			Assert::IsTrue(expect == m1);
			Assert::IsTrue(m2 == Matrix3(
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

			Assert::IsTrue(expect == m1);
			Assert::IsTrue(m2 == Matrix3(
				1, 2, 3,
				4, 5, 6,
				7, 8, 9));

			//verify multiply identity equals same matrix
			Assert::IsTrue(m2 == (m2 *= Matrix3::Identity()));
		}

	};

}