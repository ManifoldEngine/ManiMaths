#include "ManiTests/ManiTests.h"
#include "ManiZ/ManiZ.h"

#include "ManiMaths/Vec2.h"
#include "ManiMaths/Vec3.h"
#include "ManiMaths/Vec4.h"

#include "ManiMaths/Maths.h"

MANI_SECTION_BEGIN(Vec3, "Vector section")
{
	MANI_TEST(CanSerializeAVector3, "Should successfully serialize and deserialize a vector")
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

	MANI_TEST(AddVector3s, "Should successfully operate on 2 vectors")
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

	MANI_TEST(InterTypeMathVector3, "Should be able to do math between different vector types")
	{
		Mani::Vec3i v1{ 1, 2, 3 };
		Mani::Vec3f v2{ 1.8f, 2.5f, 3.2f };
		Mani::Vec3f expected{ 2.8f, 4.5f, 6.2f };

		// doesn't compile because float to int requires a narrowing conversion which requires an explicit cast.
		// MANI_TEST_ASSERT((v1 + v2).isNearlyEqual(expected), "v1 + v2 should equal expected");
		MANI_TEST_ASSERT((v2 + v1).isNearlyEqual(expected), "v1 + v2 should equal expected");
	}

	MANI_TEST(Vector3Length, "Should correctly compute the length of a vector")
	{
		Mani::Vec3f v1{ 1.f, 2.f, 3.f };
		const float length = v1.length();
		const float lengthSquared = v1.lengthSquared();

		constexpr float expectedSquared = 14.f;

		MANI_TEST_ASSERT(Mani::abs(length - std::sqrt(expectedSquared)) <= FLT_EPSILON, "length should be equal to what is expected");
		MANI_TEST_ASSERT(Mani::abs(lengthSquared - expectedSquared) <= FLT_EPSILON, "length should be equal to what is expected");
	}

	MANI_TEST(DistanceMathsVec3, "Should correctly compute the distance betweem 2 vectors")
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

	MANI_TEST(ToStringVec3, "Should output a properly formatted string")
	{
		Mani::Vec3i v1{ 1, 2, 3 };
		MANI_TEST_ASSERT(v1.toString() == "(1, 2, 3)", "Should be equal to expected value");
	}

	MANI_TEST(DotAndCrossVec3, "Should dot and cross 2 vec3")
	{
		Mani::Vec3f v1 = Mani::VEC3F::FORWARD;
		Mani::Vec3f v2 = Mani::VEC3F::RIGHT;

		const float dot = v1.dot(v2);
		const Mani::Vec3f cross = v1.cross(v2);

		MANI_TEST_ASSERT(Mani::isEqual(dot, 0.f), "dot should be 0");
		MANI_TEST_ASSERT(cross.isNearlyEqual(Mani::VEC3F::UP), "cross should be equal to up");
	}
}
MANI_SECTION_END(Vec3)

