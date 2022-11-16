#include "geometry/circle.hpp"

#include "geometry/coordinate_utils.hpp"
#include "geometry/intersection.hpp"
#include "geometry/line_segment.hpp"
#include "geometry/line_segment_utils.hpp"
#include "geometry/vector_utils.hpp"

#include <cassert>
#include <cmath>

namespace cdy {

auto make_circle(
        Coordinate const& first,
        Coordinate const& second,
        Coordinate const& third)
    -> std::optional<Circle>
{
    if (orientation(first, second, third) == ChoordinateOrientation::Collinear)
    {
        return std::nullopt;
    }

    /**
     * The intersection of the perpendicular bisectors of any circle chords
     * must be at the center of the circle if the three points are not collinear.
     *
     * https://math.stackexchange.com/a/827091
     */
    auto const chord1 = LineSegment{first, second};
    auto const chord2 = LineSegment{first, third};
    auto const bisector1 = perpendicular_bisector(chord1);
    auto const bisector2 = perpendicular_bisector(chord2);

    auto const maybe_intersection = intersection(bisector1, bisector2);
    assert(maybe_intersection.has_value());

    return Circle{*maybe_intersection, distance(*maybe_intersection, first)};
}

} // namespace cdy
