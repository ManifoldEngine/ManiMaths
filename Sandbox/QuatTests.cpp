#include "ManiTests/ManiTests.h"
#include "ManiZ/ManiZ.h"

#include "ManiMaths/Quaternion.h"

MANI_SECTION_BEGIN(Quaternion, "Quaternion section")
{
	MANI_TEST(CanSerializeAQuaternion, "Should successfully serialize and deserialize a quaternion")
	{
		{
			Mani::Quatf q1;
			const std::string jsonString = ManiZ::to::json(q1);
			Mani::Quatf q2 = ManiZ::from::json<Mani::Quatf>(jsonString);
			MANI_TEST_ASSERT(q1 == q2, "q1 should equal q2 after going through ManiZ serialization/deserialization.");
		}
		{
			Mani::Quatd q1;
			const std::string jsonString = ManiZ::to::json(q1);
			Mani::Quatd q2 = ManiZ::from::json<Mani::Quatd>(jsonString);
			MANI_TEST_ASSERT(q1 == q2, "q1 should equal q2 after going through ManiZ serialization/deserialization.");
		}
	}

	MANI_TEST(QuaternionArithmetic, "Should successfully operate on 2 quaternions")
	{
		{
			Mani::Quatf q1 = { 1, 2, 3, 4 };
			Mani::Quatf q2 = { 4, 5, 6, 7 };
			Mani::Quatf expected = { 5, 7, 9, 11 };
			MANI_TEST_ASSERT((q1 + q2) == expected, "q1 + q2 should equal expected");
		}
		{
			Mani::Quatf q1 = { 1, 2, 3, 4 };
			Mani::Quatf q2 = { 4, 5, 6, 7 };
			Mani::Quatf expected = { 3, 3, 3, 3 };
			MANI_TEST_ASSERT((q2 - q1) == expected, "q1 - q2 should equal expected");
		}
		{
			Mani::Quatf q1 = { 2, 4, 1, 3 };
			Mani::Quatf q2 = { 3, 5, 2, 1 };
			Mani::Quatf expected = { 14, 18, 5, -25 };
			MANI_TEST_ASSERT((q1 * q2) == expected, "q1 * q2 should equal expected");
			MANI_TEST_ASSERT((q2 * q1) != expected, "product is not commutative.");
		}
		/* {
			Mani::Vector3i v1 = { 1, 2, 3 };
			Mani::Vector3i v2 = { 4, 5, 6 };
			Mani::Vector3i expected = { 5, 7, 9 };
			v1 += v2;
			MANI_TEST_ASSERT(v1 == expected, "v1 + v2 should equal expected");
		}
		{
			Mani::Vector3i v1 = { 1, 2, 3 };
			Mani::Vector3i v2 = { 4, 5, 6 };
			Mani::Vector3i expected = { 3, 3, 3 };
			v2 -= v1;
			MANI_TEST_ASSERT(v2 == expected, "v1 - v2 should equal expected");
		}
		{
			Mani::Vector3i v1 = { 1, 2, 3 };
			Mani::Vector3i v2 = { 4, 5, 6 };
			Mani::Vector3i expected = { 4, 10, 18 };
			v1 *= v2;
			MANI_TEST_ASSERT(v1 == expected, "v1 * v2 should equal expected");
		}
		{
			Mani::Vector3i v1 = { 1, 2, 3 };
			constexpr int scale = 2;
			Mani::Vector3i expected = { 2, 4, 6 };

			MANI_TEST_ASSERT(v1 * 2 == expected, "v1 * 2 should equal expected");
		}
		{
			Mani::Vector3i v1 = { 1, 2, 3 };
			constexpr int scale = 2;
			Mani::Vector3i expected = { 2, 4, 6 };
			v1 *= 2;
			MANI_TEST_ASSERT(v1 == expected, "v1 * 2 should equal expected");
		}
		*/
		{
			Mani::Quatf q1 = { 1.f, 2.f, 3.f, 1.f };
			Mani::Quatf q2 = { 4.f, 5.f, 6.f, 1.f };
			Mani::Quatf q3 = { 1.f, 2.f, 3.f, 1.f };

			MANI_TEST_ASSERT(q1.isNearlyEqual(q2) == false, "q1 is not equal to q2");
			MANI_TEST_ASSERT(q1.isNearlyEqual(q3) == true, "q1 is equal to q3");
		}
		/*
		{
			Mani::Vector3f v1 = { 1.f, 2.f, 3.f };
			constexpr int scale = 2;
			Mani::Vector3f expected = { .5f, 1.f, 1.5f };

			MANI_TEST_ASSERT((v1 / 2).isNearlyEqual(expected), "v1 / 2 should equal expected");
		}
		{
			Mani::Vector3f v1 = { 1.f, 2.f, 3.f };
			constexpr int scale = 2;
			Mani::Vector3f expected = { .5f, 1.f, 1.5f };
			v1 /= 2;
			MANI_TEST_ASSERT(v1.isNearlyEqual(expected), "v1 / 2 should equal expected");
		}*/
	}
}
MANI_SECTION_END(Quaternion)