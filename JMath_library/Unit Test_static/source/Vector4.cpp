#include "CppUnitTest.h"
#include "TheMath.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_static
{
	TEST_CLASS(Test_Vector4)
	{
	public:
		const double DELTA = .00001;
		TEST_METHOD(constructorDefault)
		{
			Vector4 v;
			Assert::AreEqual(static_cast<double>(0), static_cast<double>(v.x), DELTA);
			Assert::AreEqual(static_cast<double>(0), static_cast<double>(v.y), DELTA);
			Assert::AreEqual(static_cast<double>(0), static_cast<double>(v.z), DELTA);
			Assert::AreEqual(static_cast<double>(0), static_cast<double>(v.w), DELTA);
		}

		TEST_METHOD(constructorFloats)
		{
			Vector4 v(1.3f, 2.5f, -5.0f, -3.14159f);
			Assert::AreEqual(static_cast<double>(1.3f), static_cast<double>(v.x), DELTA);
			Assert::AreEqual(static_cast<double>(2.5f), static_cast<double>(v.y), DELTA);
			Assert::AreEqual(static_cast<double>(-5.0f), static_cast<double>(v.z), DELTA);
			Assert::AreEqual(static_cast<double>(-3.14159f), static_cast<double>(v.w), DELTA);
		}

		TEST_METHOD(constructorHex)
		{
			Vector4 v1(0x00000000);
			Vector4 v2(0xFFFFFFFF);
			Vector4 red(0xFF0000FF);
			Vector4 green(0x00FF00FF);
			Vector4 blue(0x0000FF7F);

			Assert::IsTrue(Vector4() == v1);
			Assert::IsTrue(Vector4(255, 255, 255, 255) == v2);
			Assert::IsTrue(Vector4(255, 0, 0, 255) == red);
			Assert::IsTrue(Vector4(0, 255, 0, 255) == green);
			Assert::IsTrue(Vector4(0, 0, 255, 127) == blue);
		}

		TEST_METHOD(constructorHexStatic)
		{
			Vector4 v1 = Vector4::ConstructFromHex(0x00000000);
			Vector4 v2 = Vector4::ConstructFromHex(0xFFFFFFFF);
			Vector4 red = Vector4::ConstructFromHex(0xFF0000FF);
			Vector4 green = Vector4::ConstructFromHex(0x00FF00FF);
			Vector4 blue = Vector4::ConstructFromHex(0x0000FF7F);

			Assert::IsTrue(Vector4() == v1);
			Assert::IsTrue(Vector4(255, 255, 255, 255) == v2);
			Assert::IsTrue(Vector4(255, 0, 0, 255) == red);
			Assert::IsTrue(Vector4(0, 255, 0, 255) == green);
			Assert::IsTrue(Vector4(0, 0, 255, 127) == blue);
		}

		TEST_METHOD(constructorCopy)
		{
			Vector4 v(1, 2, 3, 4);
			Vector4 v2(v);
			Assert::AreEqual(static_cast<double>(1), static_cast<double>(v.x), DELTA);
			Assert::AreEqual(static_cast<double>(2), static_cast<double>(v.y), DELTA);
			Assert::AreEqual(static_cast<double>(3), static_cast<double>(v.z), DELTA);
			Assert::AreEqual(static_cast<double>(4), static_cast<double>(v.w), DELTA);

			//verify param still same
			Assert::IsTrue(&v != &v2);
			Assert::IsTrue(v == v2);
		}

		TEST_METHOD(assignment)
		{
			Vector4 v(1, 2, 3, 4);
			Vector4 v2(4, 3, 2, 1);

			v = v2 = v2;
			Assert::IsTrue(v == v2);
			Assert::IsFalse(&v == &v2);
			Assert::IsTrue(v2 == Vector4(4, 3, 2, 1));
		}

		TEST_METHOD(equality)
		{
			Vector4 v1(1, 2, 3, 4);
			Vector4 v2(1, 2, 3, 4);
			Vector4 v3(1, 2, 3, 5);

			Assert::IsTrue(v1 == v1);
			Assert::IsTrue(v1 == v2);
			Assert::IsFalse(v1 == v3);

			Assert::IsTrue(v1 == v1);
			Assert::IsTrue(v1 == v2);
			Assert::IsFalse(v1 == v3);
		}

		TEST_METHOD(inEquality)
		{
			Vector4 v1(1, 2, 3, 4);
			Vector4 v2(1, 2, 3, 4);
			Vector4 v3(1, 2, 3, 5);

			Assert::IsFalse(v1 != v1);
			Assert::IsFalse(v1 != v2);
			Assert::IsTrue(v1 != v3);
		}

		TEST_METHOD(additionAssignment)
		{
			Vector4 v1(1, 2, 3, 4);
			Vector4 v2(5, 4, 3, 2);
			v1 += v2;

			Assert::IsTrue(Vector4(6, 6, 6, 6) == v1);
			Assert::IsTrue(Vector4(5, 4, 3, 2) == v2);

			//verify chaining
			v1 = Vector4(1, 2, 3, 4);
			v1 += v2 += v2;

			Assert::IsTrue(Vector4(11, 10, 9, 8) == v1);
			Assert::IsTrue(Vector4(10, 8, 6, 4) == v2);
		}

		TEST_METHOD(addition)
		{
			Vector4 v1(10, 10, 10, 10);
			Vector4 v2(5, 5, 5, 5);
			Vector4 v3 = v1 + v2;

			Assert::IsTrue(v1 == Vector4(10, 10, 10, 10));
			Assert::IsTrue(v2 == Vector4(5, 5, 5, 5));
			Assert::IsTrue(v3 == Vector4(15, 15, 15, 15));

			//verify chaining
			v3 = v1 + v2 + v3;
			Assert::IsTrue(v3 == Vector4(30, 30, 30, 30));
			Assert::IsTrue(v1 == Vector4(10, 10, 10, 10));
			Assert::IsTrue(v2 == Vector4(5, 5, 5, 5));
		}

		TEST_METHOD(subtractAssignment)
		{
			Vector4 v1(10, 10, 10, 10);
			Vector4 v2(5, 5, 5, 5);
			v1 -= v2;

			Assert::IsTrue(Vector4(5, 5, 5, 5) == v1);
			Assert::IsTrue(Vector4(5, 5, 5, 5) == v2);

			//verify chaining
			v1 = Vector4(10, 10, 10, 10);
			v1 -= v2 -= v2;

			Assert::IsTrue(Vector4(10, 10, 10, 10) == v1);
			Assert::IsTrue(Vector4(0, 0, 0, 0) == v2);
		}

		TEST_METHOD(subtractOperator)
		{

			Vector4 v1(10, 10, 10, 10);
			Vector4 v2(5, 5, 5, 5);
			Vector4 v3 = v1 - v2;

			Assert::IsTrue(v1 == Vector4(10, 10, 10, 10));
			Assert::IsTrue(v2 == Vector4(5, 5, 5, 5));
			Assert::IsTrue(v3 == Vector4(5, 5, 5, 5));

			//chaining 
			v3 = v1 - v2 - v2;
			Assert::IsTrue(v1 == Vector4(10, 10, 10, 10));
			Assert::IsTrue(v2 == Vector4(5, 5, 5, 5));
			Assert::IsTrue(v3 == Vector4(0, 0, 0, 0));

		}

		TEST_METHOD(negativeUnary)
		{
			Vector4 v(1, 2, 3, 4);
			Assert::IsTrue(Vector4(-1, -2, -3, -4) == -v);
			Assert::IsTrue(Vector4(1, 2, 3, 4) == v);
		}

		TEST_METHOD(bangOperator)
		{
			Vector4 v(1, 2, 3, 4);
			Vector4 v2;

			Assert::IsFalse(!v);
			Assert::IsTrue(!v2);
		}

		TEST_METHOD(multiplyOperator)
		{
			Vector4 v1(10, 10, 10, 10);

			double scalar = 5.0;
			Vector4 v2 = v1 * scalar;

			Assert::IsTrue(v1 == Vector4(10, 10, 10, 10));
			Assert::AreEqual(5.0, scalar, DELTA);
			Assert::IsTrue(v2 == Vector4(50, 50, 50, 50));
		}

		TEST_METHOD(multiplyAssignmentOperator)
		{
			Vector4 v1(5, 5, 5, 5);
			double scalar = 10.0;
			v1 *= scalar;

			Assert::IsTrue(v1 == Vector4(50, 50, 50, 50));
			Assert::AreEqual(10.0, scalar, DELTA);
		}

		TEST_METHOD(bracketOperator)
		{
			Vector4 v(1, 2, 3, 4);
			float r = v[2];

			Assert::AreEqual(static_cast<double>(3), static_cast<double>(r), DELTA);
		}

		TEST_METHOD(magnitude)
		{
			Vector4 v1;
			//check zero

			Assert::AreEqual(static_cast<double>(0), static_cast<double>(v1.Magnitude()), DELTA);

			v1 = Vector4(1, 5, 8, 9);
			Assert::AreEqual(13.076696830622020656710945951579, static_cast<double>(v1.Magnitude()), DELTA);
			Assert::IsTrue(v1 == Vector4(1, 5, 8, 9));

		}

		TEST_METHOD(normalize)
		{
			Vector4 v(30, 40, 50, 60);
			v.Normalize();
			//magnitude = sqrt(5000)
			Assert::AreEqual(static_cast<double>(0.32349831961031524718080521188338), static_cast<double>(v.x), DELTA);
			Assert::AreEqual(static_cast<double>(0.43133109281375366290774028251117), static_cast<double>(v.y), DELTA);
			Assert::AreEqual(static_cast<double>(0.53916386601719207863467535313896), static_cast<double>(v.z), DELTA);
			Assert::AreEqual(static_cast<double>(0.64699663922063049436161042376676), static_cast<double>(v.w), DELTA);

			Vector4 v2;
			v2.Normalize();
			//divide by zero check
			Assert::IsTrue(v2 == Vector4());
		}

		TEST_METHOD(dotProduct)
		{
			Vector4 v1(5, 2, 15, -10);
			Vector4 v2(-10, 4, -100, 12);
			Assert::AreEqual(static_cast<double>(-1662), static_cast<double>(v1.DotProduct(v2)), DELTA);
			Assert::IsTrue(v1 == Vector4(5, 2, 15, -10));
			Assert::IsTrue(v2 == Vector4(-10, 4, -100, 12));
		}
	};
}