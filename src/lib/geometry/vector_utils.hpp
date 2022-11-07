#ifndef CADYA_GEOMETRY_VECTOR_UTILS_HPP
#define CADYA_GEOMETRY_VECTOR_UTILS_HPP

#include "coordinate.hpp"
#include "length.hpp"
#include "vector.hpp"

#include <cassert>
#include <cmath>

namespace cdy {

inline constexpr auto operator==(
        Coordinate const& lhs,
        Coordinate const& rhs)
    -> bool
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

inline constexpr auto operator+(
        Coordinate const& lhs,
        Vector const& rhs)
    -> Coordinate
{
    return Coordinate{lhs.x + rhs.x, lhs.y + rhs.y};
}

inline constexpr auto operator+(
        Vector const& lhs,
        Coordinate const& rhs)
    -> Coordinate
{
    return Coordinate{lhs.x + rhs.x, lhs.y + rhs.y};
}

inline constexpr auto operator+=(
        Coordinate& lhs,
        Vector const& rhs)
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
}

inline constexpr auto operator-(
        Coordinate const& first,
        Coordinate const& second)
    -> Vector
{
    return Vector{first.x - second.x, first.y - second.y};
}

inline constexpr auto operator*(
        double scalar,
        Vector const& vector)
    -> Vector
{
    return Vector{vector.x * scalar, vector.y * scalar};
}

inline constexpr auto operator*(
        Vector const& vector,
        double scalar)
    -> Vector
{
    return Vector{vector.x * scalar, vector.y * scalar};
}

inline constexpr auto operator*=(
        Vector& vector,
        double scalar)
{
    vector.x *= scalar;
    vector.y *= scalar;
}

inline constexpr auto operator/(
        Vector const& vector,
        double scalar)
    -> Vector
{
    assert(scalar != 0.0);
    return Vector{vector.x / scalar, vector.y / scalar};
}

inline constexpr auto operator/=(
        Vector& vector,
        double scalar)
    -> void
{
    assert(scalar != 0.0);
    vector.x /= scalar;
    vector.y /= scalar;
}

inline constexpr auto norm_squared(Vector const& vector) -> double
{
    return vector.x * vector.x + vector.y * vector.y;
}

inline auto norm(Vector const& vector) -> double
{
    return std::sqrt(norm_squared(vector));
}

inline auto distance_squared(
        Coordinate const& first,
        Coordinate const& second)
    -> Length
{
    return Length{norm_squared(first - second)};
}

inline auto distance(
        Coordinate const& first,
        Coordinate const& second)
    -> Length
{
    return Length{norm(first - second)};
}

inline auto dot_product(
        Vector const& first,
        Vector const& second)
    -> double
{
    return first.x * second.x + first.y * second.y;
}

} // namespace cdy

#endif
