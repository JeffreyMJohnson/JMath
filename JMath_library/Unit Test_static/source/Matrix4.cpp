#include "CppUnitTest.h"
#include "TheMath.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_static
{
	TEST_CLASS(Test_Matrix4)
	{
	public:
		const double DELTA = .00001;
		TEST_METHOD(constructorDefault)
		{
			Matrix4 m;

			for (int row = 0; row < 4; row++)
			{
				for (int col = 0; col < 4; col++)
				{
					Assert::AreEqual(0, static_cast<double>(m.matrix[row][col]), DELTA);
				}
			}
		}

		TEST_METHOD(constructor)
		{
			Matrix4 m(
				10, 11, 12, 13,
				20, 21, 22, 23,
				30, 31, 32, 33,
				40, 41, 42, 43);

			Assert::AreEqual(10, static_cast<double>(m.matrix[0][0]), DELTA);
			Assert::AreEqual(11, static_cast<double>(m.matrix[0][1]), DELTA);
			Assert::AreEqual(12, static_cast<double>(m.matrix[0][2]), DELTA);
			Assert::AreEqual(13, static_cast<double>(m.matrix[0][3]), DELTA);
			Assert::AreEqual(20, static_cast<double>(m.matrix[1][0]), DELTA);
			Assert::AreEqual(21, static_cast<double>(m.matrix[1][1]), DELTA);
			Assert::AreEqual(22, static_cast<double>(m.matrix[1][2]), DELTA);
			Assert::AreEqual(23, static_cast<double>(m.matrix[1][3]), DELTA);
			Assert::AreEqual(30, static_cast<double>(m.matrix[2][0]), DELTA);
			Assert::AreEqual(31, static_cast<double>(m.matrix[2][1]), DELTA);
			Assert::AreEqual(32, static_cast<double>(m.matrix[2][2]), DELTA);
			Assert::AreEqual(33, static_cast<double>(m.matrix[2][3]), DELTA);
			Assert::AreEqual(40, static_cast<double>(m.matrix[3][0]), DELTA);
			Assert::AreEqual(41, static_cast<double>(m.matrix[3][1]), DELTA);
			Assert::AreEqual(42, static_cast<double>(m.matrix[3][2]), DELTA);
			Assert::AreEqual(43, static_cast<double>(m.matrix[3][3]), DELTA);

		}

		TEST_METHOD(copyConstructor)
		{
			Matrix4 m(
				1, 2, 3, 4,
				5, 6, 7, 8,
				9, 10, 11, 12,
				13, 14, 15, 16);

			Matrix4 m2(m);

			Assert::IsTrue(m2 == m);
			//verify copy not same object
			Assert::IsFalse(&m2 == &m);
		}

		TEST_METHOD(get)
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
				Assert::AreEqual(static_cast<double>(m2[i]), static_cast<double>(m3[i]), DELTA);
			}


		}

		TEST_METHOD(equality)
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

			Assert::IsTrue(m1 == m2);
			Assert::IsTrue(m1 == m1);
			Assert::IsFalse(m1 == m3);

		}

		TEST_METHOD(inEquality)
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

			Assert::IsTrue(m1 != m3);
			Assert::IsTrue(m2 != m3);
			Assert::IsFalse(m1 != m2);

		}

		TEST_METHOD(assignmentOperator)
		{
			Matrix4 m1(
				1, 2, 3, 4,
				5, 6, 7, 8,
				9, 10, 11, 12,
				13, 14, 15, 16);
			Matrix4 m2;
			Matrix4 m3;
			m3 = m2 = m1;

			Assert::IsTrue(m1 == m2);
			Assert::IsTrue(m1 == m3);
			Assert::IsFalse(&m1 == &m2);

		}

		TEST_METHOD(additionAssignemntOperator)
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
			Assert::IsTrue(expect == (m1 += m2));
			Assert::IsTrue(m2 ==
				Matrix4(
					16, 15, 14, 13,
					12, 11, 10, 9,
					8, 7, 6, 5,
					4, 3, 2, 1));
		}

		TEST_METHOD(subtractAssignemntOperator)
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
			Assert::IsTrue(expect == (m1 -= m2));
			Assert::IsTrue(m2 ==
				Matrix4(
					16, 15, 14, 13,
					12, 11, 10, 9,
					8, 7, 6, 5,
					4, 3, 2, 1));
		}

		TEST_METHOD(getVector4FromMatrix)
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
			Assert::IsTrue(result == Vector4(0, 1, 2, 3));

			result = Matrix4::GetVector4(majorType, 1, mRow);
			Assert::IsTrue(result == Vector4(4, 5, 6, 7));

			result = Matrix4::GetVector4(majorType, 2, mRow);
			Assert::IsTrue(result == Vector4(8, 9, 10, 11));

			majorType = COL;
			result = Matrix4::GetVector4(majorType, 0, mCol);
			Assert::IsTrue(result == Vector4(0, 1, 2, 3));

			result = Matrix4::GetVector4(majorType, 1, mCol);
			Assert::IsTrue(result == Vector4(4, 5, 6, 7));

			result = Matrix4::GetVector4(majorType, 2, mCol);
			Assert::IsTrue(result == Vector4(8, 9, 10, 11));


		}

		TEST_METHOD(productAssignemntOperator)
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

			//Assert::AreEqual(15, static_cast<double>(m1.matrix[0][0]), DELTA);
			//Assert::AreEqual(18, static_cast<double>(m1.matrix[0][1]), DELTA);
			//Assert::AreEqual(21, static_cast<double>(m1.matrix[0][2]), DELTA);
			//Assert::AreEqual(42, static_cast<double>(m1.matrix[1][0]), DELTA);
			//Assert::AreEqual(54, static_cast<double>(m1.matrix[1][1]), DELTA);
			//Assert::AreEqual(66, static_cast<double>(m1.matrix[1][2]), DELTA);
			//Assert::AreEqual(69, static_cast<double>(m1.matrix[2][0]), DELTA);
			//Assert::AreEqual(90, static_cast<double>(m1.matrix[2][1]), DELTA);
			//Assert::AreEqual(111, static_cast<double>(m1.matrix[2][2]), DELTA);

			Assert::IsTrue(expect == m1);
			Assert::IsTrue(Matrix4(
				0, 1, 2, 0,
				4, 5, 6, 0,
				8, 9, 10, 0,
				0, 0, 0, 1) == m2);

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

			Assert::IsTrue(expect == m1);
			Assert::IsTrue(Matrix4(
				12, -25, -98, 0,
				45, 369, 7, 0,
				98, -5, 180, 0,
				0, 0, 0, 1) == m2);

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

			Assert::IsTrue(expect == m1);

			//Assert::AreEqual(54, static_cast<double>(m1.matrix[0][0]), DELTA);
			//Assert::AreEqual(72, static_cast<double>(m1.matrix[0][1]), DELTA);
			//Assert::AreEqual(90, static_cast<double>(m1.matrix[0][2]), DELTA);
			//Assert::AreEqual(42, static_cast<double>(m1.matrix[1][0]), DELTA);
			//Assert::AreEqual(57, static_cast<double>(m1.matrix[1][1]), DELTA);
			//Assert::AreEqual(72, static_cast<double>(m1.matrix[1][2]), DELTA);
			//Assert::AreEqual(30, static_cast<double>(m1.matrix[2][0]), DELTA);
			//Assert::AreEqual(42, static_cast<double>(m1.matrix[2][1]), DELTA);
			//Assert::AreEqual(54, static_cast<double>(m1.matrix[2][2]), DELTA);

			//verify multiply identity equals same matrix
			Assert::IsTrue(m2 == (m2 *= Matrix4::Identity()));
		}

		TEST_METHOD(identity)
		{
			Matrix4 expect(
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);
			Assert::IsTrue(expect == Matrix4::Identity());
		}

		TEST_METHOD(orthographicProjection)
		{
			Matrix4 result = Matrix4::GetOrthographicProjection(0, 100, 100, 0, -10, 100);

			Assert::AreEqual(.02, static_cast<double>(result.matrix[0][0]), DELTA);
			Assert::AreEqual(0, static_cast<double>(result.matrix[0][1]), DELTA);
			Assert::AreEqual(0, static_cast<double>(result.matrix[0][2]), DELTA);
			Assert::AreEqual(-1, static_cast<double>(result.matrix[0][3]), DELTA);
			Assert::AreEqual(0, static_cast<double>(result.matrix[1][0]), DELTA);
			Assert::AreEqual(.02, static_cast<double>(result.matrix[1][1]), DELTA);
			Assert::AreEqual(0, static_cast<double>(result.matrix[1][2]), DELTA);
			Assert::AreEqual(-1, static_cast<double>(result.matrix[1][3]), DELTA);
			Assert::AreEqual(0, static_cast<double>(result.matrix[2][0]), DELTA);
			Assert::AreEqual(0, static_cast<double>(result.matrix[2][1]), DELTA);
			Assert::AreEqual(-2.0 / 110, static_cast<double>(result.matrix[2][2]), DELTA);
			Assert::AreEqual(-90.0 / 110.0, static_cast<double>(result.matrix[2][3]), DELTA);
			Assert::AreEqual(0, static_cast<double>(result.matrix[3][0]), DELTA);
			Assert::AreEqual(0, static_cast<double>(result.matrix[3][1]), DELTA);
			Assert::AreEqual(0, static_cast<double>(result.matrix[3][2]), DELTA);
			Assert::AreEqual(1, static_cast<double>(result.matrix[3][3]), DELTA);
		}

		TEST_METHOD(transform)
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

			Assert::IsTrue(expected == result);
			Assert::IsTrue(v == Vector3(8, 7, 2));
			Assert::IsTrue(m == Matrix4(
				3, 12, 6, 0,
				7, 10, 4, 0,
				5, 2, 9, 0,
				0, 0, 0, 1));

			Assert::IsTrue(v == (Matrix4::Identity().Transform(v)));
		}

		TEST_METHOD(productOperatorVector4)
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

			Assert::IsTrue(expected == result);
			Assert::IsTrue(v == Vector4(8, 7, 2, 1));
			Assert::IsTrue(m == Matrix4(
				3, 12, 6, 2,
				7, 10, 4, -3,
				5, 2, 9, 3,
				0, 0, 0, 1));

			Assert::IsTrue(v == (Matrix4::Identity() * v));
		}

		TEST_METHOD(productOperator)
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

			Assert::IsTrue(expect == r);
			Assert::IsTrue(Matrix4(
				0, 1, 2, 0,
				4, 5, 6, 0,
				8, 9, 10, 0,
				0, 0, 0, 1) == m1);
			Assert::IsTrue(Matrix4(
				0, 1, 2, 0,
				4, 5, 6, 0,
				8, 9, 10, 0,
				0, 0, 0, 1) == m2);

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

			Assert::IsTrue(expect == r);
			Assert::IsTrue(Matrix4(
				320, -8, 58, 0,
				45, 26, -369, 0,
				65, 14, -65, 0,
				0, 0, 0, 1) == m1);
			Assert::IsTrue(Matrix4(
				12, -25, -98, 0,
				45, 369, 7, 0,
				98, -5, 180, 0,
				0, 0, 0, 1) == m2);

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

			Assert::IsTrue(expect == r);

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

			Assert::IsTrue(expect == r);

			//verify multiply identity equals same matrix
			Assert::IsTrue(r == (r = m2 * Matrix4::Identity()));
		}

		TEST_METHOD(subtractOperator)
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
			Assert::IsTrue(expect == result);
			Assert::IsTrue(m1 == Matrix4(
				1, 2, 3, 4,
				4, 5, 6, 3,
				7, 8, 9, 2,
				1, 2, 3, 4));
			Assert::IsTrue(m2 == Matrix4(
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

			Assert::IsTrue(expect == result);
			Assert::IsTrue(m1 == Matrix4(
				1, 2, 3, 4,
				4, 5, 6, 3,
				7, 8, 9, 2,
				1, 2, 3, 4));
			Assert::IsTrue(m2 == Matrix4(
				9, 8, 7, 2,
				6, 5, 4, 3,
				3, 2, 1, -3,
				0, 0, 2, 1));
		}

		TEST_METHOD(additionOperator)
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

			Assert::IsTrue(expect == result);
			Assert::IsTrue(m1 == Matrix4(
				1, 2, 3, 4,
				4, 5, 6, 3,
				7, 8, 9, 2,
				1, 2, 3, 4));
			Assert::IsTrue(m2 == Matrix4(
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

			Assert::IsTrue(expect == result);
			Assert::IsTrue(m1 == Matrix4(
				1, 2, 3, 4,
				4, 5, 6, 3,
				7, 8, 9, 2,
				1, 2, 3, 4));
			Assert::IsTrue(m2 == Matrix4(
				9, 8, 7, 2,
				6, 5, 4, 3,
				3, 2, 1, -3,
				0, 0, 2, 1));
		}

		TEST_METHOD(setupRotationIndividualAxis)
		{
			Matrix4 m = Matrix4::SetupRotation(X, JMath::DegreeToRadians(0));
			Matrix4 expected(
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);

			Assert::IsTrue(expected == m);

			m = Matrix4::SetupRotation(Y, JMath::DegreeToRadians(0));
			expected = Matrix4(
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);

			Assert::IsTrue(expected == m);

			m = Matrix4::SetupRotation(Z, JMath::DegreeToRadians(0));
			expected = Matrix4(
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);

			Assert::IsTrue(expected == m);

			float rads = JMath::DegreeToRadians(90);
			m = Matrix4::SetupRotation(X, rads);
			expected = Matrix4(
				1, 0, 0, 0,
				0, cos(rads), -sin(rads), 0,
				0, sin(rads), cos(rads), 0,
				0, 0, 0, 1);
			Assert::IsTrue(expected == m);

			m = Matrix4::SetupRotation(Y, rads);
			expected = Matrix4(
				cos(rads), 0, sin(rads), 0,
				0, 1, 0, 0,
				-sin(rads), 0, cos(rads), 0,
				0, 0, 0, 1);
			Assert::IsTrue(expected == m);

			m = Matrix4::SetupRotation(Z, rads);
			expected = Matrix4(
				cos(rads), -sin(rads), 0, 0,
				sin(rads), cos(rads), 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);
			Assert::IsTrue(expected == m);

			rads = JMath::DegreeToRadians(-90);
			m = Matrix4::SetupRotation(X, rads);
			expected = Matrix4(
				1, 0, 0, 0,
				0, cos(rads), -sin(rads), 0,
				0, sin(rads), cos(rads), 0,
				0, 0, 0, 1);
			Assert::IsTrue(expected == m);
		}

		TEST_METHOD(setupRotationCombinesAxisSingleValue)
		{
			Matrix4 m = Matrix4::SetupRotation(JMath::DegreeToRadians(0));
			Matrix4 expected(
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);

			Assert::IsTrue(expected == m);

			float rads = JMath::DegreeToRadians(90);
			m = Matrix4::SetupRotation(rads);
			expected = Matrix4(
				0, 0, 1, 0,
				0, -1, 0, 0,
				1, 0, 0, 0,
				0, 0, 0, 1);
			double delta = .00001;
			Assert::AreEqual(0, static_cast<double>(m[0][0]), delta);
			Assert::AreEqual(0, static_cast<double>(m[0][1]), delta);
			Assert::AreEqual(1, static_cast<double>(m[0][2]), delta);
			Assert::AreEqual(0, static_cast<double>(m[0][3]), delta);
			Assert::AreEqual(0, static_cast<double>(m[1][0]), delta);
			Assert::AreEqual(-1, static_cast<double>(m[1][1]), delta);
			Assert::AreEqual(0, static_cast<double>(m[1][2]), delta);
			Assert::AreEqual(0, static_cast<double>(m[1][3]), delta);
			Assert::AreEqual(1, static_cast<double>(m[2][0]), delta);
			Assert::AreEqual(0, static_cast<double>(m[2][1]), delta);
			Assert::AreEqual(0, static_cast<double>(m[2][2]), delta);
			Assert::AreEqual(0, static_cast<double>(m[2][3]), delta);
			Assert::AreEqual(0, static_cast<double>(m[3][0]), delta);
			Assert::AreEqual(0, static_cast<double>(m[3][1]), delta);
			Assert::AreEqual(0, static_cast<double>(m[3][2]), delta);
			Assert::AreEqual(1, static_cast<double>(m[3][3]), delta);

		}
		TEST_METHOD(setupRotationCombinesAxisVector3)
		{
			Matrix4 m = Matrix4::SetupRotation(JMath::DegreeToRadians(0));
			Matrix4 expected(
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);

			Assert::IsTrue(expected == m);

			float rads = JMath::DegreeToRadians(90);
			Vector3 angles(rads, rads, rads);
			m = Matrix4::SetupRotation(angles);
			expected = Matrix4(
				0, 0, 1, 0,
				0, -1, 0, 0,
				1, 0, 0, 0,
				0, 0, 0, 1);
			double delta = .00001;
			Assert::AreEqual(0, static_cast<double>(m[0][0]), delta);
			Assert::AreEqual(0, static_cast<double>(m[0][1]), delta);
			Assert::AreEqual(1, static_cast<double>(m[0][2]), delta);
			Assert::AreEqual(0, static_cast<double>(m[0][3]), delta);
			Assert::AreEqual(0, static_cast<double>(m[1][0]), delta);
			Assert::AreEqual(-1, static_cast<double>(m[1][1]), delta);
			Assert::AreEqual(0, static_cast<double>(m[1][2]), delta);
			Assert::AreEqual(0, static_cast<double>(m[1][3]), delta);
			Assert::AreEqual(1, static_cast<double>(m[2][0]), delta);
			Assert::AreEqual(0, static_cast<double>(m[2][1]), delta);
			Assert::AreEqual(0, static_cast<double>(m[2][2]), delta);
			Assert::AreEqual(0, static_cast<double>(m[2][3]), delta);
			Assert::AreEqual(0, static_cast<double>(m[3][0]), delta);
			Assert::AreEqual(0, static_cast<double>(m[3][1]), delta);
			Assert::AreEqual(0, static_cast<double>(m[3][2]), delta);
			Assert::AreEqual(1, static_cast<double>(m[3][3]), delta);

			rads = JMath::DegreeToRadians(-90);
			angles.y = angles.z = 0;
			angles.x = rads;
			m = Matrix4::SetupRotation(angles);
			expected = Matrix4(
				1, 0, 0, 0,
				0, cos(rads), -sin(rads), 0,
				0, sin(rads), cos(rads), 0,
				0, 0, 0, 1);
			Assert::IsTrue(expected == m);

		}

		TEST_METHOD(setupScale)
		{
			Matrix4 m = Matrix4::SetupScale(Vector3(5, 10, 2));
			Matrix4 expect(
				5, 0, 0, 0,
				0, 10, 0, 0,
				0, 0, 2, 0,
				0, 0, 0, 1);
			Assert::IsTrue(expect == m);

			m = Matrix4::SetupScale(Vector3(.25, .5, .2));
			expect = Matrix4(
				.25, 0, 0, 0,
				0, .50, 0, 0,
				0, 0, .2, 0,
				0, 0, 0, 1);
			Assert::IsTrue(expect == m);
		}

		TEST_METHOD(setupTranslation)
		{
			Matrix4 m = Matrix4::SetupTranslation(Vector3(2, 5, -2));
			Matrix4 expect(
				1, 0, 0, 2,
				0, 1, 0, 5,
				0, 0, 1, -2,
				0, 0, 0, 1);
			Assert::IsTrue(expect == m);

			m = Matrix4::SetupTranslation(Vector3(5, -1, 43));
			expect = Matrix4(
				1, 0, 0, 5,
				0, 1, 0, -1,
				0, 0, 1, 43,
				0, 0, 0, 1);
			Assert::IsTrue(expect == m);
		}

		TEST_METHOD(bracketOperator)
		{
			Matrix4 m(
				1, 2, 3, 4,
				4, 5, 6, 5,
				7, 8, 9, 6,
				7, 8, 9, 10);

			float* v = m[2];
			float f = v[2];

			Assert::IsTrue(9 == f);

			f = m[3][2];
			Assert::IsTrue(9 == f);
		}

		TEST_METHOD(transpose)
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
			Assert::IsTrue(expected == m);

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

			Assert::IsTrue(expected == m);
		}

		TEST_METHOD(getTranspose)
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
			Assert::IsTrue(expected == r);
			Assert::IsTrue(Matrix4(
				1, 5, 6, 7,
				2, 7, 8, 6,
				2, 7, 5, -2,
				23, 4, 3, 65) == m);

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

			Assert::IsTrue(expected == r);
			Assert::IsTrue(Matrix4(
				6, 4, 8, 12,
				3, 1, 2, 21,
				3, 9, 5, -76,
				87, 7, 4, 0) == m);
		}

	};
}
