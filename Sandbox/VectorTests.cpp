#include "ManiTests/ManiTests.h"
#include "ManiZ/ManiZ.h"

#include "ManiMaths/Vector.h"
#include "ManiMaths/Maths.h"

MANI_SECTION_BEGIN(Vector, "Vector section")
{
	MANI_TEST(CanSerializeAVector, "Should successfully serialize and deserialize a vector")
	{
		{
			Mani::Vec3i v1;
			const std::string jsonString = ManiZ::to::json(v1);
			Mani::Vec3i v2 = ManiZ::from::json<Mani::Vec3i>(jsonString);
			MANI_TEST_ASSERT(v1 == v2, "v1 should equal v2 after going through ManiZ serialization/deserialization.");
		}
		{
			Mani::Vec3l v1;
			const std::string jsonString = ManiZ::to::json(v1);
			Mani::Vec3l v2 = ManiZ::from::json<Mani::Vec3l>(jsonString);
			MANI_TEST_ASSERT(v1 == v2, "v1 should equal v2 after going through ManiZ serialization/deserialization.");
		}
		{
			Mani::Vec3f v1;
			const std::string jsonString = ManiZ::to::json(v1);
			Mani::Vec3f v2 = ManiZ::from::json<Mani::Vec3f>(jsonString);
			MANI_TEST_ASSERT(v1 == v2, "v1 should equal v2 after going through ManiZ serialization/deserialization.");
		}
		{
			Mani::Vec3d v1;
			const std::string jsonString = ManiZ::to::json(v1);
			Mani::Vec3d v2 = ManiZ::from::json<Mani::Vec3d>(jsonString);
			MANI_TEST_ASSERT(v1 == v2, "v1 should equal v2 after going through ManiZ serialization/deserialization.");
		}
		{
			Mani::Vec3ui v1;
			const std::string jsonString = ManiZ::to::json(v1);
			Mani::Vec3ui v2 = ManiZ::from::json<Mani::Vec3ui>(jsonString);
			MANI_TEST_ASSERT(v1 == v2, "v1 should equal v2 after going through ManiZ serialization/deserialization.");
		}
		{
			Mani::Vec3ul v1;
			const std::string jsonString = ManiZ::to::json(v1);
			Mani::Vec3ul v2 = ManiZ::from::json<Mani::Vec3ul>(jsonString);
			MANI_TEST_ASSERT(v1 == v2, "v1 should equal v2 after going through ManiZ serialization/deserialization.");
		}
	}

	MANI_TEST(AddVectors, "Should successfully operate on 2 vectors")
	{
		{
			Mani::Vec3i v1 = { 1, 2, 3 };
			Mani::Vec3i v2 = { 4, 5, 6 };
			Mani::Vec3i expected = { 5, 7, 9 };
			MANI_TEST_ASSERT((v1 + v2) == expected, "v1 + v2 should equal expected");
		}
		{
			Mani::Vec3i v1 = { 1, 2, 3 };
			Mani::Vec3i v2 = { 4, 5, 6 };
			Mani::Vec3i expected = { 3, 3, 3 };
			MANI_TEST_ASSERT((v2 - v1) == expected, "v1 - v2 should equal expected");
		}
		{
			Mani::Vec3i v1 = { 1, 2, 3 };
			Mani::Vec3i v2 = { 4, 5, 6 };
			Mani::Vec3i expected = { 4, 10, 18 };
			MANI_TEST_ASSERT((v1 * v2) == expected, "v1 * v2 should equal expected");
		}
		{
			Mani::Vec3i v1 = { 1, 2, 3 };
			Mani::Vec3i v2 = { 4, 5, 6 };
			Mani::Vec3i expected = { 5, 7, 9 };
			v1 += v2;
			MANI_TEST_ASSERT(v1 == expected, "v1 + v2 should equal expected");
		}
		{
			Mani::Vec3i v1 = { 1, 2, 3 };
			Mani::Vec3i v2 = { 4, 5, 6 };
			Mani::Vec3i expected = { 3, 3, 3 };
			v2 -= v1;
			MANI_TEST_ASSERT(v2 == expected, "v1 - v2 should equal expected");
		}
		{
			Mani::Vec3i v1 = { 1, 2, 3 };
			Mani::Vec3i v2 = { 4, 5, 6 };
			Mani::Vec3i expected = { 4, 10, 18 };
			v1 *= v2;
			MANI_TEST_ASSERT(v1 == expected, "v1 * v2 should equal expected");
		}
		{
			Mani::Vec3i v1 = { 1, 2, 3 };
			constexpr int scale = 2;
			Mani::Vec3i expected = { 2, 4, 6 };
			
			MANI_TEST_ASSERT(v1 * 2 == expected, "v1 * 2 should equal expected");
		}
		{
			Mani::Vec3i v1 = { 1, 2, 3 };
			constexpr int scale = 2;
			Mani::Vec3i expected = { 2, 4, 6 };
			v1 *= 2;
			MANI_TEST_ASSERT(v1 == expected, "v1 * 2 should equal expected");
		}
		{
			Mani::Vec3f v1 = { 1.f, 2.f, 3.f };
			Mani::Vec3f v2 = { 4.f, 5.f, 6.f };
			Mani::Vec3f v3 = { 1.f, 2.f, 3.f };
			
			MANI_TEST_ASSERT(v1.isNearlyEqual(v2) == false, "v1 is not equal to v2");
			MANI_TEST_ASSERT(v1.isNearlyEqual(v3) == true, "v1 is equal to v3");
		}
		{
			Mani::Vec3f v1 = { 1.f, 2.f, 3.f };
			constexpr int scale = 2;
			Mani::Vec3f expected = { .5f, 1.f, 1.5f };
			
			MANI_TEST_ASSERT((v1 / 2).isNearlyEqual(expected), "v1 / 2 should equal expected");
		}
		{
			Mani::Vec3f v1 = { 1.f, 2.f, 3.f };
			constexpr int scale = 2;
			Mani::Vec3f expected = { .5f, 1.f, 1.5f };
			v1 /= 2;
			MANI_TEST_ASSERT(v1.isNearlyEqual(expected), "v1 / 2 should equal expected");
		}
		{
			const Mani::Vec3f v1 = { 1.f, 2.f, 3.f };
			const Mani::Vec3f v1Normalized = v1.normalize();
			MANI_TEST_ASSERT(Mani::abs(v1Normalized.length() - 1.f) < FLT_EPSILON, "Can normalize v1");
		}
	}

	MANI_TEST(InterTypeMath, "Should be able to do math between different vector types")
	{
		Mani::Vec3i v1{ 1, 2, 3 };
		Mani::Vec3f v2{ 1.8f, 2.5f, 3.2f };
		Mani::Vec3f expected{ 2.8f, 4.5f, 6.2f };

		// doesn't compile because float to int requires a narrowing conversion which requires an explicit cast.
		// MANI_TEST_ASSERT((v1 + v2).isNearlyEqual(expected), "v1 + v2 should equal expected");
		MANI_TEST_ASSERT((v2 + v1).isNearlyEqual(expected), "v1 + v2 should equal expected");
	}

	MANI_TEST(VectorLength, "Should correctly compute the length of a vector")
	{
		Mani::Vec3f v1{ 1.f, 2.f, 3.f };
		const float length = v1.length();
		const float lengthSquared = v1.lengthSquared();

		constexpr float expectedSquared = 14.f;

		MANI_TEST_ASSERT(Mani::abs(length - std::sqrt(expectedSquared)) <= FLT_EPSILON, "length should be equal to what is expected");
		MANI_TEST_ASSERT(Mani::abs(lengthSquared - expectedSquared) <= FLT_EPSILON, "length should be equal to what is expected");
	}

	MANI_TEST(DistanceMaths, "Should correctly compute the distance betweem 2 vectors")
	{
		Mani::Vec3f v1{ 1.f, 2.f, 3.f };
		Mani::Vec3f v2{ 2.f, 3.f, 4.f };

		const float v1tov2 = v1.distance(v2);
		const float v2tov1 = v2.distance(v1);

		const float v1tov2squared = v1.distanceSquared(v2);
		const float v2tov1squared = v2.distanceSquared(v1);

		constexpr float expectedSquared = 3.f;
		MANI_TEST_ASSERT(Mani::abs(v1tov2 - std::sqrt(expectedSquared)) <= FLT_EPSILON, "v1 should be at 1 unit from v2");
		MANI_TEST_ASSERT(Mani::abs(v2tov1 - std::sqrt(expectedSquared)) <= FLT_EPSILON, "v1 should be at 1 unit from v2");

		MANI_TEST_ASSERT(Mani::abs(v1tov2squared - expectedSquared) <= FLT_EPSILON, "v1 should be at 1 unit from v2");
		MANI_TEST_ASSERT(Mani::abs(v2tov1squared - expectedSquared) <= FLT_EPSILON, "v1 should be at 1 unit from v2");
	}

	MANI_TEST(ToString, "Should output a properly formatted string")
	{
		Mani::Vec3i v1{ 1, 2, 3 };
		MANI_TEST_ASSERT(v1.toString() == "(1, 2, 3)", "Should be equal to expected value");
	}
}
MANI_SECTION_END(Vector)