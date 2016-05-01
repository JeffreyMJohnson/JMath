#include "CppUnitTest.h"
#include "TheMath.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_static
{
	TEST_CLASS(Test_Vector3)
	{
	public:
		const double DELTA = .00001;
		TEST_METHOD(constructorDefault)
		{
			Vector3 v;
			Assert::AreEqual(static_cast<double>(0), static_cast<double>(v.x), DELTA);
			Assert::AreEqual(static_cast<double>(0), static_cast<double>(v.y), DELTA);
			Assert::AreEqual(static_cast<double>(0), static_cast<double>(v.z), DELTA);
		}

		TEST_METHOD(constructor)
		{
			Vector3 v(1, 2, 3);
			Assert::AreEqual(static_cast<double>(1), static_cast<double>(v.x), DELTA);
			Assert::AreEqual(static_cast<double>(2), static_cast<double>(v.y), DELTA);
			Assert::AreEqual(static_cast<double>(3), static_cast<double>(v.z), DELTA);
		}

		TEST_METHOD(copyConstructor)
		{
			Vector3 v(1, 2, 3);
			Vector3 v2(v);
			Assert::IsTrue(v == v2);
			Assert::IsTrue(v == v);

		}

		//test equality operator so can use to verify future tests
		TEST_METHOD(equalityOperator)
		{
			Vector3 v1(1, 2, 3);
			Vector3 v2(3, 2, 1);
			Vector3 v3(1, 2, 3);

			Assert::IsTrue(v1 == v3);
			Assert::IsTrue(v1 != v2);
			Assert::IsTrue(v1 == v1);
			Assert::IsTrue(v1 == v1);
			Assert::IsTrue(v1 == v3);
			Assert::IsFalse(v1 == v2);

		}

		TEST_METHOD(inEqualityOperator)
		{
			Vector3 v1(1, 2, 3);
			Vector3 v2(3, 2, 1);
			Vector3 v3(1, 2, 3);

			Assert::IsFalse(v1 != v1);
			Assert::IsFalse(v1 != v3);
			Assert::IsTrue(v1 != v2);

		}

		TEST_METHOD(assignmentOperator)
		{
			Vector3 v1(5, 10, 15);
			Vector3 v2 = v1;
			Assert::IsTrue(v2 == v1);

			//change v1 and verify v2 did not change
			v1.x = 10;
			Assert::IsTrue(v1 == Vector3(10, 10, 15));
			Assert::IsTrue(v2 == Vector3(5, 10, 15));

			//chaining
			v1 = v2 = Vector3();
			Assert::IsTrue(Vector3() == v1);
			Assert::IsTrue(Vector3() == v2);
		}

		TEST_METHOD(additionOperator)
		{

			Vector3 v1(10, 10, 10);
			Vector3 v2(5, 5, 5);
			Vector3 v3 = v1 + v2;

			Assert::IsTrue(v1 == Vector3(10, 10, 10));
			Assert::IsTrue(v2 == Vector3(5, 5, 5));
			Assert::IsTrue(v3 == Vector3(15, 15, 15));

			//verify chaining
			v3 = v1 + v2 + v3;
			Assert::IsTrue(v3 == Vector3(30, 30, 30));
			Assert::IsTrue(v1 == Vector3(10, 10, 10));
			Assert::IsTrue(v2 == Vector3(5, 5, 5));
		}

		TEST_METHOD(additionAssignmentOperator)
		{
			Vector3 v1(5, 5, 5);
			Vector3 v2(10, 10, 10);
			v1 += v2;

			Assert::IsTrue(v1 == Vector3(15, 15, 15));
			Assert::IsTrue(v2 == Vector3(10, 10, 10));

			//chaining
			v1 += v2 += Vector3(-10, -10, -10);
			Assert::IsTrue(Vector3(15, 15, 15) == v1);
			Assert::IsTrue(Vector3() == v2);
		}

		TEST_METHOD(subtractOperator)
		{

			Vector3 v1(10, 10, 10);
			Vector3 v2(5, 5, 5);
			Vector3 v3 = v1 - v2;

			Assert::IsTrue(v1 == Vector3(10, 10, 10));
			Assert::IsTrue(v2 == Vector3(5, 5, 5));
			Assert::IsTrue(v3 == Vector3(5, 5, 5));

			//chaining 
			v3 = v1 - v2 - v2;
			Assert::IsTrue(v1 == Vector3(10, 10, 10));
			Assert::IsTrue(v2 == Vector3(5, 5, 5));
			Assert::IsTrue(v3 == Vector3(0, 0, 0));

		}

		TEST_METHOD(subtractAssignmentOperator)
		{
			Vector3 v1(5, 5, 5);
			Vector3 v2(10, 10, 10);
			v1 -= v2;

			Assert::IsTrue(v1 == Vector3(-5, -5, -5));
			Assert::IsTrue(v2 == Vector3(10, 10, 10));

			//chaining
			v1 -= v2 -= Vector3(10, 10, 10);
			Assert::IsTrue(Vector3(-5, -5, -5) == v1);
			Assert::IsTrue(Vector3() == v2);
		}

		TEST_METHOD(multiplyOperator)
		{

			Vector3 v1(10, 10, 10);

			double scalar = 5.0;
			Vector3 v2 = v1 * scalar;

			Assert::IsTrue(v1 == Vector3(10, 10, 10));
			Assert::AreEqual(5.0, scalar, DELTA);
			Assert::IsTrue(v2 == Vector3(50, 50, 50));
		}

		TEST_METHOD(multiplyAssignmentOperator)
		{
			Vector3 v1(5, 5, 5);
			double scalar = 10.0;
			v1 *= scalar;

			Assert::IsTrue(v1 == Vector3(50, 50, 50));
			Assert::AreEqual(10.0, scalar, DELTA);
		}

		TEST_METHOD(bracketOperator)
		{
			Vector3 v(1, 2, 3);
			float r = v[1];
			Assert::AreEqual(static_cast<double>(2), static_cast<double>(r), DELTA);
		}

		TEST_METHOD(negativeUnary)
		{
			Vector3 v(1, 2, 3);

			Assert::IsTrue(Vector3(-1, -2, -3) == -v);
			Assert::IsTrue(Vector3(1, 2, 3) == v);
		}

		TEST_METHOD(bangOperator)
		{
			Vector3 v(1, 2, 3);
			Vector3 v2;

			Assert::IsFalse(!v);
			Assert::IsTrue(!v2);
		}

		TEST_METHOD(equals)
		{
			Vector3 v1(.0009, -.0009, .0009);
			Vector3 v2;

			Assert::IsTrue(v1.Equals(v2, .001));
			Assert::IsFalse(v1.Equals(v2, .0001));
		}

		TEST_METHOD(magnitude)
		{
			Vector3 v1(3, 4, 5);
			//expect sqrt(50)
			Assert::AreEqual(static_cast<double>(7.0710678118654752440084436210485), static_cast<double>(v1.Magnitude()), DELTA);
			Assert::IsTrue(v1 == Vector3(3, 4, 5));

			v1 *= 3;
			Assert::IsTrue(sqrtf(450) == v1.Magnitude());
		}

		TEST_METHOD(normalize)
		{
			Vector3 v(30, 40, 50);
			v.Normalize();
			//magnitude = sqrt(5000)
			Assert::AreEqual(static_cast<double>(0.42426406871192851464050661726291), static_cast<double>(v.x), DELTA);
			Assert::AreEqual(static_cast<double>(0.56568542494923801952067548968388), static_cast<double>(v.y), DELTA);
			Assert::AreEqual(static_cast<double>(0.70710678118654752440084436210485), static_cast<double>(v.z), DELTA);

			Vector3 v2;
			v2.Normalize();
			//divide by zero check
			Assert::IsTrue(v2 == Vector3());
		}

		TEST_METHOD(getNormal)
		{
			Vector3 v(30, 40, 50);
			Vector3 v2 = v.GetNormal();

			//magnitude = sqrt(5000)
			Assert::AreEqual(static_cast<double>(0.42426406871192851464050661726291), static_cast<double>(v2.x), DELTA);
			Assert::AreEqual(static_cast<double>(0.56568542494923801952067548968388), static_cast<double>(v2.y), DELTA);
			Assert::AreEqual(static_cast<double>(0.70710678118654752440084436210485), static_cast<double>(v2.z), DELTA);
			Assert::IsTrue(v == Vector3(30, 40, 50));

			//divide by zero check
			v = Vector3();
			v2 = v.GetNormal() = Vector3();
			Assert::IsTrue(Vector3() == v2);
		}

		TEST_METHOD(dotProduct)
		{
			Vector3 v1(5, 2, 15);
			Vector3 v2(-10, 4, -100);
			Assert::AreEqual(static_cast<double>(-1542), static_cast<double>(v1.DotProduct(v2)), DELTA);
			Assert::IsTrue(v1 == Vector3(5, 2, 15));
			Assert::IsTrue(v2 == Vector3(-10, 4, -100));
		}

		TEST_METHOD(crossProduct)
		{
			Vector3 v1(3, 4, 5);
			Vector3 v2(6, 7, 8);

			Vector3 xProd = v1.CrossProduct(v2);

			Assert::IsTrue(xProd == Vector3(-3, 6, -3));

			v1 = Vector3(10, 0, 0);
			v2 = Vector3(0, 10, 0);
			xProd = v1.CrossProduct(v2);

			Assert::IsTrue(xProd == Vector3(0, 0, 100));
		}

		TEST_METHOD(getLERP)
		{
			float percent = 0;
			Vector3 start(0, 0, 0);
			Vector3 end(5, 5, 5);
			Vector3 result = start.GetLERP(end, percent);

			Assert::IsTrue(start == result);
			Assert::IsTrue(&start != &result);
			percent = 1;
			result = start.GetLERP(end, percent);
			Assert::IsTrue(end == result);
			Assert::IsTrue(&start != &result);
			percent = .5;
			result = start.GetLERP(end, percent);
			Assert::IsTrue(Vector3(2.5, 2.5, 2.5) == result);

			Assert::IsTrue(Vector3() == start);

			Assert::IsTrue(&start != &result);
		}

		TEST_METHOD(lerp_static)
		{
			float percent = 0;
			Vector3 start(0, 0, 0);
			Vector3 end(5, 5, 5);
			Vector3 result = Vector3::LERP(start, end, percent);

			Assert::IsTrue(start == result);
			percent = 1;
			result = Vector3::LERP(start, end, percent);
			Assert::IsTrue(end == result);
			percent = .5;
			result = Vector3::LERP(start, end, percent);
			Assert::IsTrue(Vector3(2.5, 2.5, 2.5) == result);

			Assert::IsTrue(&start != &result);
		}
	};
}