MANI_SECTION_BEGIN(Vec2, "Vector2 section")
{
	MANI_TEST(CanSerializeAVector2, "Should successfully serialize and deserialize a vector2")
	{
		{
			Mani::Vec2i v1;
			const std::string jsonString = ManiZ::to::json(v1);
			Mani::Vec2i v2 = ManiZ::from::json<Mani::Vec2i>(jsonString);
			MANI_TEST_ASSERT(v1 == v2, "v1 should equal v2 after going through ManiZ serialization/deserialization.");
		}
		{
			Mani::Vec2l v1;
			const std::string jsonString = ManiZ::to::json(v1);
			Mani::Vec2l v2 = ManiZ::from::json<Mani::Vec2l>(jsonString);
			MANI_TEST_ASSERT(v1 == v2, "v1 should equal v2 after going through ManiZ serialization/deserialization.");
		}
		{
			Mani::Vec2f v1;
			const std::string jsonString = ManiZ::to::json(v1);
			Mani::Vec2f v2 = ManiZ::from::json<Mani::Vec2f>(jsonString);
			MANI_TEST_ASSERT(v1 == v2, "v1 should equal v2 after going through ManiZ serialization/deserialization.");
		}
		{
			Mani::Vec2d v1;
			const std::string jsonString = ManiZ::to::json(v1);
			Mani::Vec2d v2 = ManiZ::from::json<Mani::Vec2d>(jsonString);
			MANI_TEST_ASSERT(v1 == v2, "v1 should equal v2 after going through ManiZ serialization/deserialization.");
		}
		{
			Mani::Vec2ui v1;
			const std::string jsonString = ManiZ::to::json(v1);
			Mani::Vec2ui v2 = ManiZ::from::json<Mani::Vec2ui>(jsonString);
			MANI_TEST_ASSERT(v1 == v2, "v1 should equal v2 after going through ManiZ serialization/deserialization.");
		}
		{
			Mani::Vec2ul v1;
			const std::string jsonString = ManiZ::to::json(v1);
			Mani::Vec2ul v2 = ManiZ::from::json<Mani::Vec2ul>(jsonString);
			MANI_TEST_ASSERT(v1 == v2, "v1 should equal v2 after going through ManiZ serialization/deserialization.");
		}
	}

	MANI_TEST(AddVector2s, "Should successfully operate on 2 vectors")
	{
		{
			Mani::Vec2i v1 = { 1, 2 };
			Mani::Vec2i v2 = { 4, 5 };
			Mani::Vec2i expected = { 5, 7 };
			MANI_TEST_ASSERT((v1 + v2) == expected, "v1 + v2 should equal expected");
		}
		{
			Mani::Vec2i v1 = { 1, 2 };
			Mani::Vec2i v2 = { 4, 5 };
			Mani::Vec2i expected = { 3, 3 };
			MANI_TEST_ASSERT((v2 - v1) == expected, "v1 - v2 should equal expected");
		}
		{
			Mani::Vec2i v1 = { 1, 2 };
			Mani::Vec2i v2 = { 4, 5 };
			Mani::Vec2i expected = { 4, 10 };
			MANI_TEST_ASSERT((v1 * v2) == expected, "v1 * v2 should equal expected");
		}
		{
			Mani::Vec2i v1 = { 1, 2 };
			Mani::Vec2i v2 = { 4, 5 };
			Mani::Vec2i expected = { 5, 7 };
			v1 += v2;
			MANI_TEST_ASSERT(v1 == expected, "v1 + v2 should equal expected");
		}
		{
			Mani::Vec2i v1 = { 1, 2 };
			Mani::Vec2i v2 = { 4, 5 };
			Mani::Vec2i expected = { 3, 3 };
			v2 -= v1;
			MANI_TEST_ASSERT(v2 == expected, "v1 - v2 should equal expected");
		}
		{
			Mani::Vec2i v1 = { 1, 2 };
			Mani::Vec2i v2 = { 4, 5 };
			Mani::Vec2i expected = { 4, 10 };
			v1 *= v2;
			MANI_TEST_ASSERT(v1 == expected, "v1 * v2 should equal expected");
		}
		{
			Mani::Vec2i v1 = { 1, 2 };
			constexpr int scale = 2;
			Mani::Vec2i expected = { 2, 4 };

			MANI_TEST_ASSERT(v1 * 2 == expected, "v1 * 2 should equal expected");
		}
		{
			Mani::Vec2i v1 = { 1, 2 };
			constexpr int scale = 2;
			Mani::Vec2i expected = { 2, 4 };
			v1 *= 2;
			MANI_TEST_ASSERT(v1 == expected, "v1 * 2 should equal expected");
		}
		{
			Mani::Vec2f v1 = { 1.f, 2.f };
			Mani::Vec2f v2 = { 4.f, 5.f };
			Mani::Vec2f v3 = { 1.f, 2.f };

			MANI_TEST_ASSERT(v1.isNearlyEqual(v2) == false, "v1 is not equal to v2");
			MANI_TEST_ASSERT(v1.isNearlyEqual(v3) == true, "v1 is equal to v3");
		}
		{
			Mani::Vec2f v1 = { 1.f, 2.f };
			constexpr int scale = 2;
			Mani::Vec2f expected = { .5f, 1.f };

			MANI_TEST_ASSERT((v1 / 2).isNearlyEqual(expected), "v1 / 2 should equal expected");
		}
		{
			Mani::Vec2f v1 = { 1.f, 2.f };
			constexpr int scale = 2;
			Mani::Vec2f expected = { .5f, 1.f };
			v1 /= 2;
			MANI_TEST_ASSERT(v1.isNearlyEqual(expected), "v1 / 2 should equal expected");
		}
		{
			const Mani::Vec2f v1 = { 1.f, 2.f };
			const Mani::Vec2f v1Normalized = v1.normalize();
			MANI_TEST_ASSERT(Mani::abs(v1Normalized.length() - 1.f) < FLT_EPSILON, "Can normalize v1");
		}
	}

	MANI_TEST(Vector2Length, "Should correctly compute the length of a vector")
	{
		Mani::Vec2f v1{ 1.f, 2.f };
		const float length = v1.length();
		const float lengthSquared = v1.lengthSquared();

		constexpr float expectedSquared = 5.f;

		MANI_TEST_ASSERT(Mani::abs(length - std::sqrt(expectedSquared)) <= FLT_EPSILON, "length should be equal to what is expected");
		MANI_TEST_ASSERT(Mani::abs(lengthSquared - expectedSquared) <= FLT_EPSILON, "length should be equal to what is expected");
	}

	MANI_TEST(DistanceMathsVec2, "Should correctly compute the distance between 2 vectors")
	{
		Mani::Vec2f v1{ 1.f, 2.f };
		Mani::Vec2f v2{ 2.f, 3.f };

		const float v1tov2 = v1.distance(v2);
		const float v2tov1 = v2.distance(v1);

		const float v1tov2squared = v1.distanceSquared(v2);
		const float v2tov1squared = v2.distanceSquared(v1);

		constexpr float expectedSquared = 2.f;
		MANI_TEST_ASSERT(Mani::abs(v1tov2 - std::sqrt(expectedSquared)) <= FLT_EPSILON, "v1 should be at 1 unit from v2");
		MANI_TEST_ASSERT(Mani::abs(v2tov1 - std::sqrt(expectedSquared)) <= FLT_EPSILON, "v1 should be at 1 unit from v2");

		MANI_TEST_ASSERT(Mani::abs(v1tov2squared - expectedSquared) <= FLT_EPSILON, "v1 should be at 1 unit from v2");
		MANI_TEST_ASSERT(Mani::abs(v2tov1squared - expectedSquared) <= FLT_EPSILON, "v1 should be at 1 unit from v2");
	}

	MANI_TEST(ToStringVec2, "Should output a properly formatted string")
	{
		Mani::Vec2i v1{ 1, 2 };
		MANI_TEST_ASSERT(v1.toString() == "(1, 2)", "Should be equal to expected value");
	}

	MANI_TEST(DotVec2, "Should correctly compute dot product of 2 vec2")
	{
		Mani::Vec2f v1{ 1.f, 2.f };
		Mani::Vec2f v2{ 3.f, 4.f };

		// Dot product test
		const float dot = v1.dot(v2);
		const float expectedDot = 11.f; // 1*3 + 2*4 = 11
		MANI_TEST_ASSERT(Mani::isEqual(dot, expectedDot), "dot product should be equal to 11");
	}
}
MANI_SECTION_END(Vec2)

