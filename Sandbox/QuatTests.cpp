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
}
MANI_SECTION_END(Quaternion)