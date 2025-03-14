#pragma once

#include "_Vec.h"
#include "Debug.h"
#include "Traits.h"
#include "ManiMaths/Maths.h"

namespace Mani
{
    template<IsNumeric T>
    struct Vec<T, 4>
    {
        T x = static_cast<T>(0);
        T y = static_cast<T>(0);
        T z = static_cast<T>(0);
        T w = static_cast<T>(0);

        template<IsNumeric T1, IsNumeric T2>
        [[nodiscard]] static bool isNearlyEqual(const Vec<T1, 4>& lhs, const Vec<T2, 4> rhs, double tolerance = FLT_EPSILON)
        {
            return	abs(lhs.x - rhs.x) <= tolerance &&
                    abs(lhs.y - rhs.y) <= tolerance &&
                    abs(lhs.z - rhs.z) <= tolerance &&
                    abs(lhs.w - rhs.w) <= tolerance;
        }

        template<IsNumeric T2>
        [[nodiscard]] bool isNearlyEqual(const Vec<T2, 4>& rhs, double tolerance = FLT_EPSILON) const
        {
            return isNearlyEqual(*this, rhs, tolerance);
        }

        [[nodiscard]] T length() const
        {
            return sqrt(x * x + y * y + z * z + w * w);
        }

        [[nodiscard]] T lengthSquared() const
        {
            return x * x + y * y + z * z + w * w;
        }

        [[nodiscard]] Vec<T, 4> normalize() const
        {
            constexpr T _1 = static_cast<T>(1);
            T l = length();
            if (l > 0)
            {
                return *this * (_1 / l);    
            }
            return *this;
        }

        template<IsNumeric T1, IsNumeric T2>
        [[nodiscard]] static T distance(const Vec<T1, 4>& v1, const Vec<T2, 4>& v2)
        {
            return sqrt((v2.x - v1.x) * (v2.x - v1.x) + (v2.y - v1.y) * (v2.y - v1.y) + (v2.z - v1.z) * (v2.z - v1.z) + (v2.w - v1.w) * (v2.w - v1.w));
        }

        template<IsNumeric T2>
        [[nodiscard]] T distance(const Vec<T2, 4>& other) const
        {
            return distance(*this, other);
        }

        template<IsNumeric T1, IsNumeric T2>
        [[nodiscard]] static T distanceSquared(const Vec<T1, 4>& v1, const Vec<T2, 4>& v2)
        {
            return (v2.x - v1.x) * (v2.x - v1.x) + (v2.y - v1.y) * (v2.y - v1.y) + (v2.z - v1.z) * (v2.z - v1.z) + (v2.w - v1.w) * (v2.w - v1.w);
        }

        template<IsNumeric T2>
        [[nodiscard]] T distanceSquared(const Vec<T2, 4>& other) const
        {
            return distanceSquared(*this, other);
        }

        template<IsNumeric T1, IsNumeric T2>
        [[nodiscard]] static T dot(const Vec<T1, 4>& v1, const Vec<T2, 4>& v2)
        {
            return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
        }

        template<IsNumeric T2>
        [[nodiscard]] T dot(const Vec<T2, 4>& other) const
        {
            return dot(*this, other);
        }

        operator Vec<T, 2>() const { return { x, y }; }
        operator Vec<T, 3>() const { return { x, y, z }; }

        [[nodiscard]] std::string toString() const
        {
            return std::format("({}, {}, {}, {})", x, y, z, w);
        }
    };

    typedef Vec<int,            4> Vec4i;
    typedef Vec<long,           4> Vec4l;
    typedef Vec<float,          4> Vec4f;
    typedef Vec<double,         4> Vec4d;
    typedef Vec<unsigned int,   4> Vec4ui;
    typedef Vec<unsigned long,  4> Vec4ul;

    template<IsNumeric T1, IsNumeric T2>
    bool operator==(const Vec<T1, 4>& lhs, const Vec<T2, 4>& rhs)
    {
        return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
    }

    template<IsNumeric T1, IsNumeric T2>
    bool operator!=(const Vec<T1, 4>& lhs, const Vec<T2, 4>& rhs)
    {
        return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z || lhs.w != rhs.w;
    }