MANI_SECTION_BEGIN(Vec4, "Vector 4D section")
{
	MANI_TEST(CanSerializeAVector4, "Should successfully serialize and deserialize a vector")
	{
		{
			Mani::Vec4i v1;
			const std::string jsonString = ManiZ::to::json(v1);
			Mani::Vec4i v2 = ManiZ::from::json<Mani::Vec4i>(jsonString);
			MANI_TEST_ASSERT(v1 == v2, "v1 should equal v2 after going through ManiZ serialization/deserialization.");
		}
		{
			Mani::Vec4l v1;
			const std::string jsonString = ManiZ::to::json(v1);
			Mani::Vec4l v2 = ManiZ::from::json<Mani::Vec4l>(jsonString);
			MANI_TEST_ASSERT(v1 == v2, "v1 should equal v2 after going through ManiZ serialization/deserialization.");
		}
		{
			Mani::Vec4f v1;
			const std::string jsonString = ManiZ::to::json(v1);
			Mani::Vec4f v2 = ManiZ::from::json<Mani::Vec4f>(jsonString);
			MANI_TEST_ASSERT(v1 == v2, "v1 should equal v2 after going through ManiZ serialization/deserialization.");
		}
		{
			Mani::Vec4d v1;
			const std::string jsonString = ManiZ::to::json(v1);
			Mani::Vec4d v2 = ManiZ::from::json<Mani::Vec4d>(jsonString);
			MANI_TEST_ASSERT(v1 == v2, "v1 should equal v2 after going through ManiZ serialization/deserialization.");
		}
		{
			Mani::Vec4ui v1;
			const std::string jsonString = ManiZ::to::json(v1);
			Mani::Vec4ui v2 = ManiZ::from::json<Mani::Vec4ui>(jsonString);
			MANI_TEST_ASSERT(v1 == v2, "v1 should equal v2 after going through ManiZ serialization/deserialization.");
		}
		{
			Mani::Vec4ul v1;
			const std::string jsonString = ManiZ::to::json(v1);
			Mani::Vec4ul v2 = ManiZ::from::json<Mani::Vec4ul>(jsonString);
			MANI_TEST_ASSERT(v1 == v2, "v1 should equal v2 after going through ManiZ serialization/deserialization.");
		}
	}

	MANI_TEST(AddVector4s, "Should successfully operate on 2 vectors")
	{
		{
			Mani::Vec4i v1 = { 1, 2, 3, 4 };
			Mani::Vec4i v2 = { 5, 6, 7, 8 };
			Mani::Vec4i expected = { 6, 8, 10, 12 };
			MANI_TEST_ASSERT((v1 + v2) == expected, "v1 + v2 should equal expected");
		}
		{
			Mani::Vec4i v1 = { 1, 2, 3, 4 };
			Mani::Vec4i v2 = { 5, 6, 7, 8 };
			Mani::Vec4i expected = { 4, 4, 4, 4 };
			MANI_TEST_ASSERT((v2 - v1) == expected, "v2 - v1 should equal expected");
		}
		{
			Mani::Vec4i v1 = { 1, 2, 3, 4 };
			Mani::Vec4i v2 = { 5, 6, 7, 8 };
			Mani::Vec4i expected = { 5, 12, 21, 32 };
			MANI_TEST_ASSERT((v1 * v2) == expected, "v1 * v2 should equal expected");
		}
		{
			Mani::Vec4i v1 = { 1, 2, 3, 4 };
			Mani::Vec4i v2 = { 5, 6, 7, 8 };
			Mani::Vec4i expected = { 6, 8, 10, 12 };
			v1 += v2;
			MANI_TEST_ASSERT(v1 == expected, "v1 + v2 should equal expected");
		}
		{
			Mani::Vec4i v1 = { 1, 2, 3, 4 };
			Mani::Vec4i v2 = { 5, 6, 7, 8 };
			Mani::Vec4i expected = { 4, 4, 4, 4 };
			v2 -= v1;
			MANI_TEST_ASSERT(v2 == expected, "v2 - v1 should equal expected");
		}
		{
			Mani::Vec4i v1 = { 1, 2, 3, 4 };
			Mani::Vec4i v2 = { 5, 6, 7, 8 };
			Mani::Vec4i expected = { 5, 12, 21, 32 };
			v1 *= v2;
			MANI_TEST_ASSERT(v1 == expected, "v1 * v2 should equal expected");
		}
		{
			Mani::Vec4i v1 = { 1, 2, 3, 4 };
			constexpr int scale = 2;
			Mani::Vec4i expected = { 2, 4, 6, 8 };
			MANI_TEST_ASSERT(v1 * 2 == expected, "v1 * 2 should equal expected");
		}
		{
			Mani::Vec4i v1 = { 1, 2, 3, 4 };
			constexpr int scale = 2;
			Mani::Vec4i expected = { 2, 4, 6, 8 };
			v1 *= 2;
			MANI_TEST_ASSERT(v1 == expected, "v1 * 2 should equal expected");
		}
		{
			Mani::Vec4f v1 = { 1.f, 2.f, 3.f, 4.f };
			Mani::Vec4f v2 = { 5.f, 6.f, 7.f, 8.f };
			Mani::Vec4f v3 = { 1.f, 2.f, 3.f, 4.f };

			MANI_TEST_ASSERT(v1.isNearlyEqual(v2) == false, "v1 is not equal to v2");
			MANI_TEST_ASSERT(v1.isNearlyEqual(v3) == true, "v1 is equal to v3");
		}
		{
			Mani::Vec4f v1 = { 1.f, 2.f, 3.f, 4.f };
			constexpr int scale = 2;
			Mani::Vec4f expected = { .5f, 1.f, 1.5f, 2.f };
			MANI_TEST_ASSERT((v1 / 2).isNearlyEqual(expected), "v1 / 2 should equal expected");
		}
		{
			Mani::Vec4f v1 = { 1.f, 2.f, 3.f, 4.f };
			constexpr int scale = 2;
			Mani::Vec4f expected = { .5f, 1.f, 1.5f, 2.f };
			v1 /= 2;
			MANI_TEST_ASSERT(v1.isNearlyEqual(expected), "v1 / 2 should equal expected");
		}
		{
			const Mani::Vec4f v1 = { 1.f, 2.f, 3.f, 4.f };
			const Mani::Vec4f v1Normalized = v1.normalize();
			MANI_TEST_ASSERT(Mani::abs(v1Normalized.length() - 1.f) < FLT_EPSILON, "Can normalize v1");
		}
	}

	MANI_TEST(InterTypeMathVector4, "Should be able to do math between different vector types")
	{
		Mani::Vec4i v1{ 1, 2, 3, 4 };
		Mani::Vec4f v2{ 1.8f, 2.5f, 3.2f, 4.1f };
		Mani::Vec4f expected{ 2.8f, 4.5f, 6.2f, 8.1f };

		// doesn't compile because float to int requires a narrowing conversion which requires an explicit cast.
		// MANI_TEST_ASSERT((v1 + v2).isNearlyEqual(expected), "v1 + v2 should equal expected");
		MANI_TEST_ASSERT((v2 + v1).isNearlyEqual(expected), "v1 + v2 should equal expected");
	}

	MANI_TEST(Vector4Length, "Should correctly compute the length of a vector")
	{
		Mani::Vec4f v1{ 1.f, 2.f, 3.f, 4.f };
		const float length = v1.length();
		const float lengthSquared = v1.lengthSquared();

		constexpr float expectedSquared = 30.f;

		MANI_TEST_ASSERT(Mani::abs(length - std::sqrt(expectedSquared)) <= FLT_EPSILON, "length should be equal to what is expected");
		MANI_TEST_ASSERT(Mani::abs(lengthSquared - expectedSquared) <= FLT_EPSILON, "length should be equal to what is expected");
	}

	MANI_TEST(DistanceMathsVec4, "Should correctly compute the distance between 2 vectors")
	{
		Mani::Vec4f v1{ 1.f, 2.f, 3.f, 4.f };
		Mani::Vec4f v2{ 2.f, 3.f, 4.f, 5.f };

		const float v1tov2 = v1.distance(v2);
		const float v2tov1 = v2.distance(v1);

		const float v1tov2squared = v1.distanceSquared(v2);
		const float v2tov1squared = v2.distanceSquared(v1);

		constexpr float expectedSquared = 4.f;
		MANI_TEST_ASSERT(Mani::abs(v1tov2 - std::sqrt(expectedSquared)) <= FLT_EPSILON, "v1 should be at distance from v2");
		MANI_TEST_ASSERT(Mani::abs(v2tov1 - std::sqrt(expectedSquared)) <= FLT_EPSILON, "v2 should be at distance from v1");

		MANI_TEST_ASSERT(Mani::abs(v1tov2squared - expectedSquared) <= FLT_EPSILON, "distance squared should match");
		MANI_TEST_ASSERT(Mani::abs(v2tov1squared - expectedSquared) <= FLT_EPSILON, "distance squared should match");
	}

	MANI_TEST(ToStringVec4, "Should output a properly formatted string")
	{
		Mani::Vec4i v1{ 1, 2, 3, 4 };
		MANI_TEST_ASSERT(v1.toString() == "(1, 2, 3, 4)", "Should be equal to expected value");
	}

	MANI_TEST(DotAndCrossVec4, "Should dot 2 vec4")
	{
		Mani::Vec4f v1 = Mani::VEC4F::FORWARD;
		Mani::Vec4f v2 = Mani::VEC4F::RIGHT;

		const float dot = v1.dot(v2);

		MANI_TEST_ASSERT(Mani::isEqual(dot, 0.f), "dot should be 0");
	}
}
MANI_SECTION_END(Vec4)
