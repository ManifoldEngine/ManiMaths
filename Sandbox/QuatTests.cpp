#include "ManiTests/ManiTests.h"
#include "ManiZ/ManiZ.h"

#include "ManiMaths/Quat.h"
#include "ManiMaths/Vec3.h"
#include "ManiMaths/Maths.h"

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
			MANI_TEST_ASSERT((q2 * q1) != expected, "quaternion product is not commutative.");
		}
		{
			Mani::Quatf q1 = { .1f, .2f, .3f, 1.f };
			Mani::Quatf expected = { -.1f, -.2f, -.3f, 1.f };
			MANI_TEST_ASSERT(q1.conjugate().isNearlyEqual(expected), "conguate should be -x, -y, -z, w");
		}
		{
			Mani::Quatf q1 = { 1, 2, 3, 4 };
			Mani::Quatf expected = { 0.18257f, 0.36515f, 0.54772f, 0.7303f };
			Mani::Quatf q1Normalized = q1.normalize();
			constexpr float tolerance = .0001f;
			MANI_TEST_ASSERT(expected.isNearlyEqual(q1Normalized, tolerance), "Should normalize properly");
		}
		{
			Mani::Quatf q1 = { 1.f, 2.f, 3.f, 1.f };
			Mani::Quatf q2 = { 4.f, 5.f, 6.f, 1.f };
			Mani::Quatf q3 = { 1.f, 2.f, 3.f, 1.f };

			MANI_TEST_ASSERT(q1.isNearlyEqual(q2) == false, "q1 is not equal to q2");
			MANI_TEST_ASSERT(q1.isNearlyEqual(q3) == true, "q1 is equal to q3");
		}
	}

	MANI_TEST(QuaternionToVectorOperations, "Should operate on vectors")
	{
		{
			const Mani::Quatf q1 = Mani::Quatf::axisAngleDeg(90.0f, Mani::Vec3f{ 1.f, 0.f, 0.f });
			const Mani::Vec3f v1 = Mani::Vec3f{ 0.0f, 1.0f, 0.0f };

			const Mani::Vec3f rotatedVector = Mani::Quatf::rotate(q1, v1);
			const Mani::Vec3f expected = Mani::Vec3f{ 0.0f, 0.0f, 1.0f };
			MANI_TEST_ASSERT(rotatedVector.isNearlyEqual(expected), "Should rotate 1/4 around x axis");
		}
	}

	MANI_TEST(QuaternionFunctionalities, "Various Quaternion functionalities")
	{
		{
			const Mani::Quatf q1 = { 1.0f, 0.f, 0.f, 0.f };
			const Mani::Quatf q2 = { 0.f, 1.f, 0.f, 0.f };

			const float result = q1.angleDeg(q2);
			MANI_TEST_ASSERT(Mani::Math::isEqual(result, 180.f), "Should be about 90 degree");
		}
		{
			const Mani::Quatf q1 = { 1.0f, 0.f, 0.f, 0.f };
			const Mani::Quatf q2 = { 0.f, 1.f, 0.f, 0.f };

			const float result = q1.angleDeg(q2);
			MANI_TEST_ASSERT(Mani::Math::isEqual(result, 180.f), "Should be about 90 degree");
		}
		{
			const Mani::Quatf q1 = { 1.0f, 0.f, 0.f, 0.f };
			const Mani::Quatf q2 = { 0.f, 1.f, 0.f, 0.f };

			const Mani::Quatf result1 = Mani::Quatf::slerp(q1, q2, 0.f);
			const Mani::Quatf result2 = Mani::Quatf::slerp(q1, q2, 1.f);
			MANI_TEST_ASSERT(q1.isNearlyEqual(result1), "no slerp should be equal to q1");
			MANI_TEST_ASSERT(q2.isNearlyEqual(result2), "full slerp should be equal to q2");
		}
	}
}
MANI_SECTION_END(Quaternion)