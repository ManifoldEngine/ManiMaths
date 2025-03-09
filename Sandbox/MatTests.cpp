#include "ManiTests/ManiTests.h"
#include "ManiZ/ManiZ.h"

#include "ManiMaths/Matrix.h"
#include "ManiMaths/Maths.h"

MANI_SECTION_BEGIN(Matrix, "Enter the Matrix")
{
	MANI_TEST(CanSerializeAMatrix, "Should successfully serialize and deserialize a Matrix")
	{
		{
			Mani::Mat<float, 4, 4> m1;
			const std::string jsonString = ManiZ::to::json(m1);
			Mani::Mat<float, 4, 4> m2 = ManiZ::from::json<Mani::Mat<float, 4, 4>>(jsonString);
			//MANI_TEST_ASSERT(q1 == q2, "q1 should equal q2 after going through ManiZ serialization/deserialization.");
		}
	}
}
MANI_SECTION_END(Matrix)