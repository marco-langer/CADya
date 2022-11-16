#ifndef CADYA_GEOMETRY_MATH_HPP
#define CADYA_GEOMETRY_MATH_HPP

#include <cmath>
#include <type_traits>

namespace cdy {

// TODO C++23 replace with constexpr std::isnan and std::isinf
constexpr auto is_nan(double x) -> bool
{
    if (std::is_constant_evaluated())
    {
        return x != x;
    }
    else
    {
        return std::isnan(x);
    }
}

constexpr auto is_inf(double x) -> bool
{
    if (std::is_constant_evaluated())
    {
        return x == std::numeric_limits<double>::infinity()
            || x == -std::numeric_limits<double>::infinity();
    }
    else
    {
        return std::isinf(x);
    }
}

constexpr auto is_much_smaller_than(double value, double other) -> bool
{
    constexpr auto dummy_precision = 1e-12;
    return std::abs(value) < std::abs(other) * dummy_precision;
}

constexpr auto is_zero(double value) -> bool
{
    return is_much_smaller_than(value, 1.0);
}

constexpr auto is_approx_same(double first, double second) -> bool
{
    return is_zero(first - second);
}

} // namespace cdy

#endif
