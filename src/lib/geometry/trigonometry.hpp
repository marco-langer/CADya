#ifndef CADYA_GEOMETRY_TRIGONOMETRY_HPP
#define CADYA_GEOMETRY_TRIGONOMETRY_HPP

#include "angle.hpp"

#include <cmath>

namespace cdy {

inline auto sin(Angle<Radian> radians) -> double
{
    return std::sin(radians);
}

inline auto cos(Angle<Radian> radians) -> double
{
    return std::cos(radians);
}

} // namespace cdy

#endif
