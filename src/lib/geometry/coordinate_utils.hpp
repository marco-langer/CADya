#ifndef CADYA_GEOMETRY_COORDINATE_UTILS_HPP
#define CADYA_GEOMETRY_COORDINATE_UTILS_HPP

#include "geometry/coordinate.hpp"

namespace cdy {

enum class ChoordinateOrientation { Collinear, Counterclockwise, Clockwise };

auto orientation(
        Coordinate const& point1,
        Coordinate const& point2,
        Coordinate const& point3)
    -> ChoordinateOrientation;

} // namespace cdy

#endif
