#pragma once

#include "_Vec.h"
#include "Debug.h"
#include "Traits.h"
#include "ManiMaths/Maths.h"
#include <format>

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
            return	Math::abs(lhs.x - rhs.x) <= tolerance &&
                    Math::abs(lhs.y - rhs.y) <= tolerance &&
                    Math::abs(lhs.z - rhs.z) <= tolerance &&
                    Math::abs(lhs.w - rhs.w) <= tolerance;
        }

        template<IsNumeric T2>
        [[nodiscard]] bool isNearlyEqual(const Vec<T2, 4>& rhs, double tolerance = FLT_EPSILON) const
        {
            return isNearlyEqual(*this, rhs, tolerance);
        }

        [[nodiscard]] T length() const
        {
            return Math::sqrt(x * x + y * y + z * z + w * w);
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
            return Math::sqrt((v2.x - v1.x) * (v2.x - v1.x) + (v2.y - v1.y) * (v2.y - v1.y) + (v2.z - v1.z) * (v2.z - v1.z) + (v2.w - v1.w) * (v2.w - v1.w));
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

        [[nodiscard]] static Vec<T, 4> clamp(const Vec<T, 4>& v, T target)
        {
            if (v.length() > target)
            {
                return v.normalize() * target;
            }
            return v;
        }

        [[nodiscard]] Vec<T, 4> clamp(T target) const
        {
            return clamp(*this, target);
        }

        [[nodiscard]] constexpr Vec<T, 4> operator-() const
        {
            return { -x, -y, -z, -w };
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
    [[nodiscard]] constexpr bool operator==(const Vec<T1, 4>& lhs, const Vec<T2, 4>& rhs)
    {
        return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
    }

    template<IsNumeric T1, IsNumeric T2>
    [[nodiscard]] constexpr bool operator!=(const Vec<T1, 4>& lhs, const Vec<T2, 4>& rhs)
    {
        return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z || lhs.w != rhs.w;
    }

    template<IsNumeric T1, IsNumeric T2, IsNumeric TReturn = T1>
    [[nodiscard]] constexpr Vec<TReturn, 4> operator+(const Vec<T1, 4>& lhs, const Vec<T2, 4>& rhs)
    {
        return { 
            lhs.x + rhs.x, 
            lhs.y + rhs.y, 
            lhs.z + rhs.z, 
            lhs.w + rhs.w
        };
    }

    template<IsNumeric T1, IsNumeric T2, IsNumeric TReturn = T1>
    [[nodiscard]] constexpr Vec<TReturn, 4> operator-(const Vec<T1, 4>& lhs, const Vec<T2, 4>& rhs)
    {
        return { 
            lhs.x - rhs.x, 
            lhs.y - rhs.y, 
            lhs.z - rhs.z, 
            lhs.w - rhs.w
        };
    }

    template<IsNumeric T1, IsNumeric T2, IsNumeric TReturn = T1>
    [[nodiscard]] constexpr Vec<TReturn, 4> operator*(const Vec<T1, 4>& lhs, const Vec<T2, 4>& rhs)
    {
        return { 
            lhs.x * rhs.x, 
            lhs.y * rhs.y, 
            lhs.z * rhs.z, 
            lhs.w * rhs.w
        };
    }

    template<IsNumeric T1, IsNumeric T2>
    constexpr void operator+=(Vec<T1, 4>& lhs, const Vec<T2, 4>& rhs)
    {
        lhs.x += rhs.x;
        lhs.y += rhs.y;
        lhs.z += rhs.z;
        lhs.w += rhs.w;
    }

    template<IsNumeric T1, IsNumeric T2>
    constexpr void operator-=(Vec<T1, 4>& lhs, const Vec<T2, 4>& rhs)
    {
        lhs.x -= rhs.x;
        lhs.y -= rhs.y;
        lhs.z -= rhs.z;
        lhs.w -= rhs.w;
    }

    template<IsNumeric T1, IsNumeric T2>
    constexpr void operator*=(Vec<T1, 4>& lhs, const Vec<T2, 4>& rhs)
    {
        lhs.x *= rhs.x;
        lhs.y *= rhs.y;
        lhs.z *= rhs.z;
        lhs.w *= rhs.w;
    }

    template<IsNumeric T, IsNumeric TScale, IsNumeric TReturn = T>
    [[nodiscard]] constexpr Vec<TReturn, 4> operator*(const Vec<T, 4>& lhs, TScale scale)
    {
        return {
            lhs.x * scale,
            lhs.y * scale,
            lhs.z * scale,
            lhs.w * scale
        };
    }

    template<IsNumeric T, IsNumeric TScale, IsNumeric TReturn = T>
    [[nodiscard]] constexpr Vec<TReturn, 4> operator*(TScale scale, const Vec<T, 4>& rhs)
    {
        return {
            rhs.x * scale,
            rhs.y * scale,
            rhs.z * scale,
            rhs.w * scale,
        };
    }

    template<IsNumeric T, IsNumeric TScale>
    constexpr void operator*=(Vec<T, 4>& lhs, TScale scale)
    {
        lhs.x *= scale;
        lhs.y *= scale;
        lhs.z *= scale;
        lhs.w *= scale;
    }

    template<IsNumeric T, IsNumeric TScale, IsNumeric TReturn = T>
    [[nodiscard]] constexpr Vec<TReturn, 4> operator/(const Vec<T, 4>& lhs, TScale scale)
    {
        MANIMATHS_ASSERT(Math::abs(scale) > 0);
        return {
            lhs.x / scale,
            lhs.y / scale,
            lhs.z / scale,
            lhs.w / scale
        };
    }

    template<IsNumeric T, IsNumeric TScale>
    constexpr void operator/=(Vec<T, 4>& lhs, TScale scale)
    {
        MANIMATHS_ASSERT(Math::abs(scale) > 0);
        lhs.x /= scale;
        lhs.y /= scale;
        lhs.z /= scale;
        lhs.w /= scale;
    }
}
