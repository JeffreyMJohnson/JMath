#include "CppUnitTest.h"
#include "TheMath.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_static
{
	TEST_CLASS(Test_Vector2)
	{
	public:
		const double DELTA = .00001;
		TEST_METHOD(constructorDefault)
		{
			Vector2 v;
			Assert::AreEqual(0, static_cast<double>(v.x), DELTA);
			Assert::AreEqual(0, static_cast<double>(v.y), DELTA);
		}

		TEST_METHOD(constructor)
		{
			Vector2 v(1, 2);
			Assert::AreEqual(1, static_cast<double>(v.x), DELTA);
			Assert::AreEqual(2, static_cast<double>(v.y), DELTA);
		}

		TEST_METHOD(copyConstructor)
		{
			Vector2 v(1, 2);
			Vector2 v2(v);
			Assert::IsTrue(v ==v2);
			Assert::IsTrue(v == v);

		}

		//test equality operator so can use to verify future tests
		TEST_METHOD(equalityOperator)
		{
			Vector2 v1(1, 2);
			Vector2 v2(3, 2);
			Vector2 v3(1, 2);

			Assert::IsTrue(v1 == v1);
			Assert::IsTrue(v1 == v3);
			Assert::IsFalse(v1 == v2);

			Assert::IsTrue(v1 == v1);
			Assert::IsTrue(v1 == v3);
			Assert::IsTrue(v1 != v2);

		}

		TEST_METHOD(inEqualityOperator)
		{
			Vector2 v1(1, 2);
			Vector2 v2(3, 2);
			Vector2 v3(1, 2);

			Assert::IsFalse(v1 != v1);
			Assert::IsFalse(v1 != v3);
			Assert::IsTrue(v1 != v2);

		}

		TEST_METHOD(assignmentOperator)
		{
			Vector2 v1(5, 10);
			Vector2 v2 = v1;
			Assert::IsTrue(v2 == v1);

			//change v1 and verify v2 did not change
			v1.x = 10;
			Assert::IsTrue(v1 == Vector2(10, 10));
			Assert::IsTrue(v2 == Vector2(5, 10));

			//verify chaining is possible a=b=c
			Vector2 v3 = v2 = v1;

			Assert::IsTrue(v1 == Vector2(10, 10));
			Assert::IsTrue(v2 == Vector2(10, 10));
			Assert::IsTrue(v3 == Vector2(10, 10));
		}

		TEST_METHOD(additionOperator)
		{

			Vector2 v1(10, 10);
			Vector2 v2(5, 5);
			Vector2 v3 = v1 + v2;

			Assert::IsTrue(v1 == Vector2(10, 10));
			Assert::IsTrue(v2 == Vector2(5, 5));
			Assert::IsTrue(v3 == Vector2(15, 15));

			//chaining
			v3 = v1 + v1 + v2;
			Assert::IsTrue(v1 == Vector2(10, 10));
			Assert::IsTrue(v2 == Vector2(5, 5));
			Assert::IsTrue(v3 == Vector2(25, 25));
		}

		TEST_METHOD(additionAssignmentOperator)
		{
			Vector2 v1(5, 5);
			Vector2 v2(10, 10);
			v1 += v2;

			Assert::IsTrue(v1 == Vector2(15, 15));
			Assert::IsTrue(v2 == Vector2(10, 10));

			//verify chaining is doable for crazy people
			(v2 += Vector2(1, 1)) += Vector2(4, 4);

			Assert::IsTrue(v2 == Vector2(15, 15));
		}

		TEST_METHOD(subtractOperator)
		{

			Vector2 v1(10, 10);
			Vector2 v2(5, 5);
			Vector2 v3 = v1 - v2;

			Assert::IsTrue(v1 == Vector2(10, 10));
			Assert::IsTrue(v2 == Vector2(5, 5));
			Assert::IsTrue(v3 == Vector2(5, 5));

			//chaining
			v3 = v1 - v2 - v2;
			Assert::IsTrue(v1 == Vector2(10, 10));
			Assert::IsTrue(v2 == Vector2(5, 5));
			Assert::IsTrue(v3 == Vector2(0, 0));

		}

		TEST_METHOD(subtractAssignmentOperator)
		{
			Vector2 v1(5, 5);
			Vector2 v2(10, 10);
			v1 -= v2;

			Assert::IsTrue(v1 == Vector2(-5, -5));
			Assert::IsTrue(v2 == Vector2(10, 10));

			//chaining
			v1 = Vector2(5, 5);
			v1 -= v2 -= v2;
			Assert::IsTrue(Vector2(5, 5) == v1);
			Assert::IsTrue(Vector2() == v2);
		}

		TEST_METHOD(negativeUnaryOperator)
		{
			Vector2 v(1, 2);
			Assert::IsTrue(Vector2(1, 2) == v);
			Assert::IsTrue(Vector2(-1, -2) == -v);

		}

		TEST_METHOD(bangOperator)
		{
			Vector2 v(1, 2);
			Vector2 v2;

			Assert::IsFalse(!v);
			Assert::IsTrue(!v2);
		}

		TEST_METHOD(multiplyOperator)
		{
			Vector2 v1(10, 10);

			double scalar = 5.0;
			Vector2 v2 = v1 * scalar;

			Assert::IsTrue(v1 == Vector2(10, 10));
			Assert::AreEqual(5.0, scalar, DELTA);
			Assert::IsTrue(v2 == Vector2(50, 50));

			v1 = Vector2(5, 5);
			v2 = scalar * v1;
			Assert::IsTrue(Vector2(25, 25) == v2);
		}

		TEST_METHOD(multiplyAssignmentOperator)
		{
			Vector2 v1(5, 5);
			float scalar = 10.0f;
			v1 *= scalar;

			Assert::IsTrue(v1 == Vector2(50, 50));
		}

		TEST_METHOD(equals)
		{
			Vector2 v1(.0009, -.0009);
			Vector2 v2;

			Assert::IsTrue(v1.Equals(v2, .001));
			Assert::IsFalse(v1.Equals(v2, .0001));
		}

		TEST_METHOD(magnitude)
		{
			Vector2 v1(3, 4);
			Assert::AreEqual(5.0, static_cast<double>(v1.Magnitude()), DELTA);
			Assert::IsTrue(v1 == Vector2(3, 4));

			v1 *= 3;
			Assert::IsTrue(15.0f == v1.Magnitude());
		}

		TEST_METHOD(normalize)
		{
			Vector2 v(30, 40);
			v.Normalize();
			Assert::AreEqual(.6, static_cast<double>(v.x), DELTA);
			Assert::AreEqual(.8, static_cast<double>(v.y), DELTA);

			//divide by zero check
			v = Vector2();
			v.Normalize();
			Assert::IsTrue(Vector2() == v);
		}

		TEST_METHOD(getNormal)
		{
			Vector2 v(30, 40);
			Vector2 v2 = v.GetNormal();

			Assert::AreEqual(.6, static_cast<double>(v2.x), DELTA);
			Assert::AreEqual(.8, static_cast<double>(v2.y), DELTA);
			Assert::IsTrue(v == Vector2(30, 40));

			//divide by zero check
			v = Vector2();
			v2 = v.GetNormal() = Vector2();
			Assert::IsTrue(Vector2() == v2);
		}

		TEST_METHOD(dotProduct)
		{
			Vector2 v1(5, 2);
			Vector2 v2(-10, 4);
			Assert::AreEqual(-42, static_cast<double>(v1.DotProduct(v2)), DELTA);
			Assert::IsTrue(v1 == Vector2(5, 2));
			Assert::IsTrue(v2 == Vector2(-10, 4));
		}

		TEST_METHOD(getPerp)
		{
			Vector2 v(10, 100);
			Vector2 perp = v.GetPerp();

			Assert::IsTrue(v == Vector2(10, 100));
			Assert::IsTrue(perp == Vector2(100, -10));

			v = Vector2(4, 6);
			perp = v.GetPerp();
			Assert::IsTrue(v == Vector2(4, 6));
			Assert::IsTrue(perp == Vector2(6, -4));

		}

		TEST_METHOD(getLERP)
		{
			float percent = 0;
			Vector2 start(0, 0);
			Vector2 end(5, 5);
			Vector2 result = start.GetLERP(end, percent);

			Assert::IsTrue(start == result);
			percent = 1;
			result = start.GetLERP(end, percent);
			Assert::IsTrue(end == result);
			percent = .5;
			result = start.GetLERP(end, percent);
			Assert::IsTrue(Vector2(2.5, 2.5) == result);

		}

		TEST_METHOD(getQuadBezier)
		{
			Vector2 start(1, 1);
			Vector2 mid(1.5, 4.5);
			Vector2 end(4, 2);
			Vector2 r = start.GetQuadBezier(mid, end, .5f);
			Assert::IsTrue(Vector2(2, 3) == r);
		}

		TEST_METHOD(lerp_static)
		{
			float percent = 0;
			Vector2 start(0, 0);
			Vector2 end(5, 5);
			Vector2 result = Vector2::LERP(start, end, percent);

			Assert::IsTrue(start == result);
			percent = 1;

			result = Vector2::LERP(start, end, percent);
			Assert::IsTrue(end == result);

			percent = .5;
			result = Vector2::LERP(start, end, percent);
			Assert::IsTrue(Vector2(2.5, 2.5) == result);
		}

		TEST_METHOD(q_bez_static)
		{
			Vector2 start(1, 1);
			Vector2 mid(1.5, 4.5);
			Vector2 end(4, 2);
			Vector2 r = Vector2::QuadBezier(start, mid, end, .5f);
			Assert::IsTrue(Vector2(2, 3) == r);

		}

		TEST_METHOD(cub_bezier_static)
		{
			Vector2 p0;
			Vector2 p1(3, 5);
			Vector2 p2(7, 4);
			Vector2 p3(20, 1);
			float t = .5f;

			//Vector2 l0 = Vector2::LERP(p0, p1, t);
			//Vector2 l1 = Vector2::LERP(p1, p2, t);
			//Vector2 l2 = Vector2::LERP(p2, p3, t);
			//EXPECT_TRUE(false) << "l0: " << l0 << "\nl1: " << l1 << "\nl2: " << l2 << "\n";

			//Vector2 l3 = Vector2::LERP(l0, l1, t);
			//Vector2 l4 = Vector2::LERP(l1, l2, t);
			//EXPECT_TRUE(false) << "l3: " << l3 << "\nl4: " << l4 << "\n";

			//Vector2 l5 = Vector2::LERP(l3, l4, t);
			//EXPECT_TRUE(false) << "l5: " << l5 << "\n";

			Vector2 expected(6.25, 3.5);
			Vector2 r = Vector2::CubicBezier(p0, p1, p2, p3, t);
			Assert::IsTrue(expected == r);

			r = Vector2::CubicBezier(p0, p1, p2, p3, 1.0f);
			Assert::IsTrue(Vector2(20, 1) == r);

		}
	};
}