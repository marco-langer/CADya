#ifndef CADYA_BEZIER_HPP
#define CADYA_BEZIER_HPP

#include <kernel/point.hpp>

#include <array>

namespace cy {

struct bezier_tag {};

template <Point Point>
struct basic_cubic_bezier
{
    auto operator[](std::size_t index) const noexcept -> Point
    {
        return pts[index];
    }

    std::array<Point, 4> pts;
};

template <Point Point>
struct get_tag<basic_cubic_bezier<Point>>
{
    using type = bezier_tag;
};

template <Point Point>
struct get_point_type<basic_cubic_bezier<Point>>
{
    using type = Point;
};

template <typename T>
concept CubicBezier = requires(T t)
{
    typename get_tag<T>::type;
    std::same_as<typename get_tag<T>::type, bezier_tag>;
    typename get_point_type<T>::type;
    Point<typename get_point_type<T>::type>;
};

} // namespace cy

#endif