    template<IsNumeric T1, IsNumeric T2, IsNumeric TReturn = T1>
    Vec<TReturn, 4> operator+(const Vec<T1, 4>& lhs, const Vec<T2, 4>& rhs)
    {
        return { 
            lhs.x + rhs.x, 
            lhs.y + rhs.y, 
            lhs.z + rhs.z, 
            lhs.w + rhs.w
        };
    }

    template<IsNumeric T1, IsNumeric T2, IsNumeric TReturn = T1>
    Vec<TReturn, 4> operator-(const Vec<T1, 4>& lhs, const Vec<T2, 4>& rhs)
    {
        return { 
            lhs.x - rhs.x, 
            lhs.y - rhs.y, 
            lhs.z - rhs.z, 
            lhs.w - rhs.w
        };
    }

    template<IsNumeric T1, IsNumeric T2, IsNumeric TReturn = T1>
    Vec<TReturn, 4> operator*(const Vec<T1, 4>& lhs, const Vec<T2, 4>& rhs)
    {
        return { 
            lhs.x * rhs.x, 
            lhs.y * rhs.y, 
            lhs.z * rhs.z, 
            lhs.w * rhs.w
        };
    }

    template<IsNumeric T1, IsNumeric T2>
    void operator+=(Vec<T1, 4>& lhs, const Vec<T2, 4>& rhs)
    {
        lhs.x += rhs.x;
        lhs.y += rhs.y;
        lhs.z += rhs.z;
        lhs.w += rhs.w;
    }

    template<IsNumeric T1, IsNumeric T2>
    void operator-=(Vec<T1, 4>& lhs, const Vec<T2, 4>& rhs)
    {
        lhs.x -= rhs.x;
        lhs.y -= rhs.y;
        lhs.z -= rhs.z;
        lhs.w -= rhs.w;
    }

    template<IsNumeric T1, IsNumeric T2>
    void operator*=(Vec<T1, 4>& lhs, const Vec<T2, 4>& rhs)
    {
        lhs.x *= rhs.x;
        lhs.y *= rhs.y;
        lhs.z *= rhs.z;
        lhs.w *= rhs.w;
    }

    template<IsNumeric T, IsNumeric TScale, IsNumeric TReturn = T>
    Vec<TReturn, 4> operator*(const Vec<T, 4>& lhs, TScale scale)
    {
        return {
            lhs.x * scale,
            lhs.y * scale,
            lhs.z * scale,
            lhs.w * scale
        };
    }

    template<IsNumeric T, IsNumeric TScale, IsNumeric TReturn = T>
    Vec<TReturn, 4> operator*(TScale scale, const Vec<T, 4>& rhs)
    {
        return {
            rhs.x * scale,
            rhs.y * scale,
            rhs.z * scale,
            rhs.w * scale,
        };
    }

    template<IsNumeric T, IsNumeric TScale>
    void operator*=(Vec<T, 4>& lhs, TScale scale)
    {
        lhs.x *= scale;
        lhs.y *= scale;
        lhs.z *= scale;
        lhs.w *= scale;
    }

    template<IsNumeric T, IsNumeric TScale, IsNumeric TReturn = T>
    Vec<TReturn, 4> operator/(const Vec<T, 4>& lhs, TScale scale)
    {
        MANIMATHS_ASSERT(abs(scale) > 0);
        return {
            lhs.x / scale,
            lhs.y / scale,
            lhs.z / scale,
            lhs.w / scale
        };
    }

    template<IsNumeric T, IsNumeric TScale>
    void operator/=(Vec<T, 4>& lhs, TScale scale)
    {
        MANIMATHS_ASSERT(abs(scale) > 0);
        lhs.x /= scale;
        lhs.y /= scale;
        lhs.z /= scale;
        lhs.w /= scale;
    }

