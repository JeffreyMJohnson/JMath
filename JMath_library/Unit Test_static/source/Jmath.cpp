#include "CppUnitTest.h"
#include "TheMath.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_static
{		
	TEST_CLASS(Test_Jmath)
	{
	public:
		
		TEST_METHOD(DegToRad)
		{
			Assert::AreEqual(.7853975, static_cast<double>(JMath::DegreeToRadians(45)), .001);
		}

		TEST_METHOD(RadToDeg)
		{
			Assert::AreEqual(static_cast<double>(JMath::DegreeToRadians(45)), .7853975, .001);
		}

		TEST_METHOD(staticLerp)
		{
			float start = 0;
			float end = 10;

			float r = JMath::LERP(start, end, 0);
			Assert::AreEqual(0, static_cast<double>(r), .001);

			r = JMath::LERP(start, end, 1);
			Assert::AreEqual(10, static_cast<double>(r), .001);

			r = JMath::LERP(start, end, .5);
			Assert::AreEqual(5, static_cast<double>(r), .001);
		}

		TEST_METHOD(isPowOfTwo)
		{
			unsigned int i = 10;
			Assert::IsFalse(JMath::IsPowerOfTwo(i));

			i = 128;
			Assert::IsTrue(JMath::IsPowerOfTwo(i));

			i = 0;
			Assert::IsFalse(JMath::IsPowerOfTwo(i));

			i = 1;
			Assert::IsTrue(JMath::IsPowerOfTwo(i));

			i = 127;
			Assert::IsFalse(JMath::IsPowerOfTwo(i));
		}

		TEST_METHOD(getNextPowOfTwo)
		{
			Assert::AreEqual(0, JMath::GetNextPowerOfTwo(0), .00001);
			Assert::AreEqual(2, JMath::GetNextPowerOfTwo(2), .00001);
			Assert::AreEqual(8, JMath::GetNextPowerOfTwo(6), .00001);
			Assert::AreEqual(16, JMath::GetNextPowerOfTwo(9), .00001);
			Assert::AreEqual(1073741824, JMath::GetNextPowerOfTwo(1073741823), .00001);
		}

	};
}