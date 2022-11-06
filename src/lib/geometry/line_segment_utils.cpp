#include "line_segment_utils.hpp"

#include "vector_utils.hpp"

namespace cdy {

[[nodiscard]] auto projected(
        LineSegment const& line_segment,
        Coordinate const& point)
    -> Coordinate
{
    auto const v = line_segment.second - line_segment.first;
    auto const w = point - line_segment.first;

    auto const c1 = dot_product(v, w);
    if (c1 <= 0.0)
    {
        return line_segment.first;
    }

    auto const c2 = dot_product(v, v);
    if (c2 <= c1)
    {
        return line_segment.second;
    }

    return line_segment.first + c1/c2 * v;
}

auto distance(
        LineSegment const& line_segment,
        Coordinate const& point)
    -> Length
{
    auto const projected_point = projected(line_segment, point);
    return distance(projected_point, point);
}

auto is_close(
        LineSegment const& line_segment,
        Coordinate const& point,
        double epsilon)
    -> bool
{
    return distance(line_segment, point) <= epsilon;
}

} // namespace cdy