    namespace VEC4I
    {
        constexpr Vec4i 	ZERO		= {  0,  0,  0,  0 };
        constexpr Vec4i 	ONE			= {  1,  1,  1,  1 };
        constexpr Vec4i 	RIGHT		= {  1,  0,  0,  0 };
        constexpr Vec4i 	LEFT		= { -1,  0,  0,  0 };
        constexpr Vec4i 	UP			= {  0,  1,  0,  0 };
        constexpr Vec4i 	DOWN		= {  0, -1,  0,  0 };
        constexpr Vec4i 	FORWARD		= {  0,  0,  1,  0 };
        constexpr Vec4i 	BACK		= {  0,  0, -1,  0 };
    }

    namespace VEC4L
    {
        constexpr Vec4l 	ZERO		= {  0,  0,  0,  0 };
        constexpr Vec4l 	ONE			= {  1,  1,  1,  1 };
        constexpr Vec4l 	RIGHT		= {  1,  0,  0,  0 };
        constexpr Vec4l 	LEFT		= { -1,  0,  0,  0 };
        constexpr Vec4l 	UP			= {  0,  1,  0,  0 };
        constexpr Vec4l 	DOWN		= {  0, -1,  0,  0 };
        constexpr Vec4l 	FORWARD		= {  0,  0,  1,  0 };
        constexpr Vec4l 	BACK		= {  0,  0, -1,  0 };
    }

    namespace VEC4F
    {
        constexpr Vec4f 	ZERO		= {  0,  0,  0,  0 };
        constexpr Vec4f 	ONE			= {  1,  1,  1,  1 };
        constexpr Vec4f 	RIGHT		= {  1,  0,  0,  0 };
        constexpr Vec4f 	LEFT		= { -1,  0,  0,  0 };
        constexpr Vec4f 	UP			= {  0,  1,  0,  0 };
        constexpr Vec4f 	DOWN		= {  0, -1,  0,  0 };
        constexpr Vec4f 	FORWARD		= {  0,  0,  1,  0 };
        constexpr Vec4f 	BACK		= {  0,  0, -1,  0 };
    }

    namespace VEC4D
    {
        constexpr Vec4d 	ZERO		= {  0,  0,  0,  0 };
        constexpr Vec4d 	ONE			= {  1,  1,  1,  1 };
        constexpr Vec4d 	RIGHT		= {  1,  0,  0,  0 };
        constexpr Vec4d 	LEFT		= { -1,  0,  0,  0 };
        constexpr Vec4d 	UP			= {  0,  1,  0,  0 };
        constexpr Vec4d 	DOWN		= {  0, -1,  0,  0 };
        constexpr Vec4d 	FORWARD		= {  0,  0,  1,  0 };
        constexpr Vec4d 	BACK		= {  0,  0, -1,  0 };
    }

    namespace VEC4UI
    {
        constexpr Vec4ui 	ZERO		= {  0,  0,  0,  0 };
        constexpr Vec4ui 	ONE			= {  1,  1,  1,  1 };
        constexpr Vec4ui 	RIGHT		= {  1,  0,  0,  0 };
        constexpr Vec4ui 	LEFT		= { -1,  0,  0,  0 };
        constexpr Vec4ui 	UP			= {  0,  1,  0,  0 };
        constexpr Vec4ui 	DOWN		= {  0, -1,  0,  0 };
        constexpr Vec4ui 	FORWARD		= {  0,  0,  1,  0 };
        constexpr Vec4ui 	BACK		= {  0,  0, -1,  0 };
    }

    namespace VEC4UL
    {
        constexpr Vec4ul 	ZERO		= {  0,  0,  0,  0 };
        constexpr Vec4ul 	ONE			= {  1,  1,  1,  1 };
        constexpr Vec4ul 	RIGHT		= {  1,  0,  0,  0 };
        constexpr Vec4ul 	LEFT		= { -1,  0,  0,  0 };
        constexpr Vec4ul 	UP			= {  0,  1,  0,  0 };
        constexpr Vec4ul 	DOWN		= {  0, -1,  0,  0 };
        constexpr Vec4ul 	FORWARD		= {  0,  0,  1,  0 };
        constexpr Vec4ul 	BACK		= {  0,  0, -1,  0 };
    }
}
