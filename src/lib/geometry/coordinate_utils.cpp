#include "geometry/coordinate_utils.hpp"

#include "geometry/vector_utils.hpp"
#include "math.hpp"

#include <cmath>

namespace cdy {

auto orientation(
        Coordinate const& point1,
        Coordinate const& point2,
        Coordinate const& point3)
    -> ChoordinateOrientation
{
    /*
     * check sign of determinant:
     *
     * | p1.x  p1.y  1 |
     * | p2.x  p2.y  1 |
     * | p3.x  p3.y  1 |
     */
    auto const determinant =
        point1.x * point2.y + point1.y * point3.x + point2.x * point3.y
        - point1.x * point3.y - point2.y * point3.x - point1.y * point2.x;

    if (is_zero(determinant))
    {
        return ChoordinateOrientation::Collinear;
    }
    else
    {
        return determinant < 0.0
            ? ChoordinateOrientation::Clockwise
            : ChoordinateOrientation::Counterclockwise;
    }
}

} // namespace cdy
