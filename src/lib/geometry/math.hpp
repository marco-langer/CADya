#ifndef CADYA_GEOMETRY_MATH_HPP
#define CADYA_GEOMETRY_MATH_HPP

#include <cmath>
#include <cstdint>
#include <limits>
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

} // namespace cdy

#endif
