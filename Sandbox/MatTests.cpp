#include "ManiTests/ManiTests.h"
#include "ManiZ/ManiZ.h"

#include "ManiMaths/Mat4.h"
#include "ManiMaths/Maths.h"

MANI_SECTION_BEGIN(Mat4, "Enter the Matrix")
{
	MANI_TEST(CanSerializeAMat4, "Should successfully serialize and deserialize a Matrix")
	{
		{
			Mani::Mat4f m1 = {
				 1,  2,  3,  4,
				 5,  6,  7,  8,
				 9, 10, 11, 12,
				13, 14, 15, 16,
			};
			const std::string jsonString = ManiZ::to::json(m1);
			Mani::Mat4f m2 = ManiZ::from::json<Mani::Mat4f>(jsonString);
			MANI_TEST_ASSERT(m1 == m2, "m1 should equal m2 after going through ManiZ serialization/deserialization.");
		}
		{
			Mani::Mat4d m1 = {
				 1,  2,  3,  4,
				 5,  6,  7,  8,
				 9, 10, 11, 12,
				13, 14, 15, 16,
			};
			const std::string jsonString = ManiZ::to::json(m1);
			Mani::Mat4d m2 = ManiZ::from::json<Mani::Mat4d>(jsonString);
			MANI_TEST_ASSERT(m1 == m2, "m1 should equal m2 after going through ManiZ serialization/deserialization.");
		}
	}

    MANI_TEST(Mat4Arithmetic, "Should successfully operate on 4x4 matrices")
    {
        {
            Mani::Mat4f m1 = { 1.0f, 2.0f, 3.0f, 4.0f,
                               5.0f, 6.0f, 7.0f, 8.0f,
                               9.0f, 10.0f, 11.0f, 12.0f,
                               13.0f, 14.0f, 15.0f, 16.0f };

            Mani::Mat4f m2 = { 16.0f, 15.0f, 14.0f, 13.0f,
                               12.0f, 11.0f, 10.0f, 9.0f,
                               8.0f, 7.0f, 6.0f, 5.0f,
                               4.0f, 3.0f, 2.0f, 1.0f };

            Mani::Mat4f expected = { 17.0f, 17.0f, 17.0f, 17.0f,
                                     17.0f, 17.0f, 17.0f, 17.0f,
                                     17.0f, 17.0f, 17.0f, 17.0f,
                                     17.0f, 17.0f, 17.0f, 17.0f };

            MANI_TEST_ASSERT((m1 + m2) == expected, "Matrix m1 + m2 should equal expected");
        }
        {
            Mani::Mat4f m1 = { 1.0f, 2.0f, 3.0f, 4.0f,
                               5.0f, 6.0f, 7.0f, 8.0f,
                               9.0f, 10.0f, 11.0f, 12.0f,
                               13.0f, 14.0f, 15.0f, 16.0f };

            Mani::Mat4f m2 = { 16.0f, 15.0f, 14.0f, 13.0f,
                               12.0f, 11.0f, 10.0f, 9.0f,
                               8.0f, 7.0f, 6.0f, 5.0f,
                               4.0f, 3.0f, 2.0f, 1.0f };

            Mani::Mat4f expected = { -15.0f, -13.0f, -11.0f, -9.0f,
                                     -7.0f, -5.0f, -3.0f, -1.0f,
                                     1.0f, 3.0f, 5.0f, 7.0f,
                                     9.0f, 11.0f, 13.0f, 15.0f };

            MANI_TEST_ASSERT((m1 - m2) == expected, "Matrix m1 - m2 should equal expected");
        }
        {
            Mani::Mat4f m1 = { 1.0f, 2.0f, 3.0f, 4.0f,
                               5.0f, 6.0f, 7.0f, 8.0f,
                               9.0f, 10.0f, 11.0f, 12.0f,
                               13.0f, 14.0f, 15.0f, 16.0f };

            Mani::Mat4f m2 = { 16.0f, 15.0f, 14.0f, 13.0f,
                               12.0f, 11.0f, 10.0f, 9.0f,
                               8.0f, 7.0f, 6.0f, 5.0f,
                               4.0f, 3.0f, 2.0f, 1.0f };

            m1 += m2;
            Mani::Mat4f expected = { 17.0f, 17.0f, 17.0f, 17.0f,
                                     17.0f, 17.0f, 17.0f, 17.0f,
                                     17.0f, 17.0f, 17.0f, 17.0f,
                                     17.0f, 17.0f, 17.0f, 17.0f };

            MANI_TEST_ASSERT(m1 == expected, "Matrix m1 should equal expected after m1 += m2");
        }
        {
            Mani::Mat4f m1 = { 1.0f, 2.0f, 3.0f, 4.0f,
                               5.0f, 6.0f, 7.0f, 8.0f,
                               9.0f, 10.0f, 11.0f, 12.0f,
                               13.0f, 14.0f, 15.0f, 16.0f };

            Mani::Mat4f m2 = { 16.0f, 15.0f, 14.0f, 13.0f,
                               12.0f, 11.0f, 10.0f, 9.0f,
                               8.0f, 7.0f, 6.0f, 5.0f,
                               4.0f, 3.0f, 2.0f, 1.0f };

            m1 -= m2;
            Mani::Mat4f expected = { -15.0f, -13.0f, -11.0f, -9.0f,
                                     -7.0f, -5.0f, -3.0f, -1.0f,
                                     1.0f, 3.0f, 5.0f, 7.0f,
                                     9.0f, 11.0f, 13.0f, 15.0f };

            MANI_TEST_ASSERT(m1 == expected, "Matrix m1 should equal expected after m1 -= m2");
        }
    }
}
MANI_SECTION_END(Matrix)