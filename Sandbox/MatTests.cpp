#include "ManiTests/ManiTests.h"
#include "ManiZ/ManiZ.h"

#include "ManiMaths/Mat4.h"
#include "ManiMaths/Mat3.h"
#include "ManiMaths/MatTransforms.h"

#include "ManiMaths/Vec3.h"
#include "ManiMaths/Maths.h"

MANI_SECTION_BEGIN(Mat4, "Enter the Matrix")
{
	MANI_TEST(CanSerializeAMat4, "Should successfully serialize and deserialize a Matrix")
	{
		{
			Mani::Mat4f m1 = {
				 1.f,  2.f,  3.f,  4.f,
				 5.f,  6.f,  7.f,  8.f,
				 9.f, 10.f, 11.f, 12.f,
				13.f, 14.f, 15.f, 16.f,
			};
			const std::string jsonString = ManiZ::to::json(m1);
			Mani::Mat4f m2 = ManiZ::from::json<Mani::Mat4f>(jsonString);
			MANI_TEST_ASSERT(m1 == m2, "m1 should equal m2 after going through ManiZ serialization/deserialization.");
		}
		{
			Mani::Mat4d m1 = {
				 1.f,  2.f,  3.f,  4.f,
				 5.f,  6.f,  7.f,  8.f,
				 9.f, 10.f, 11.f, 12.f,
				13.f, 14.f, 15.f, 16.f,
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

    MANI_TEST(IndexOperatorMat4, "should be able to access the matrice like a normal 2d array")
    {
        {
            Mani::Mat4i m1 = { 1,  2,  3,  4,
                               5,  6,  7,  8,
                               9, 10, 11, 12,
                              13, 14, 15, 16 };

            MANI_TEST_ASSERT(m1[2][3] == 15, "[2][3] should be equal to 15");

            m1[2][3] = 100;

            MANI_TEST_ASSERT(m1[2][3] == 100, "should be able to mutate");
        }
        {
            const Mani::Mat4i m1 = { 1,  2,  3,  4,
                                     5,  6,  7,  8,
                                     9, 10, 11, 12,
                                    13, 14, 15, 16 };

            MANI_TEST_ASSERT(m1[2][3] == 15, "[2][3] should be equal to 15");
        }
        {
            Mani::Mat4i m1 = { 1,  2,  3,  4,
                               5,  6,  7,  8,
                               9, 10, 11, 12,
                              13, 14, 15, 16 };

            Mani::Mat4i m2 = { 1,  2,  3,  4,
                               5,  6,  7,  8,
                               9, 10, 11, 12,
                              13, 14, 15, 16 };

            m2[0][0] = m1[0][0] + m2[0][0];
            MANI_TEST_ASSERT(m2[0][0] == 2, "should be able to add and store by ref");
        }
    }

    MANI_TEST(MakeFunctionMat4, "make a mat4")
    {
        Mani::Mat4i m1 = Mani::Mat4i::make(4);
        Mani::Mat4i m2 = {
            4, 4, 4, 4,
            4, 4, 4, 4,
            4, 4, 4, 4,
            4, 4, 4, 4
        };
        MANI_TEST_ASSERT(m1 == m2, "should be able to easily fill a matrix from a single value");
    }

    MANI_TEST(Mat4Multiplication, "Should multiply 2 mat4s")
    {
        Mani::Mat4f m1 = Mani::Mat4f::make(2.f);
        Mani::Mat4f m2 = Mani::Mat4f::make(3.f);

        Mani::Mat4f result = m1 * m2;
        m1 *= m2;

        Mani::Mat4f expected = Mani::Mat4f::make(24.f);

        MANI_TEST_ASSERT(result.isNearlyEqual(expected), "should equal matf(24.f)");
        MANI_TEST_ASSERT(m1.isNearlyEqual(expected), "should equal matf(24.f)");
    }

    MANI_TEST(Mat4Transpose, "Should transpose a mat4")
    {
        Mani::Mat4i m1 = {
            1,  2,  3,  4,
            5,  6,  7,  8,
            9,  10, 11, 12,
            13, 14, 15, 16
        };

        Mani::Mat4i expected = {
            1, 5, 9,  13,
            2, 6, 10, 14,
            3, 7, 11, 15,
            4, 8, 12, 16
        };

        Mani::Mat4i result = m1.transpose();
        MANI_TEST_ASSERT(result == expected, "transpose should be as expected.");
    }

    MANI_TEST(Mat4Determinant, "Should calculate the determinant")
    {
        Mani::Mat4f m1 = {
            1,  2,  3,  4,
            5,  6,  7,  8,
            9,  10, 11, 12,
            13, 14, 15, 16
        };

        MANI_TEST_ASSERT(Mani::isEqual(m1.determinant(), 0.f), "should compute the correct determinant");
    }

    MANI_TEST(Mat4Inverse, "Should calculate the inverse")
    {
        Mani::Mat4f m1 = {
             3.f,   0.f,   1.f,   0.f,
            -1.f,   3.f,   5.f,  -2.f,
             1.f,  -1.f,   0.f,   0.f,
            -2.f,   5.f,  -4.f,   2.f
        };

        Mani::Mat4f expected = {
             -1.f/2.f,   1.f/2.f,   4.f,       1.f/2.f,
             -1.f/2.f,   1.f/2.f,   3.f,       1.f/2.f,
              5.f/2.f,  -3.f/2.f, -12.f,      -3.f/2.f,
             23.f/4.f, -15.f/4.f, -55.f/2.f, -13.f/4.f
        };

        MANI_TEST_ASSERT(m1.inverse().isNearlyEqual(expected), "should compute the correct inverse");
        MANI_TEST_ASSERT((m1 * expected).isNearlyEqual(Mani::MAT4F::IDENTITY), "AB == I means that A and B are inverse of each other");
    }

    MANI_TEST(Mat4to3Conversion, "should convert properly")
    {
        Mani::Mat4i m1 = {
             3,  0,  1,  0,
            -1,  3,  5, -2,
             1, -1,  0,  0,
            -2,  5, -4,  2
        };

        Mani::Mat3i m2 = m1;

        Mani::Mat3i expected = {
             3,  0,  1,
            -1,  3,  5,
             1, -1,  0
        };

        MANI_TEST_ASSERT(m2 == expected, "should convert properly");
    }

    MANI_TEST(Mat4TranslateAndScale, "should compute translation and scale properly")
    {
        {
            const Mani::Mat4f translation1 = Mani::translate(Mani::MAT4F::IDENTITY, Mani::VEC3F::RIGHT * 5.f);
            const Mani::Mat4f translation2 = Mani::translate(Mani::MAT4F::IDENTITY, Mani::VEC3F::DOWN * 2.f);
            const Mani::Mat4f translation3 = Mani::translate(Mani::MAT4F::IDENTITY, Mani::VEC3F::FORWARD * 3.f);

            const Mani::Mat4f translation = translation1 * translation2 * translation3;

            Mani::Vec3f point = translation * Mani::VEC3F::ZERO;
            Mani::Vec3f expected = { 5.f, -2.f, 3.f };
            MANI_TEST_ASSERT(point.isNearlyEqual(expected), "Point should be where it's expected.");
        }
        {
            const Mani::Mat4f withTranslation1 = Mani::translate(Mani::MAT4F::IDENTITY, Mani::VEC3F::RIGHT * 5.f);
            const Mani::Mat4f withRotation1 = Mani::rotateDeg(withTranslation1, 45.f, Mani::VEC3F::FORWARD); // rotate along the Y axis
            
            Mani::Vec3f point = withRotation1 * Mani::VEC3F::ZERO;
            Mani::Vec3f expected = { 0.f, 0.f, 5.f };
            MANI_TEST_ASSERT(point.isNearlyEqual(expected), "Point should be where it's expected.");
        }
        {
            const Mani::Mat4f withTranslation1 = Mani::translate(Mani::MAT4F::IDENTITY, Mani::VEC3F::RIGHT * 5.f);
            const Mani::Mat4f withScale1 = Mani::scale(withTranslation1, Mani::VEC3F::ONE * 3.f);

            Mani::Vec3f point = withScale1 * Mani::VEC3F::ZERO;
            Mani::Vec3f expected = { 15.f, 0.f, 0.f };
            MANI_TEST_ASSERT(point.isNearlyEqual(expected), "Point should be where it's expected.");
        }
    }
}
MANI_SECTION_END(Matrix)