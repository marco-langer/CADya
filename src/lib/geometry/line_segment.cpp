#include "geometry/line_segment.hpp"

#include "geometry/vector_utils.hpp"
#include "math.hpp"

#include <cassert>

namespace cdy {

LineSegment::LineSegment(Coordinate const& start, Coordinate const& end)
    : start_{start}
    , end_{end}
{
    assert(!is_zero(distance(start, end)));
}

auto make_line_segment(
        Coordinate const& start,
        Coordinate const& end)
    -> std::optional<LineSegment>
{
    return is_zero(distance(start, end))
        ? std::nullopt
        : std::optional<LineSegment>{LineSegment{start, end}};
}

} // namespace cdy
